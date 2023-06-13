package com.lightboxtechnologies.lightgrep;

import java.nio.ByteBuffer;

import static com.lightboxtechnologies.lightgrep.Throws.*;

public class ContextHandle extends Handle {
  static {
    LibraryLoader.init();
  }

  static native void init();

  private ContextHandle(long ptr) {
    super(ptr);
  }

  public native void destroy();

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   * @throws NullPointerException
   */
  public void startsWith(byte[] buffer, int offset, int size, long startOffset, HitCallback callback) {
    throwIfNull("buffer", buffer);
    throwIfNegative("offset", offset);
    throwIfNegative("size", size);
    throwIfByteArrayTooSmall("buffer", buffer, "offset", offset, "size", size);
    throwIfNegative("startOffset", startOffset);
    throwIfNull("callback", callback);
    throwIfDestroyed(this);
    startsWithImpl(buffer, offset, size, startOffset, callback);
  }

  public void startsWith(ByteBuffer buffer, int size, long startOffset, HitCallback callback) {
    throwIfNull("buffer", buffer);
    throwIfNegative("size", size);
    throwIfByteBufferTooSmall("buffer", buffer, "size", size);
    throwIfNegative("startOffset", startOffset);
    throwIfNull("callback", callback);
    throwIfDestroyed(this);

    if (buffer.isDirect()) {
      startsWithImpl(buffer, buffer.position(), size, startOffset, callback);
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

      startsWithImpl(array, position, size, startOffset, callback);
    }
  }

  private native void startsWithImpl(byte[] buffer, int offset, int size, long startOffset, HitCallback callback);

  private native void startsWithImpl(ByteBuffer buffer, int offset, int size, long startOffset, HitCallback callback);

  public void reset() {
    throwIfDestroyed(this);
    resetImpl();
  }

  private native void resetImpl();

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   * @throws NullPointerException
   */
  public int search(byte[] buffer, int offset, int size, long startOffset, HitCallback callback) {
    throwIfNull("buffer", buffer);
    throwIfNegative("offset", offset);
    throwIfNegative("size", size);
    throwIfByteArrayTooSmall("buffer", buffer, "offset", offset, "size", size);
    throwIfNegative("startOffset", startOffset);
    throwIfNull("callback", callback);
    throwIfDestroyed(this);
    return searchImpl(buffer, offset, size, startOffset, callback);
  }

  public int search(ByteBuffer buffer, int size, long startOffset, HitCallback callback) {
    throwIfNull("buffer", buffer);
    throwIfNegative("size", size);
    throwIfByteBufferTooSmall("buffer", buffer, "size", size);
    throwIfNegative("startOffset", startOffset);
    throwIfNull("callback", callback);
    throwIfDestroyed(this);

    if (buffer.isDirect()) {
      return searchImpl(buffer, buffer.position(), size, startOffset, callback);
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

      return searchImpl(array, position, size, startOffset, callback);
    }
  }

  private native int searchImpl(byte[] buffer, int offset, int size, long startOffset, HitCallback callback);

  private native int searchImpl(ByteBuffer buffer, int offset, int size, long startOffset, HitCallback callback);

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   */
  public void closeoutSearch(HitCallback callback) {
    throwIfNull("callback", callback);
    throwIfDestroyed(this);
    closeoutSearchImpl(callback);
  }

  private native void closeoutSearchImpl(HitCallback callback);
}
