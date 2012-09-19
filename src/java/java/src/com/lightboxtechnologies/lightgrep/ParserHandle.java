package com.lightboxtechnologies.lightgrep;

public class ParserHandle implements Handle {
  static {
    System.loadLibrary("jlightgrep");
  }

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
   * @throws NullPointerException
   * @throws IndexOutOfBoundsException
   * @throws KeywordException
   */ 
  public native int addKeyword(String keyword, int keyIndex, KeyOptions options, String encoding) throws KeywordException;

  /**
   * @throws NullPointerException
   * @throws KeywordException
   */
  public native ProgramHandle createProgram(ProgramOptions options) throws KeywordException;
}
