package com.lightboxtechnologies.lightgrep;

import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;

import static com.lightboxtechnologies.lightgrep.Throws.*;

public class LGUtil {
  static {
    LibraryLoader.init();
  }

// FIXME: windowSize is a misleading name. windowPadding would be better.

  public static HitContext getHitContext(DecoderHandle hDec, byte[] buffer, int offset, int size, long startOffset, long ibegin, long iend, String encoding, int windowSize, int replacement) throws UnsupportedEncodingException {
    throwIfNull("hDec", hDec);
    throwIfNull("buffer", buffer);
    throwIfNegative("offset", offset);
    throwIfNegative("size", size);
    throwIfByteArrayTooSmall("buffer", buffer, "offset", offset, "size", size);
    throwIfNegative("startOffset", startOffset);
    throwIfNegative("ibegin", ibegin);
    throwIfNegative("iend", iend);
    throwIfGreaterThan("startOffset", startOffset, "ibegin", ibegin);
    throwIfGreaterThan("ibegin", ibegin, "iend", iend);
    throwIfGreaterThan("iend", iend, startOffset + size);
    throwIfNull("encoding", encoding);
    throwIfNegative("windowSize", windowSize);
    throwIfNegative("replacement", replacement);
// TODO: should we require that replacement != 0?
    throwIfGreaterThan("replacement", replacement, 0x10FFFF);

    return getHitContextImpl(hDec, buffer, offset, size, startOffset, ibegin, iend, encoding, windowSize, replacement);
  }

  public static HitContext getHitContext(DecoderHandle hDec, ByteBuffer buffer, int size, long startOffset, long ibegin, long iend, String encoding, int windowSize, int replacement) throws UnsupportedEncodingException {
    throwIfNull("hDec", hDec);
    throwIfNull("buffer", buffer);
    throwIfNegative("size", size);
    throwIfByteBufferTooSmall("buffer", buffer, "size", size);
    throwIfNegative("startOffset", startOffset);
    throwIfNegative("ibegin", ibegin);
    throwIfNegative("iend", iend);
    throwIfGreaterThan("startOffset", startOffset, "ibegin", ibegin);
    throwIfGreaterThan("ibegin", ibegin, "iend", iend);
    throwIfGreaterThan("iend", iend, startOffset + size);
    throwIfNull("encoding", encoding);
    throwIfNegative("windowSize", windowSize);
    throwIfNegative("replacement", replacement);
// TODO: should we require that replacement != 0?
    throwIfGreaterThan("replacement", replacement, 0x10FFFF);

// FIXME: this code is repeated in several places, factor it out.
    if (buffer.isDirect()) {
      return getHitContextImpl(hDec, buffer, buffer.position(), size, startOffset, ibegin, iend, encoding, windowSize, replacement);
    }
    else {
      byte[] array = null;
      int position = 0;
      if (buffer.hasArray()) {
        // buffer wraps an array, use that
        array = buffer.array();
        position = buffer.arrayOffset() + buffer.position();
      }
      else {
        // ugh, this buffer must be read-only
        array = new byte[size];
        buffer.get(array);
      }

      return getHitContextImpl(hDec, array, position, size, startOffset, ibegin, iend, encoding, windowSize, replacement);
    }
  }

  private static native HitContext getHitContextImpl(DecoderHandle hDec, byte[] buffer, int offset, int size, long startOffset, long ibegin, long iend, String encoding, int windowSize, int replacement) throws UnsupportedEncodingException;

  private static native HitContext getHitContextImpl(DecoderHandle hDec, ByteBuffer buffer, int offset, int size, long startOffset, long ibegin, long iend, String encoding, int windowSize, int replacement) throws UnsupportedEncodingException;
}
