package com.lightboxtechnologies.lightgrep;

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

  private native void startsWithImpl(byte[] buffer, int offset, int size, long startOffset, HitCallback callback);

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

  private native int searchImpl(byte[] buffer, int offset, int size, long startOffset, HitCallback callback);

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
