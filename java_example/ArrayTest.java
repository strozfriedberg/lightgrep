import java.io.BufferedReader;
import java.io.InputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileReader;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import com.lightboxtechnologies.lightgrep.ParserHandle;
import com.lightboxtechnologies.lightgrep.KeyOptions;
import com.lightboxtechnologies.lightgrep.ProgramHandle;
import com.lightboxtechnologies.lightgrep.ProgramOptions;
import com.lightboxtechnologies.lightgrep.ContextHandle;
import com.lightboxtechnologies.lightgrep.ContextOptions;
import com.lightboxtechnologies.lightgrep.HitCallback;
import com.lightboxtechnologies.lightgrep.SearchHit;

public class ArrayTest {

  public static int fillBuffer(InputStream in, byte[] buf) throws IOException {
    int rlen = 0, pos = 0;
    while (pos < buf.length &&
            (rlen = in.read(buf, pos, buf.length - pos)) != -1) {
      pos += rlen;
    }
    return pos;
  }

  public static class Filler implements Callable<Integer> {
    private final InputStream in;
    private final byte[] buf;

    public Filler(InputStream in, byte[] buf) {
      this.in = in;
      this.buf = buf;
    }

    public Integer call() throws IOException {
      return fillBuffer(in, buf);
    }
  }

  public static class HitCounter implements HitCallback {
    public int hitCount = 0;

    public void callback(SearchHit hit) {
      ++hitCount;
//              System.out.println(hit.Start + "," + hit.End + "," + hit.KeywordIndex);
    }
  }

  public static void main(String[] args) throws Exception {
    final ParserHandle hParser = new ParserHandle(10000);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;
      kopts.AsciiMode = true;

      final FileReader fr = new FileReader(args[0]);
      try {
        final BufferedReader r = new BufferedReader(fr);
        try {
          int linenum = 0;
          String line;
          while ((line = r.readLine()) != null) {
            hParser.addKeyword(line, linenum++, kopts, "ASCII");
          }
        }
        finally {
          r.close();
        }
      }
      finally {
        fr.close();
      } 

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final ContextOptions copts = new ContextOptions();

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final HitCounter cb = new HitCounter();

          long streamOffset = 0;

          final ExecutorService exec = Executors.newSingleThreadExecutor();

          byte[] cur = new byte[8*1024*1024];
          byte[] next = new byte[8*1024*1024];

          final InputStream in = new FileInputStream(args[1]);
          try {
            int size = fillBuffer(in, cur);

            final long startTime = System.currentTimeMillis();
            while (size > 0) {
              final Future<Integer> f = exec.submit(new Filler(in, next));

              hCtx.search(cur, 0, size, streamOffset, cb);
              streamOffset += size;

              size = f.get();

              byte[] tmp = cur;
              cur = next;
              next = cur;
            }
            hCtx.closeoutSearch(cb);
            final long searchTime = System.currentTimeMillis() - startTime;
            System.out.println((searchTime/1000.0) + " searchTime");
          }
          finally {
            in.close();
          }

          System.out.println(cb.hitCount + " hits");
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }    
    System.exit(0);
  }
}
