package com.lightboxtechnologies.lightgrep;

public class Lightgrep {
  static {
    System.loadLibrary("jlightgrep");
    init();
  }

  private static native void init();

  public static abstract class Handle {
    private final long Pointer;

    protected Handle(long ptr) {
      Pointer = ptr;
    }
  }

  public static class ParserHandle extends Handle {
    private ParserHandle(long ptr) {
      super(ptr);
    }
  }

  public static class ProgramHandle extends Handle {
    private ProgramHandle(long ptr) {
      super(ptr);
    }
  }

  public static class ContextHandle extends Handle {
    private ContextHandle(long ptr) {
      super(ptr);
    }
  }

  public static class LG_KeyOptions {
    public boolean FixedString;
    public boolean CaseInsensitive; 
  }

  public static class LG_ProgramOptions {
    public boolean Determinize;
  }

  public static class LG_ContextOptions {
    public long TraceBegin;
    public long TraceEnd;
  }

  public static class LG_SearchHit {
    public long Start;
    public long End;
    public int KeywordIndex;

    public LG_SearchHit(long start, long end, int keywordIndex) {
      Start = start;
      End = end;
      KeywordIndex = keywordIndex;
    }

    public boolean equals(Object o) {
      if (this == o) {
        return true;
      }

      if (!(o instanceof LG_SearchHit)) {
        return false;
      }

      final LG_SearchHit h = (LG_SearchHit) o;
      return Start == h.Start && End == h.End && KeywordIndex == h.KeywordIndex;
    }
  }

  public static interface Callback {
    void callback(LG_SearchHit hit);
  }

  public static native int lg_ok(Handle handle);

  public static native String lg_error(Handle handle);

  public static native ParserHandle lg_create_parser(int numFsmStateSizeHint);

  public static native int lg_destroy_parser(ParserHandle hParser);

  public static native int lg_add_keyword(ParserHandle hParser, String keyword,  int keyIndex, LG_KeyOptions options, String encoding);

  public static native ProgramHandle lg_create_program(ParserHandle hParser, LG_ProgramOptions options);

  public static native int lg_program_size(ProgramHandle hProg);

  public static native void lg_write_program(ProgramHandle hProg, byte[] buffer, int offset);

  public static native ProgramHandle lg_read_program(byte[] buffer, int offset, int size);

  public static native int lg_destroy_program(ProgramHandle hProg);

  public static native ContextHandle lg_create_context(ProgramHandle hProg, LG_ContextOptions options);

  public static native int lg_destroy_context(ContextHandle hCtx);

  public static native void lg_starts_with(ContextHandle hCtx, byte[] buffer, int offset, int size, long startOffset, Callback callback);

  public static native void lg_reset_context(ContextHandle hCtx);

  public static native int lg_search(ContextHandle hCtx, byte[] buffer, int offset, int size, long startOffset, Callback callback);

  public static native void lg_closeout_search(ContextHandle hCtx, Callback callback); 
}
