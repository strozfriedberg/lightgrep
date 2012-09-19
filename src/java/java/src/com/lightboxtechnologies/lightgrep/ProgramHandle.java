package com.lightboxtechnologies.lightgrep;

public class ProgramHandle implements Handle {
  static {
    LibraryLoader.init();
  }

  static native void init();

  private final long Pointer;

  private ProgramHandle(long ptr) {
    Pointer = ptr;
  }

  public native void destroy();

  public native int size();

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   * @throws NullPointerException
   */
  public native void write(byte[] buffer, int offset);

  /**
   * @throws IndexOutOfBoundsException 
   * @throws NullPointerException
   */
  public static native ProgramHandle read(byte[] buffer, int offset, int size);

  /**
   * @throws IllegalStateException
   * @throws NullPointerException
   */
  public native ContextHandle createContext(ContextOptions options);
}
