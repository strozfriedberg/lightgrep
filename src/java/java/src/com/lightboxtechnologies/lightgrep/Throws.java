package com.lightboxtechnologies.lightgrep;

import java.nio.ByteBuffer;

class Throws {
  public static void throwIfNull(String varname, Object var) {
    if (var == null) {
      throw new NullPointerException(varname + " == null");
    }
  }

  public static void throwIfNegative(String varname, int var) {
    throwIfLessThan(varname, var, 0);
  }

  public static void throwIfNegative(String varname, long var) {
    throwIfLessThan(varname, var, 0);
  }

  public static void throwIfLessThan(String varname, int var, int min) {
    if (var < min) {
      throw new IndexOutOfBoundsException(
        varname + " == " + var + " < " + min
      );
    }
  }

  public static void throwIfLessThan(String varname, long var, long min) {
    if (var < min) {
      throw new IndexOutOfBoundsException(
        varname + " == " + var + " < " + min
      );
    }
  }

  public static void throwIfGreaterThan(String varname, int var, int max) {
    if (var > max) {
      throw new IndexOutOfBoundsException(
        varname + " == " + var + " > " + max
      );
    }
  }

  public static void throwIfGreaterThan(String varname, long var, long max) {
    if (var > max) {
      throw new IndexOutOfBoundsException(
        varname + " == " + var + " > " + max
      );
    }
  }

  public static void throwIfGreaterThan(String leftname, long left, String rightname, long right) {
    if (left > right) {
      throw new IndexOutOfBoundsException(
        leftname + " == " + left + " > " + right + " == " + rightname
      );
    }
  }

  public static void throwIfDestroyed(Handle h) {
    if (h.isDestroyed()) {
      throw new IllegalStateException(
        "Tried calling method on destroyed handle"
      );
    }
  }

  public static void throwIfByteArrayTooSmall(String bufname, byte[] buffer, String offname, int offset, String sname, int size) {
    if (buffer.length - offset < size) {
      throw new IndexOutOfBoundsException(
        bufname + ".length == " + buffer.length + ", " +
        offname + " == " + offset + ", " +
        bufname + ".length - " + offname + " < " +
        sname + " == " + size
      );
    }
  }

  public static void throwIfByteBufferTooSmall(String bufname, ByteBuffer buffer, String sname, int size) {
    if (buffer.remaining() < size) {
      throw new IndexOutOfBoundsException(
        bufname + ".remaining() == " + buffer.remaining() + " < " +
        sname + " == " + size
      );
    }
  }
}
