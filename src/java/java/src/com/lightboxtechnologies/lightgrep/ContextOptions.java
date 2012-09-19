package com.lightboxtechnologies.lightgrep;

public class ContextOptions {
  static {
    LibraryLoader.init();
  }
  
  static native void init();

  public long TraceBegin;
  public long TraceEnd;
}
