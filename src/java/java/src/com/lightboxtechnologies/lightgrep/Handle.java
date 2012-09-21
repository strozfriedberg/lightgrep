package com.lightboxtechnologies.lightgrep;

abstract class Handle {
  Handle(long ptr) {
    Pointer = ptr;
  }

  protected long Pointer;

  public abstract void destroy();

  public boolean isDestroyed() {
    return Pointer == 0;
  }
}
