package com.lightboxtechnologies.lightgrep;

import static com.lightboxtechnologies.lightgrep.Throws.*;

public class ProgramHandle extends Handle {
  static {
    LibraryLoader.init();
  }

  static native void init();

  private ProgramHandle(long ptr) {
    super(ptr);
  }

  public native void destroy();

  /**
   * @throws IllegalStateException
   */
  public int size() {
    throwIfDestroyed(this);
    return sizeImpl();
  }

  private native int sizeImpl();

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   * @throws NullPointerException
   */
  public void write(byte[] buffer, int offset) {
    throwIfNull("buffer", buffer);
    throwIfNegative("offset", offset);
    throwIfByteArrayTooSmall(
      "buffer", buffer, "offset", offset, "program size", size()
    );
    throwIfDestroyed(this);
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
    throwIfByteArrayTooSmall("buffer", buffer, "offset", offset, "size", size);
    return readImpl(buffer, offset, size);
  }

  private static native ProgramHandle readImpl(byte[] buffer, int offset, int size);

  /**
   * @throws IllegalStateException
   * @throws NullPointerException
   */
  public ContextHandle createContext(ContextOptions options) {
    throwIfNull("options", options);
    throwIfDestroyed(this);
    return createContextImpl(options);
  }

  private native ContextHandle createContextImpl(ContextOptions options);
}
