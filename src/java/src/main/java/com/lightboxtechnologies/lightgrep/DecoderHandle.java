package com.lightboxtechnologies.lightgrep;

import static com.lightboxtechnologies.lightgrep.Throws.*;

public class DecoderHandle extends Handle {
  static {
    LibraryLoader.init();
  }

  public DecoderHandle() {
    super(0);
    Pointer = DecoderHandle.create();
  }

  private static native long create();

  /**
   * Releases resources held by the {@code DecoderHandle}. {@code destroy()}
   * is idempotent. Other methods <b>MUST NOT</b> be called on a
   * {@code DecoderHandle} which has been destroyed.
   */
  public native void destroy();
}
