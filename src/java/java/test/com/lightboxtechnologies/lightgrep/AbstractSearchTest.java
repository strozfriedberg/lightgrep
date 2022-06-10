package com.lightboxtechnologies.lightgrep;

import org.junit.Test;

import java.util.List;

import static org.junit.Assert.fail;

public abstract class AbstractSearchTest extends AbstractDataDrivenTest {
  protected static class HitCollector implements HitCallback {
    public HitCollector(List<SearchHit> l) {
      hits = l;
    }

    public void callback(SearchHit hit) {
      hits.add(hit);
    }

    private final List<SearchHit> hits;
  }

  protected static class Pat {
    public final String pattern;
    public final KeyOptions opts;
    public final String[] encs;

    public Pat(String pattern, KeyOptions opts, String[] encs) {
      this.pattern = pattern;
      this.opts = opts;
      this.encs = encs;
    }
  }

  protected final int fsmSizeHint;
  protected final int pmapSizeHint;
  protected final Pat[] pats;
  protected final ProgramOptions popts;
  protected final ContextOptions copts;
  protected final byte[] buf;
  protected final int offset;
  protected final int size;
  protected final long startOffset;
  protected final long endOffset;
  protected final SearchHit[] ehits;

  public AbstractSearchTest(int fsmSizeHint, int pmapSizeHint, Pat[] pats, ProgramOptions popts, ContextOptions copts, byte[] buf, int offset, int size, long startOffset, long endOffset, SearchHit[] ehits, Class<? extends Throwable> tclass) {
    super(tclass);
    this.fsmSizeHint = fsmSizeHint;
    this.pmapSizeHint = pmapSizeHint;
    this.pats = pats;
    this.popts = popts;
    this.copts = copts;
    this.buf = buf;
    this.offset = offset;
    this.size = size;
    this.startOffset = startOffset;
    this.endOffset = endOffset;
    this.ehits = ehits;
  }

  protected void doTest() throws Throwable {
    try (final ProgramHandle hProg = new ProgramHandle(0)) {
      try (final FSMHandle hFsm = new FSMHandle(pmapSizeHint, fsmSizeHint)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          int i = 0;
          for (final Pat p : pats) {
            hPattern.parsePattern(p.pattern, p.opts);
            for (String e : p.encs) {
              hFsm.addPattern(hPattern, e, i);
            }
            ++i;
          }
        }

        hProg.compile(hFsm, popts);
      }

      try (final ContextHandle hCtx = hProg.createContext(copts)) {
        runSearch(hCtx);
      }
    }
  }

  protected abstract void runSearch(ContextHandle hCtx) throws Throwable;
}
