package com.lightboxtechnologies.lightgrep;

class LibraryLoader {
  static public void init() {
    System.loadLibrary("jlightgrep");
   
    // Initializiation on the libjlightgrep side. 
    ParserHandle.init();
    ProgramHandle.init();
    ContextHandle.init();
    
    KeyOptions.init();
    ProgramOptions.init();
    ContextOptions.init();
  }
}
