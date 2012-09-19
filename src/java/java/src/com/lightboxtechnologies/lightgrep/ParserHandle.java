package com.lightboxtechnologies.lightgrep;

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

  public native void destroy();
 
  /**
   * @throws IllegalStateException
   * @throws IndexOutOfBoundsException
   * @throws KeywordException
   * @throws NullPointerException
   */ 
  public native int addKeyword(String keyword, int keyIndex, KeyOptions options, String encoding) throws KeywordException;

  /**
   * @throws IllegalStateException
   * @throws KeywordException
   * @throws NullPointerException
   */
  public native ProgramHandle createProgram(ProgramOptions options) throws KeywordException;
}
