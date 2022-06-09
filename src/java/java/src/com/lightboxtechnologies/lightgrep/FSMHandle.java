package com.lightboxtechnologies.lightgrep;

import static com.lightboxtechnologies.lightgrep.Throws.*;

public class FSMHandle extends Handle {
  static {
    LibraryLoader.init();
  }

  /**
   * @throws IndexOutOfBoundsException
   */
  public FSMHandle(int patternCountHint, int numFsmStateSizeHint) {
    super(0);
    throwIfNegative("patternCountHint", patternCountHint);
    throwIfNegative("numFsmStateSizeHint", numFsmStateSizeHint);
    Pointer = FSMHandle.create(patternCountHint, numFsmStateSizeHint);
  }

  private static native long create(int patternCountHint, int numFsmStateSizeHint);

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
  public int addPattern(ProgramHandle hProg, PatternHandle hPattern, String encoding, int userIndex) {
    throwIfNull("hProg", hProg);
    throwIfNull("hPattern", hPattern);
    throwIfNull("encoding", encoding);
    throwIfDestroyed(this);
    throwIfDestroyed(hProg);
    throwIfDestroyed(hPattern);
    return addPatternImpl(hProg, hPattern, encoding, userIndex);
  }

  private native int addPatternImpl(ProgramHandle hProg, PatternHandle hPattern, String encoding, int userIndex);
}
