package com.lightboxtechnologies.lightgrep;

import java.nio.ByteBuffer;

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
