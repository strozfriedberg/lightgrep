package com.lightboxtechnologies.lightgrep;

abstract class Handle implements AutoCloseable {
  static {
    LibraryLoader.init();
  }

  static native void init();

  Handle(long ptr) {
    Pointer = ptr;
  }

  protected long Pointer;

  public abstract void destroy();

  public boolean isDestroyed() {
    return Pointer == 0;
  }

  public void close() {
    destroy();
  }
}
