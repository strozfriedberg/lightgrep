package com.lightboxtechnologies.lightgrep;

import static com.lightboxtechnologies.lightgrep.Throws.*;

public class PatternInfo extends Handle {
  static {
    LibraryLoader.init();
  }

  // TODO: how to create these?
  private PatternInfo() {
    super(0);
  }

  public void destroy() {
    Pointer = 0; 
  }

  // TODO: wrap the LG_PatternInfo members or copy them?
}
