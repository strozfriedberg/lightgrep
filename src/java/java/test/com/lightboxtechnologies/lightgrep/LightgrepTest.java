package com.lightboxtechnologies.lightgrep;

import org.junit.Test;

import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

public class LightgrepTest {
  @Test
  public void createDestroyParserTest() {
    final ParserHandle hParser = new ParserHandle(1);
    try {
      assertNotNull(hParser);
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noAddKeywordAfterDestroyParserTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(1);
    hParser.destroy();

    final KeyOptions kopts = new KeyOptions();
    kopts.FixedString = false;
    kopts.CaseInsensitive = false;

    hParser.addKeyword("meh", 0, kopts, "ASCII");
  }

  @Test(expected=IllegalStateException.class)
  public void noCreateProgramAfterDestroyParserTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(1);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");
    }
    finally {
      hParser.destroy();
    }

    final ProgramOptions popts = new ProgramOptions();
    popts.Determinize = true;

    hParser.createProgram(popts);
  }

/*
// FIXME: make calls to handles after destroy() throw IllegalStateException
  @Test
  public void doubleDestroyParserTest() {
    final ParserHandle hParser = new ParserHandle(1);
    hParser.destroy();
// FIXME: why does this crash?
//    hParser.destroy();
  }
*/

  @Test
  public void addKeywordGoodTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      final int ret = hParser.addKeyword("meh", 0, kopts, "ASCII");
      assertTrue(ret != 0);
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=KeywordException.class)
  public void addKeywordBadTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("x*", 0, kopts, "ASCII");
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=NullPointerException.class)
  public void addKeywordNullTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword(null, 0, kopts, "ASCII");
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void addKeywordNegativeIndexTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", -1, kopts, "ASCII");
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=NullPointerException.class)
  public void addKeywordNullOptionsTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      hParser.addKeyword("meh", 0, null, "ASCII");
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=NullPointerException.class)
  public void addKeywordNullEncodingTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, null);
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=KeywordException.class)
  public void addKeywordBadEncodingTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "UTF-9");
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=KeywordException.class)
  public void createProgramEmptyTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(1);
    try {
      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
    }
    finally {
      hParser.destroy();
    }
  }

  @Test
  public void createProgramGoodTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        assertNotNull(hProg);
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

