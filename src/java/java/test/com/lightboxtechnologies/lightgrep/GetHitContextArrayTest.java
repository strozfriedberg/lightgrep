package com.lightboxtechnologies.lightgrep;

import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import static org.junit.Assert.assertEquals;

@RunWith(Parameterized.class)
public class GetHitContextArrayTest extends BaseGetHitContextTest {
  public GetHitContextArrayTest(byte[] buf, int offset, int size, long startOffset, long ibegin, long iend, String encoding, int windowSize, int replacement, HitContext exp, Class<? extends Throwable> tclass) {
    super(buf, offset, size, startOffset, ibegin, iend, encoding, windowSize, replacement, exp, tclass);
  }

  @Parameters
  public static Collection<Object[]> data() throws UnsupportedEncodingException {
    final List<Object[]> l = new ArrayList<Object[]>(BaseGetHitContextTest.data());

    // negative buffer offset
    l.add(
      new Object[]{ "abc".getBytes("UTF-8"), -1, 0, 0, 0, 0, "UTF-8", 0, 0, null, IndexOutOfBoundsException.class }
    );
    return l;
  }

  protected void doTest() throws Throwable {
    final HitContext act = LGUtil.getHitContext(
      buf, offset, size, startOffset, ibegin, iend,
      encoding, windowSize, replacement
    );

    assertEquals(exp, act);
  }
}
