package com.lightboxtechnologies.lightgrep;

public class ContextOptions {
  static {
    LibraryLoader.init();
  }
  
  static native void init();
}
