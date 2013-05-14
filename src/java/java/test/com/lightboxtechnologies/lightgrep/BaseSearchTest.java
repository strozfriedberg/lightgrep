package com.lightboxtechnologies.lightgrep;

import org.junit.runners.Parameterized.Parameters;

import java.io.UnsupportedEncodingException;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

public abstract class BaseSearchTest extends AbstractSearchTest {
  @Parameters
  public static Collection<Object[]> data() throws UnsupportedEncodingException {
    return Arrays.asList(new Object[][] {
      /* Bad Arguments */
      // null buffer
      { 0, 0, new Pat[]{ new Pat("a+b", new KeyOptions(), new String[]{ "ASCII" }) }, new ProgramOptions(), new ContextOptions(), null, 0, 0, 0, new SearchHit[0], NullPointerException.class },
      // negative buffer size
      { 0, 0, new Pat[]{ new Pat("a+b", new KeyOptions(), new String[]{ "ASCII" }) }, new ProgramOptions(), new ContextOptions(), "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII"), 0, -1, 0, new SearchHit[0], IndexOutOfBoundsException.class },
      // buffer offset >= buffer end
      { 0, 0, new Pat[]{ new Pat("a+b", new KeyOptions(), new String[]{ "ASCII" }) }, new ProgramOptions(), new ContextOptions(), "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII"), "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII").length,  "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII").length, 0, new SearchHit[0], IndexOutOfBoundsException.class },
      // buffer offset + buffer size > buffer end
      { 0, 0, new Pat[]{ new Pat("a+b", new KeyOptions(), new String[]{ "ASCII" }) }, new ProgramOptions(), new ContextOptions(), "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII"), 1, "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII").length, 0, new SearchHit[0], IndexOutOfBoundsException.class },
      // negative startOffset
      { 0, 0, new Pat[]{ new Pat("a+b", new KeyOptions(), new String[]{ "ASCII" }) }, new ProgramOptions(), new ContextOptions(), "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII"), 0, "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII").length, -1, new SearchHit[0], IndexOutOfBoundsException.class },
      /* Successful Searches */
      { 0, 0, new Pat[]{ new Pat("WMD", new KeyOptions(), new String[]{ "ASCII" }) }, new ProgramOptions(), new ContextOptions(), "Iraq".getBytes("ASCII"), 0, "Iraq".getBytes("ASCII").length, 0, new SearchHit[]{}, null },
      { 0, 0, new Pat[]{ new Pat("a+b", new KeyOptions(), new String[]{ "ASCII" }) }, new ProgramOptions(), new ContextOptions(), "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII"), 0, "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII").length, 0, new SearchHit[]{ new SearchHit(0, 4, 0), new SearchHit(7, 9, 0), new SearchHit(10, 12, 0) }, null }
    });
  }

  public BaseSearchTest(int fsmSizeHint, int pmapSizeHint, Pat[] pats, ProgramOptions popts, ContextOptions copts, byte[] buf, int offset, int size, long startOffset, SearchHit[] ehits, Class<? extends Throwable> tclass) {
    super(fsmSizeHint, pmapSizeHint, pats, popts, copts, buf, offset, size, startOffset, ehits, tclass);
  }
}
