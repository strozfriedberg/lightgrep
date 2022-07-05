package com.lightboxtechnologies.lightgrep;

import static com.lightboxtechnologies.lightgrep.Throws.*;

public class PatternHandle extends Handle {
  static {
    LibraryLoader.init();
  }

  public PatternHandle() {
    super(0);
    Pointer = PatternHandle.create();
  }

  private static native long create();

  /**
   * Releases resources held by the {@code PatternHandle}. {@code destroy()}
   * is idempotent. Other methods <b>MUST NOT</b> be called on a
   * {@code PatternHandle} which has been destroyed.
   */
  public native void destroy();

  /**
   * @throws IllegalStateException
   * @throws KeywordException
   * @throws NullPointerException
   */
  public int parsePattern(String pattern, KeyOptions options) throws KeywordException {
    throwIfNull("pattern", pattern);
    throwIfNull("options", options);
    throwIfDestroyed(this);
    return parsePatternImpl(pattern, options);
  }

  private native int parsePatternImpl(String pattern, KeyOptions options) throws KeywordException;
}
