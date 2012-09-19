package com.lightboxtechnologies.lightgrep;

public class KeyOptions {
  static {
    LibraryLoader.init();
  }

  static native void init();

  public boolean FixedString;
  public boolean CaseInsensitive;
}
