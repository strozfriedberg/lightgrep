package com.lightboxtechnologies.lightgrep;

import org.junit.runners.Parameterized.Parameters;

import java.io.UnsupportedEncodingException;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

public abstract class BaseGetHitContextTest extends AbstractDataDrivenTest {
  @Parameters
  public static Collection<Object[]> data() throws UnsupportedEncodingException {
    return Arrays.asList(new Object[][] {
      /* Bad Arguments */
      // null buffer 
      { null, 0, 0, 0, 0, 0, "UTF-8", 0, 0, null, NullPointerException.class },
      // negative buffer size
      { "abc".getBytes("UTF-8"), 0, -1, 0, 0, 0, "UTF-8", 0, 0, null, IndexOutOfBoundsException.class },
      // buffer offset >= buffer end
      { "abc".getBytes("UTF-8"), "abc".getBytes("UTF-8").length, "abc".getBytes("UTF-8").length, 0, 0, 0, "UTF-8", 0, 0, null, IndexOutOfBoundsException.class },
      // buffer offset + buffer size > buffer end
      { "abc".getBytes("UTF-8"), 1, "abc".getBytes("UTF-8").length, 0, 0, 0, "UTF-8", 0, 0, null, IndexOutOfBoundsException.class },
      // negative startOffset
      { "abc".getBytes("UTF-8"), 0, "abc".getBytes("UTF-8").length, -1, 0, 0, "UTF-8", 0, 0, null, IndexOutOfBoundsException.class },
      // negative ibegin
      { "abc".getBytes("UTF-8"), 0, "abc".getBytes("UTF-8").length, 0, -1, 0, "UTF-8", 0, 0, null, IndexOutOfBoundsException.class },
      // negative iend
      { "abc".getBytes("UTF-8"), 0, "abc".getBytes("UTF-8").length, 0, 0, -1, "UTF-8", 0, 0, null, IndexOutOfBoundsException.class },
      // startOffset > ibegin
      { "abc".getBytes("UTF-8"), 0, "abc".getBytes("UTF-8").length, 1, 0, 0, "UTF-8", 0, 0, null, IndexOutOfBoundsException.class },
      // ibegin > iend
      { "abc".getBytes("UTF-8"), 0, "abc".getBytes("UTF-8").length, 1, 0, 0, "UTF-8", 0, 0, null, IndexOutOfBoundsException.class },
      // iend > startOffset + size
      { "abc".getBytes("UTF-8"), 0, "abc".getBytes("UTF-8").length, 0, 5, 0, "UTF-8", 0, 0, null, IndexOutOfBoundsException.class },
      // null encoding
      { "abc".getBytes("UTF-8"), 0, "abc".getBytes("UTF-8").length, 0, 0, 0, null, 0, 0, null, NullPointerException.class },
      // bogus encoding
      { "abc".getBytes("UTF-8"), 0, "abc".getBytes("UTF-8").length, 0, 0, 0, "bogus|bogus", 0, 0, null, UnsupportedEncodingException.class },
      // negative windowSize
      { "abc".getBytes("UTF-8"), 0, "abc".getBytes("UTF-8").length, 0, 0, 0, "UTF-8", -1, 0, null, IndexOutOfBoundsException.class },
      // negative replacement
      { "abc".getBytes("UTF-8"), 0, "abc".getBytes("UTF-8").length, 0, 0, 0, "UTF-8", 0, -1, null, IndexOutOfBoundsException.class },
      // replacement > 10FFFFF
      { "abc".getBytes("UTF-8"), 0, "abc".getBytes("UTF-8").length, 0, 0, 0, "UTF-8", 0, 0x110000, null, IndexOutOfBoundsException.class },
      /* Successful Decoding */
      { new byte[]{ (byte) 0xE2, (byte) 0x9A, (byte) 0xA1, 0x20, 0x61, 0x62, 0x63, (byte) 0xD0, (byte) 0x96 }, 0, 9, 0, 4, 7, "UTF-8", 2, 0xFFFD, new HitContext(0, 9, "⚡ abcЖ", 0), null },
      { new byte[]{ (byte) 0xFF, (byte) 0xFF, (byte) 0xFF, 0x20, 0x61, 0x62, 0x63, (byte) 0xD0, (byte) 0x96 }, 0, 9, 0, 4, 7, "UTF-8", 2, 0xFFFD, new HitContext(2, 9, "� abcЖ", 1), null }
    });
  }

  protected final byte[] buf;
  protected final int offset;
  protected final int size;
  protected final long startOffset;
  protected final long ibegin;
  protected final long iend;
  protected final String encoding;
  protected final int windowSize;
  protected final int replacement;
  protected final HitContext exp;

  public BaseGetHitContextTest(byte[] buf, int offset, int size, long startOffset, long ibegin, long iend, String encoding, int windowSize, int replacement, HitContext exp, Class<? extends Throwable> tclass) {
    super(tclass);
    this.buf = buf;
    this.offset = offset;
    this.size = size;
    this.startOffset = startOffset;
    this.ibegin = ibegin;
    this.iend = iend;
    this.encoding = encoding;
    this.windowSize = windowSize;
    this.replacement = replacement;
    this.exp = exp;
  }

  protected void doTest() throws Throwable {
    final DecoderHandle hDec = new DecoderHandle();
    try {
      runGetHitContext(hDec);
    }
    finally {
      hDec.destroy();
    }
  }

  protected abstract void runGetHitContext(DecoderHandle hDec) throws Throwable;
}
