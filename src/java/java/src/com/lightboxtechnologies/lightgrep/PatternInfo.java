package com.lightboxtechnologies.lightgrep;

public class PatternInfo extends Handle {
  static {
    LibraryLoader.init();
  }

  static native void init();

  private PatternInfo(long ptr) {
    super(ptr);
  }

  /**
   * @throws UnsupportedOperationException
   */
  public void destroy() {
    // The LG_HPATTERNMAP owns the LG_PatternInfo, not us.
    throw new UnsupportedOperationException(
      "It is neither necessary nor possible to manually free a PatternInfo."
    );
  }

  public native String getPattern();

  public native String getEncodingChain();

  public native Object getUserData();

  public native void setUserData(Object o);
}
