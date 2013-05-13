package com.lightboxtechnologies.lightgrep;

import static com.lightboxtechnologies.lightgrep.Throws.*;

public class PatternMapHandle extends Handle {
  static {
    LibraryLoader.init();
  }

  /**
   * @throws IndexOutOfBoundsException
   */
  public PatternMapHandle(int numTotalPatternsSizeHint) {
    super(0);
    throwIfNegative("numTotalPatternsSizeHint", numTotalPatternsSizeHint);
    Pointer = PatternMapHandle.create(numTotalPatternsSizeHint);
  }

  private static native long create(int numTotalPatternsSizeHint);

  /**
   * Releases resources held by the {@code PatternMapHandle}. {@code destroy()}
   * is idempotent. Other methods <b>MUST NOT</b> be called on a
   * {@code PatternMapHandle} which has been destroyed.
   */
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
   */ 
  public PatternInfo patternInfo(int patternIndex) {
    throwIfDestroyed(this);
    throwIfNegative("patternIndex", patternIndex);
    return patternInfoImpl(patternIndex);
  }

  private native PatternInfo patternInfoImpl(int patternIndex);
}
