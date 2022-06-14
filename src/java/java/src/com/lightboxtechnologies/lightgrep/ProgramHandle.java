package com.lightboxtechnologies.lightgrep;

import static com.lightboxtechnologies.lightgrep.Throws.*;

public class ProgramHandle extends Handle {
  static {
    LibraryLoader.init();
  }

  /**
   * @throws IndexOutOfBoundsException
   */
  public ProgramHandle(int numTotalPatternsSizeHint) {
    super(0);
    throwIfNegative("numTotalPatternsSizeHint", numTotalPatternsSizeHint);
    Pointer = ProgramHandle.create(numTotalPatternsSizeHint);
  }

  private static native long create(int numTotalPatternsSizeHint);

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
   * @throws NullPointerException
   * @throws ProgramException
   */
  public int compile(FSMHandle hFsm, ProgramOptions options) {
    throwIfNull("hFsm", hFsm);
    throwIfNull("options", options);
    throwIfDestroyed(this);
    throwIfDestroyed(hFsm);
    return compileImpl(hFsm, options);
  }

  private native int compileImpl(FSMHandle hFsm, ProgramOptions options);

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
   */
  public int count() {
    throwIfDestroyed(this);
    return countImpl();
  }

  private native int countImpl();

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   */
  public PatternInfo getPatternInfo(int patternIndex) {
    throwIfDestroyed(this);
    throwIfNegative("patternIndex", patternIndex);
    // NB: getPatternInfoImpl checks for patternIndex >= size()
    // because doing it here would mean an extra JNI call.
    return getPatternInfoImpl(patternIndex);
  }

  private native PatternInfo getPatternInfoImpl(int patternIndex);

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   */
  public int getUserIndex(int patternIndex) {
    throwIfDestroyed(this);
    throwIfNegative("patternIndex", patternIndex);
    // NB: getUserIndexImpl checks for patternIndex >= size()
    // because doing it here would mean an extra JNI call.
    return getUserIndexImpl(patternIndex);
  }

  private native int getUserIndexImpl(int patternIndex);

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   */
  public void setUserIndex(int patternIndex, int userIndex) {
    throwIfDestroyed(this);
    throwIfNegative("patternIndex", patternIndex);
    // NB: setUserIndexImpl checks for patternIndex >= size()
    // because doing it here would mean an extra JNI call.
    setUserIndexImpl(patternIndex, userIndex);
  }

  private native void setUserIndexImpl(int patternIndex, int userIndex);

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
