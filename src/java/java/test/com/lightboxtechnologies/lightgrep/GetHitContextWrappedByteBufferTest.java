package com.lightboxtechnologies.lightgrep;

import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import java.nio.ByteBuffer;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import static org.junit.Assert.assertEquals;

@RunWith(Parameterized.class)
public class GetHitContextWrappedByteBufferTest extends BaseGetHitContextTest {
  public GetHitContextWrappedByteBufferTest(byte[] buf, int offset, int size, long startOffset, long ibegin, long iend, String encoding, int windowSize, int replacement, HitContext exp, Class<? extends Throwable> tclass) {
    super(buf, offset, size, startOffset, ibegin, iend, encoding, windowSize, replacement, exp, tclass);

    if (buf != null) {
      bbuf = ByteBuffer.wrap(buf); 
      bbuf.put(buf).position(offset);
    }
    else {
      bbuf = null;
    }
  }

  protected final ByteBuffer bbuf;

  protected void runGetHitContext(DecoderHandle hDec) throws Throwable {
    final HitContext act = LGUtil.getHitContext(
      hDec, bbuf, size, startOffset, ibegin, iend,
      encoding, windowSize, replacement
    );

    assertEquals(exp, act);
  }
}
