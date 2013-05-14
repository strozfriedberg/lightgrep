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
  public Object getUserData(int patternIndex) {
    throwIfDestroyed(this);
    throwIfNegative("patternIndex", patternIndex);
    // NB: getUserDataImpl checks for patternIndex >= size()
    // because doing it here would mean an extra JNI call.
    return getUserDataImpl(patternIndex);
  }

  private native Object getUserDataImpl(int patternIndex);

  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   */
  public void setUserData(int patternIndex, Object userData) {
    throwIfDestroyed(this);
    throwIfNegative("patternIndex", patternIndex);
    // NB: setUserDataImpl checks for patternIndex >= size()
    // because doing it here would mean an extra JNI call.
    setUserDataImpl(patternIndex, userData);
  }

  private native void setUserDataImpl(int patternIndex, Object userData);
}
