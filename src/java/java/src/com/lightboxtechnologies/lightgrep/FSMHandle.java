package com.lightboxtechnologies.lightgrep;

import static com.lightboxtechnologies.lightgrep.Throws.*;

public class FSMHandle extends Handle {
  static {
    LibraryLoader.init();
  }

  /**
   * @throws IndexOutOfBoundsException
   */
  public FSMHandle(int numFsmStateSizeHint) {
    super(0);
    throwIfNegative("numFsmStateSizeHint", numFsmStateSizeHint);
    Pointer = FSMHandle.create(numFsmStateSizeHint);
  }

  private static native long create(int numFsmStateSizeHint);

  /**
   * Releases resources held by the {@code FSMHandle}. {@code destroy()}
   * is idempotent. Other methods <b>MUST NOT</b> be called on a
   * {@code FSMHandle} which has been destroyed.
   */
  public native void destroy();

  /**
   * @throws IllegalStateException
   * @throws NullPointerException
   *
   * FIXME: some unknown encoding exception
   */  
  public int addPattern(PatternMapHandle hMap, PatternHandle hPattern, String encoding) {
    throwIfNull("hMap", hMap);
    throwIfNull("hPattern", hPattern);
    throwIfNull("encoding", encoding);
    throwIfDestroyed(this);
    throwIfDestroyed(hMap);
    throwIfDestroyed(hPattern);
    return addPatternImpl(hMap, hPattern, encoding);
  }

  private native int addPatternImpl(PatternMapHandle hMap, PatternHandle hPattern, String encoding);

  /**
   * @throws IllegalStateException
   * @throws KeywordException // FIXME: correct?
   * @throws NullPointerException
   */
  public ProgramHandle createProgram(ProgramOptions options) throws KeywordException {
    throwIfNull("options", options);
    throwIfDestroyed(this);
    return createProgramImpl(options);
  }

  private native ProgramHandle createProgramImpl(ProgramOptions options) throws KeywordException;
}
