package com.lightboxtechnologies.lightgrep;

import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import static org.junit.Assert.assertEquals;

// FIXME: add ctors to options objects which take params

@RunWith(Parameterized.class)
public class StartsWithArrayTest extends BaseStartsWithTest {

  @Parameters
  public static Collection<Object[]> data() throws UnsupportedEncodingException {
    final List<Object[]> l = new ArrayList<Object[]>(BaseStartsWithTest.data());

    // negative buffer offset
    l.add(
      new Object[]{ 0, 0, new Pat[]{ new Pat("a+b", new KeyOptions(), new String[]{ "ASCII" }) }, new ProgramOptions(), new ContextOptions(), "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII"), -1, "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII").length, 0, new SearchHit[0], IndexOutOfBoundsException.class }
    );
    return l;
  }

  public StartsWithArrayTest(int fsmSizeHint, int pmapSizeHint, Pat[] pats, ProgramOptions popts, ContextOptions copts, byte[] buf, int offset, int size, long startOffset, SearchHit[] ehits, Class<? extends Throwable> tclass) {
    super(fsmSizeHint, pmapSizeHint, pats, popts, copts, buf, offset, size, startOffset, ehits, tclass);
  }

  protected void runSearch(ContextHandle hCtx) throws Throwable {
    final List<SearchHit> hits = new ArrayList<SearchHit>();
    final HitCallback cb = new HitCollector(hits);

    hCtx.startsWith(buf, offset, size, startOffset, cb);
    assertEquals(Arrays.asList(ehits), hits);
  }
}
