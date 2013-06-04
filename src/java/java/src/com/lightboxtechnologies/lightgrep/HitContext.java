package com.lightboxtechnologies.lightgrep;

public class HitContext {
  static {
    LibraryLoader.init();
  }

  static native void init();

  public long Begin;
  public long End;
  public String Decoded;
  public int Bad;

  public HitContext(long begin, long end, String decoded, int bad) {
    this.Begin = begin;
    this.End = end;
    this.Decoded = decoded;
    this.Bad = bad;
  }

  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }

    if (!(o instanceof HitContext)) {
      return false;
    }

    final HitContext h = (HitContext) o;
    return Begin == h.Begin && End == h.End && Bad == h.Bad &&
      (Decoded == null ? h.Decoded == null : Decoded.equals(h.Decoded));
  }

  public int hashCode() {
    return (((17*37 + Bad)*37 +
      ((int) (Begin ^ (Begin >> 32))))*37 +
      ((int) (End ^ (End >> 32))))*37 +
      (Decoded == null ? 0 : Decoded.hashCode());
  }

  public String toString() {
    return getClass().getName() +
      "[" + Begin + "," + End + "," + Decoded + "," + Bad + "]";
  }
}
