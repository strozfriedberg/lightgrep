package com.lightboxtechnologies.lightgrep;

import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static org.junit.Assert.assertEquals;

@RunWith(Parameterized.class)
public class SearchWrappedByteBufferTest extends AbstractSearchTest {

  public SearchWrappedByteBufferTest(int fsmSizeHint, int pmapSizeHint, Pat[] pats, ProgramOptions popts, ContextOptions copts, byte[] buf, int offset, int size, long startOffset, SearchHit[] ehits, Class<? extends Throwable> tclass) {
    super(fsmSizeHint, pmapSizeHint, pats, popts, copts, buf, offset, size, startOffset, ehits, tclass);

    if (buf != null) {
      bbuf = ByteBuffer.wrap(buf);    
      bbuf.put(buf).position(offset);
    }
    else {
      bbuf = null;
    }
  }

  protected final ByteBuffer bbuf;

  protected void runSearch(ContextHandle hCtx) throws Throwable {
    final List<SearchHit> hits = new ArrayList<SearchHit>();
    final HitCallback cb = new HitCollector(hits);

    final int ret = hCtx.search(bbuf, size, startOffset, cb);
    assertEquals(0, ret);

    hCtx.closeoutSearch(cb);
    assertEquals(Arrays.asList(ehits), hits);
  }
}
