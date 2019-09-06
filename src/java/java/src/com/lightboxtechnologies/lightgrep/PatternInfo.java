package com.lightboxtechnologies.lightgrep;

import java.util.Arrays;

public class PatternInfo {
  static {
    LibraryLoader.init();
  }

  static native void init();

  public String Pattern;
  public String EncodingChain;
  public int UserIndex;

  public PatternInfo(String pattern, String encodingChain, int userIndex) {
    this.Pattern = pattern;
    this.EncodingChain = encodingChain;
    this.UserIndex = userIndex;
  }

  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }

    if (!(o instanceof PatternInfo)) {
      return false;
    }

    final PatternInfo pi = (PatternInfo) o;
    return
      (Pattern == null ? pi.Pattern == null :
        Pattern.equals(pi.Pattern)) &&
      (EncodingChain == null ? pi.EncodingChain == null :
        EncodingChain.equals(pi.EncodingChain)) &&
      UserIndex == pi.UserIndex;
  }

  public int hashCode() {
    return ((17*37 + (Pattern == null ? 0 : Pattern.hashCode()))*37 +
      (EncodingChain == null ? 0 : EncodingChain.hashCode()))*37 +
      UserIndex;
  }

  public String toString() {
    return "PatternInfo[" +
      Pattern + "," + EncodingChain + "," + UserIndex + "]";
  }
}
