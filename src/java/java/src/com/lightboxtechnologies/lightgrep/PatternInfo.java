package com.lightboxtechnologies.lightgrep;

import java.util.Arrays;

public class PatternInfo {
  static {
    LibraryLoader.init();
  }

  static native void init();

  public String Pattern;
  public String EncodingChain;
  public Object UserData;

  public PatternInfo(String pattern, String encodingChain, Object userData) {
    this.Pattern = pattern;
    this.EncodingChain = encodingChain;
    this.UserData = userData;
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
      (UserData == null ? pi.UserData == null :
        UserData.equals(pi.UserData));
  }

  public int hashCode() {
    return ((17*37 + (Pattern == null ? 0 : Pattern.hashCode()))*37 +
      (EncodingChain == null ? 0 : EncodingChain.hashCode()))*37 +
      (UserData == null ? 0 :
        (UserData.getClass().isArray() ?
          Arrays.deepHashCode((Object[]) UserData) : UserData.hashCode()));
  }

  public String toString() {
    return "PatternInfo[" +
      Pattern + "," + EncodingChain + "," + UserData + "]";
  }
}
