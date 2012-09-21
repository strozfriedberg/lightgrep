package com.lightboxtechnologies.lightgrep;

import static com.lightboxtechnologies.lightgrep.Throws.*;

public class ParserHandle implements Handle {
  static {
    LibraryLoader.init();
  }

  static native void init();

  private final long Pointer;

  /**
   * @throws IllegalArgumentException
   */
  public ParserHandle(int numFsmStateSizeHint) {
    if (numFsmStateSizeHint < 0) {
      throw new IllegalArgumentException(
        "numFsmStateSizeHint == " + numFsmStateSizeHint + " < 0"
      );
    }
    Pointer = ParserHandle.create(numFsmStateSizeHint);
  }

  private static native long create(int numFsmStateSizeHint);

  /**
   * Releases resources held by the {@code ParserHandle}. {@code destroy()}
   * is idempotent. Other methods <b>MUST NOT</b> be called on a
   * {@code ParserHandle} which has been destroyed.
   */
  public native void destroy();
 
  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   * @throws KeywordException
   * @throws NullPointerException
   */ 
  public int addKeyword(String keyword, int keyIndex, KeyOptions options, String encoding) throws KeywordException {
    throwIfNull("keyword", keyword);
    throwIfNegative("keyIndex", keyIndex); 
    throwIfNull("options", options);
    throwIfNull("encoding", encoding);
    return addKeywordImpl(keyword, keyIndex, options, encoding);
  }

  private native int addKeywordImpl(String keyword, int keyIndex, KeyOptions options, String encoding) throws KeywordException;

  /**
   * @throws IllegalStateException
   * @throws KeywordException
   * @throws NullPointerException
   */
  public ProgramHandle createProgram(ProgramOptions options) throws KeywordException {
    throwIfNull("options", options);
    return createProgramImpl(options);
  }

  private native ProgramHandle createProgramImpl(ProgramOptions options) throws KeywordException;
}
