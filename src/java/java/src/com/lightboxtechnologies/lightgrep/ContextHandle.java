package com.lightboxtechnologies.lightgrep;

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
  public native void startsWith(byte[] buffer, int offset, int size, long startOffset, HitCallback callback);

  public native void reset();

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   * @throws NullPointerException
   */
  public native int search(byte[] buffer, int offset, int size, long startOffset, HitCallback callback);

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   */
  public native void closeoutSearch(HitCallback callback);
}
