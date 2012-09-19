package com.lightboxtechnologies.lightgrep;

public class ProgramHandle implements Handle {
  static {
    System.loadLibrary("jlightgrep");
  }

  private final long Pointer;

  private ProgramHandle(long ptr) {
    Pointer = ptr;
  }

  public native void destroy();

  public native int size();

  /**
   * @throws NullPointerException
   * @throws IndexOutOfBoundsException
   */
  public native void write(byte[] buffer, int offset);

  /**
   * @throws NullPointerException
   * @throws IndexOutOfBoundsException 
   */
  public static native ProgramHandle read(byte[] buffer, int offset, int size);

  /**
   * @throws NullPointerException
   */
  public native ContextHandle createContext(ContextOptions options);
}
