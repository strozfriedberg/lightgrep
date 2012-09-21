package com.lightboxtechnologies.lightgrep;

class Throws {
  public static void throwIfNull(String varname, Object var) {
    if (var == null) {
      throw new NullPointerException(varname + " == null");
    }
  }

  public static void throwIfNegative(String varname, int var) {
    if (var < 0) {
      throw new IndexOutOfBoundsException(varname + " == " + var + " < 0");
    }
  }

  public static void throwIfNegative(String varname, long var) {
    if (var < 0) {
      throw new IndexOutOfBoundsException(varname + " == " + var + " < 0");
    }
  }
}
