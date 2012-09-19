package com.lightboxtechnologies.lightgrep;

public class ProgramOptions {
  static {
    LibraryLoader.init();
  }
  
  static native void init();

  public boolean Determinize;
}
