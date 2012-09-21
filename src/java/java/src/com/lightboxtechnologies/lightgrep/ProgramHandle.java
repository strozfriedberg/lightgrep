package com.lightboxtechnologies.lightgrep;

import static com.lightboxtechnologies.lightgrep.Throws.*;

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
  public void write(byte[] buffer, int offset) {
    throwIfNull("buffer", buffer);
    throwIfNegative("offset", offset);
    writeImpl(buffer, offset);
  }

  private native void writeImpl(byte[] buffer, int offset);

  /**
   * @throws IndexOutOfBoundsException 
   * @throws NullPointerException
   */
  public static ProgramHandle read(byte[] buffer, int offset, int size) {
    throwIfNull("buffer", buffer);
    throwIfNegative("offset", offset);
    throwIfNegative("size", size);
    return readImpl(buffer, offset, size);
  }

  private static native ProgramHandle readImpl(byte[] buffer, int offset, int size);

  /**
   * @throws IllegalStateException
   * @throws NullPointerException
   */
  public ContextHandle createContext(ContextOptions options) {
    throwIfNull("options", options);
    return createContextImpl(options);
  }

  private native ContextHandle createContextImpl(ContextOptions options);
}
