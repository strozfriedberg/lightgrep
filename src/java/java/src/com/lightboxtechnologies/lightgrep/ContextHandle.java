package com.lightboxtechnologies.lightgrep;

import static com.lightboxtechnologies.lightgrep.Throws.*;

public class ContextHandle implements Handle {
  static {
    LibraryLoader.init();
  }

  static native void init();

  private final long Pointer;

  private ContextHandle(long ptr) {
    Pointer = ptr;
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
    throwIfNegative("startOffset", startOffset);
    throwIfNull("callback", callback);
    startsWithImpl(buffer, offset, size, startOffset, callback);
  }

  private native void startsWithImpl(byte[] buffer, int offset, int size, long startOffset, HitCallback callback);

  public native void reset();

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   * @throws NullPointerException
   */
  public int search(byte[] buffer, int offset, int size, long startOffset, HitCallback callback) {
    throwIfNull("buffer", buffer);
    throwIfNegative("offset", offset);
    throwIfNegative("size", size);

    throwIfNegative("startOffset", startOffset);
    throwIfNull("callback", callback);
    return searchImpl(buffer, offset, size, startOffset, callback);
  }

  private native int searchImpl(byte[] buffer, int offset, int size, long startOffset, HitCallback callback);

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   */
  public void closeoutSearch(HitCallback callback) {
    throwIfNull("callback", callback);
    closeoutSearchImpl(callback);
  }

  private native void closeoutSearchImpl(HitCallback callback);
}