/*
  @Test
  public void doubleDestroyProgramTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      hProg.destroy();
      hProg.destroy();
    }
    finally {
      hParser.destroy();
    }

  }
*/

  @Test(expected=IllegalStateException.class)
  public void noSizeAfterDestroyProgramTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      hProg.destroy();

      hProg.size();
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noWriteAfterProgramDestroyTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      final byte[] buf = new byte[hProg.size()];
      hProg.destroy();

      hProg.write(buf, 0);
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noCreateContextAfterProgramDestroyTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      hProg.destroy();

      final ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
      copts.TraceBegin = Long.MIN_VALUE;
      copts.TraceEnd = Long.MIN_VALUE;

      hProg.createContext(copts);
    }
    finally {
      hParser.destroy();
    }
  }
  @Test
  public void writeProgramGoodTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final byte[] exp = {
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x01, 0x6D, 0x00, 0x00,
          0x0B, 0x00, 0x00, 0x00, 0x01, 0x65, 0x00, 0x00,
          0x01, 0x68, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00,
          0x07, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00,
          0x07, 0x00, 0x00, 0x00
        };

        final int size = hProg.size();
        assertEquals(exp.length, size);

        final byte[] buf = new byte[size];
        hProg.write(buf, 0);

        assertArrayEquals(exp, buf);
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=NullPointerException.class)
  public void writeProgramNullBufferTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        hProg.write(null, 0);
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void writeProgramNegativeOffsetTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final byte[] buf = new byte[hProg.size()];
        hProg.write(buf, -1);
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void writeProgramOffsetOffEndTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final byte[] buf = new byte[hProg.size()];
        hProg.write(buf, buf.length);
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void writeProgramOffsetTooLargeTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final byte[] buf = new byte[hProg.size()];
        hProg.write(buf, 1);
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  private static final byte[] aProgram = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x6D, 0x00, 0x00,
    0x0B, 0x00, 0x00, 0x00, 0x01, 0x65, 0x00, 0x00,
    0x01, 0x68, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00
  };

  @Test
  public void readWriteProgramGoodTest() {
    final byte[] exp = aProgram;

    final ProgramHandle hProg = ProgramHandle.read(exp, 0, exp.length);
    try {
      final int size = hProg.size();
      assertEquals(exp.length, size);

      final byte[] buf = new byte[size];
      hProg.write(buf, 0);

      assertArrayEquals(exp, buf);
    }
    finally {
      hProg.destroy();
    }
  }

  @Test(expected=NullPointerException.class)
  public void readProgramNullBufferTest() {
    final ProgramHandle hProg = ProgramHandle.read(null, 0, 1);
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void readProgramOffsetOffEndTest() {
    final byte[] exp = aProgram;
    final ProgramHandle hProg = ProgramHandle.read(exp, exp.length, exp.length);
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void readProgramOffsetTooLargeTest() {
    final byte[] exp = aProgram;
    final ProgramHandle hProg = ProgramHandle.read(exp, 1, exp.length);
  }

  @Test
  public void createContextGoodTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          assertNotNull(hCtx);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noResetAfterDestroyContextTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        hCtx.destroy();
        hCtx.reset();
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  private static class DummyCallback implements HitCallback {
    public void callback(SearchHit hit) {}
  } 

  @Test(expected=IllegalStateException.class)
  public void noSearchAfterDestroyContextTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        hCtx.destroy();

        final byte[] buf = "a".getBytes("ASCII");
        final HitCallback cb = new DummyCallback();

        hCtx.search(buf, 0, buf.length, 0, cb);
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noCloseoutSearchAfterDestroyContextTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        hCtx.destroy();

        final HitCallback cb = new DummyCallback();
        hCtx.closeoutSearch(cb);
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noStartsWithAfterDestroyContextTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        hCtx.destroy();

        final byte[] buf = "a".getBytes("ASCII");
        final HitCallback cb = new DummyCallback();

        hCtx.startsWith(buf, 0, buf.length, 0, cb);
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=NullPointerException.class)
  public void createContextNullOptionsTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final ContextHandle hCtx = hProg.createContext(null);
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test
  public void resetContextTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("meh", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          hCtx.reset();
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  private static class HitCollector implements HitCallback {
    public HitCollector(List<SearchHit> l) {
      hits = l;
    }

    public void callback(SearchHit hit) {
      hits.add(hit);
    }

    private final List<SearchHit> hits;
  }

  @Test
  public void searchNoHitsTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("WMD", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "Iraq".getBytes("ASCII");
  
          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          final int ret = hCtx.search(buf, 0, buf.length, 0, cb);
          assertEquals(0, ret);

          hCtx.closeoutSearch(cb);
          assertEquals(0, hits.size());
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test
  public void searchHitsTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("a+b", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");
 
          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          final int ret = hCtx.search(buf, 0, buf.length, 0, cb);
          assertEquals(0, ret);

          hCtx.closeoutSearch(cb);

          assertEquals(3, hits.size());
          assertEquals(new SearchHit(0, 4, 0), hits.get(0));
          assertEquals(new SearchHit(7, 9, 0), hits.get(1));
          assertEquals(new SearchHit(10, 12, 0), hits.get(2));
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=NullPointerException.class)
  public void searchNullBufferTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("a+b", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.search(null, 0, 0, 0, cb);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void searchNegativeOffsetTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("a+b", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");

          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.search(buf, -1, buf.length, 0, cb);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void searchNegativeSizeTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("a+b", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");

          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.search(buf, 0, -1, 0, cb);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void searchOffsetOffEndTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("a+b", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");

          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.search(buf, buf.length, buf.length, 0, cb);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void searchOffsetTooLargeTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("a+b", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");

          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.search(buf, 1, buf.length, 0, cb);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void searchNegativeStartOffsetTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("a+b", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");

          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.search(buf, 0, buf.length, -1, cb);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=NullPointerException.class)
  public void searchNullCallbackTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("a+b", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");

          hCtx.search(buf, 0, buf.length, 0, null);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  private static class CallbackExploder implements HitCallback {
    public void callback(SearchHit hit) {
      throw new RuntimeException("Out of cheese");
    }
  }

  @Test(expected=RuntimeException.class)
  public void searchBadCallbackTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("a+b", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");

          hCtx.search(buf, 0, buf.length, 0, new CallbackExploder());
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test
  public void startsWithNoHitsTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("x+", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "yyyy".getBytes("ASCII");
  
          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.startsWith(buf, 0, buf.length, 0, cb);
          assertEquals(0, hits.size());
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test
  public void startsWithHitsTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("x+", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        final ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "xxxx".getBytes("ASCII");
  
          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);
          hCtx.startsWith(buf, 0, buf.length, 0, cb);

          assertEquals(1, hits.size());
          assertEquals(new SearchHit(0, 4, 0), hits.get(0));
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=NullPointerException.class)
  public void startsWithNullBufferTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("x+", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.startsWith(null, 0, 0, 0, cb);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void startsWithNegativeOffsetTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("x+", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "xxxx".getBytes("ASCII");

          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.startsWith(buf, -1, buf.length, 0, cb);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void startsWithNegativeSizeTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("x+", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "xxxx".getBytes("ASCII");

          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.startsWith(buf, 0, -1, 0, cb);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void startsWithOffsetOffEndTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("x+", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "xxxx".getBytes("ASCII");

          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.startsWith(buf, buf.length, buf.length, 0, cb);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void startsWithOffsetTooLargeTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("x+", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "xxxx".getBytes("ASCII");

          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.startsWith(buf, 1, buf.length, 0, cb);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void startsWithNegativeStartOffsetTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("x+", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "xxxx".getBytes("ASCII");

          final List<SearchHit> hits = new ArrayList<SearchHit>();
          final HitCallback cb = new HitCollector(hits);

          hCtx.startsWith(buf, 0, buf.length, -1, cb);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }

  @Test(expected=NullPointerException.class)
  public void startsWithNullCallbackTest() throws Exception {
    final ParserHandle hParser = new ParserHandle(4);
    try {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      hParser.addKeyword("x+", 0, kopts, "ASCII");

      final ProgramOptions popts = new ProgramOptions();
      popts.Determinize = true;        

      final ProgramHandle hProg = hParser.createProgram(popts);
      try {
        ContextOptions copts = new ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
        copts.TraceBegin = Long.MIN_VALUE;
        copts.TraceEnd = Long.MIN_VALUE;

        final ContextHandle hCtx = hProg.createContext(copts);
        try {
          final byte[] buf = "xxxx".getBytes("ASCII");

          hCtx.startsWith(buf, 0, buf.length, 0, null);
        }
        finally {
          hCtx.destroy();
        }
      }
      finally {
        hProg.destroy();
      }
    }
    finally {
      hParser.destroy();
    }
  }
}
