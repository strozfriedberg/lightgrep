package com.lightboxtechnologies.lightgrep;

import org.junit.Test;

import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import com.lightboxtechnologies.lightgrep.Lightgrep.Callback;
import com.lightboxtechnologies.lightgrep.Lightgrep.ContextHandle;
import com.lightboxtechnologies.lightgrep.Lightgrep.ParserHandle;
import com.lightboxtechnologies.lightgrep.Lightgrep.ProgramHandle;
import com.lightboxtechnologies.lightgrep.Lightgrep.LG_ContextOptions;
import com.lightboxtechnologies.lightgrep.Lightgrep.LG_KeyOptions;
import com.lightboxtechnologies.lightgrep.Lightgrep.LG_ProgramOptions;
import com.lightboxtechnologies.lightgrep.Lightgrep.LG_SearchHit;

public class LightgrepTest {
  @Test
  public void createDestroyParserTest() {
    ParserHandle hParser = null;
    try {
      hParser = Lightgrep.lg_create_parser(1);
      assertNotNull(hParser);
      assertTrue(Lightgrep.lg_ok(hParser) != 0);
    }
    finally {
      Lightgrep.lg_destroy_parser(hParser);
    }
  }

  @Test
  public void addKeywordTest() {
    ParserHandle hParser = null;
    try {
      hParser = Lightgrep.lg_create_parser(4);

      final LG_KeyOptions kopts = new LG_KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      final int ret = Lightgrep.lg_add_keyword(
        hParser, "meh", 0, kopts, "ASCII"
      );
      assertTrue(ret != 0);
    }
    finally {
      Lightgrep.lg_destroy_parser(hParser);
    }
  }

  @Test
  public void createEmptyProgramTest() {
    ParserHandle hParser = null;
    try {
      hParser = Lightgrep.lg_create_parser(1);
      ProgramHandle hProg = null;
      try {
        LG_ProgramOptions popts = new LG_ProgramOptions();
        popts.Determinize = true;        

        hProg = Lightgrep.lg_create_program(hParser, popts);
        assertNotNull(hProg);
        assertTrue(Lightgrep.lg_ok(hProg) == 0);
      }
      finally {
        Lightgrep.lg_destroy_program(hProg);
      }
    }
    finally {
      Lightgrep.lg_destroy_parser(hParser);
    }
  }

  @Test
  public void createProgramTest() {
    ParserHandle hParser = null;
    try {
      hParser = Lightgrep.lg_create_parser(4);

      final LG_KeyOptions kopts = new LG_KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      final int ret = Lightgrep.lg_add_keyword(
        hParser, "meh", 0, kopts, "ASCII"
      );

      ProgramHandle hProg = null;
      try {
        LG_ProgramOptions popts = new LG_ProgramOptions();
        popts.Determinize = true;        
        hProg = Lightgrep.lg_create_program(hParser, popts);
        assertNotNull(hProg);
        assertTrue(Lightgrep.lg_ok(hProg) != 0);
      }
      finally {
        Lightgrep.lg_destroy_program(hProg);
      }
    }
    finally {
      Lightgrep.lg_destroy_parser(hParser);
    }
  }

  @Test
  public void writeProgramTest() {
    ParserHandle hParser = null;
    try {
      hParser = Lightgrep.lg_create_parser(4);

      final LG_KeyOptions kopts = new LG_KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      final int ret = Lightgrep.lg_add_keyword(
        hParser, "meh", 0, kopts, "ASCII"
      );

      ProgramHandle hProg = null;
      try {
        LG_ProgramOptions popts = new LG_ProgramOptions();
        popts.Determinize = true;        
        hProg = Lightgrep.lg_create_program(hParser, popts);

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

        final int size = Lightgrep.lg_program_size(hProg);
        assertEquals(exp.length, size);

        final byte[] buf = new byte[size];
        Lightgrep.lg_write_program(hProg, buf, 0);

        assertArrayEquals(exp, buf);
      }
      finally {
        Lightgrep.lg_destroy_program(hProg);
      }
    }
    finally {
      Lightgrep.lg_destroy_parser(hParser);
    } 
  }

  @Test
  public void readWriteProgramTest() {
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

    ProgramHandle hProg = null;
    try {
      hProg = Lightgrep.lg_read_program(exp, 0, exp.length);

      final int size = Lightgrep.lg_program_size(hProg);
      assertEquals(exp.length, size);

      final byte[] buf = new byte[size];
      Lightgrep.lg_write_program(hProg, buf, 0);

      assertArrayEquals(exp, buf);
    }
    finally {
      Lightgrep.lg_destroy_program(hProg);
    }
  }

  @Test
  public void createContextTest() {
    ParserHandle hParser = null;
    try {
      hParser = Lightgrep.lg_create_parser(4);

      final LG_KeyOptions kopts = new LG_KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      final int ret = Lightgrep.lg_add_keyword(
        hParser, "meh", 0, kopts, "ASCII"
      );

      ProgramHandle hProg = null;
      try {
        LG_ProgramOptions popts = new LG_ProgramOptions();
        popts.Determinize = true;        
        hProg = Lightgrep.lg_create_program(hParser, popts);

        ContextHandle hCtx = null;
        try {
          LG_ContextOptions copts = new LG_ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
          copts.TraceBegin = Long.MIN_VALUE;
          copts.TraceEnd = Long.MIN_VALUE;

          hCtx = Lightgrep.lg_create_context(hProg, copts);
          assertNotNull(hCtx);
          assertTrue(Lightgrep.lg_ok(hCtx) != 0);
        }
        finally {
          Lightgrep.lg_destroy_context(hCtx);
        }
      }
      finally {
        Lightgrep.lg_destroy_program(hProg);
      }
    }
    finally {
      Lightgrep.lg_destroy_parser(hParser);
    }
  }

  private static class HitCollector implements Callback {
    public HitCollector(List<LG_SearchHit> l) {
      hits = l;
    }

    public void callback(LG_SearchHit hit) {
      hits.add(hit);
    }

    private final List<LG_SearchHit> hits;
  }

  @Test
  public void searchNoHitsTest() throws UnsupportedEncodingException {
    ParserHandle hParser = null;
    try {
      hParser = Lightgrep.lg_create_parser(4);

      final LG_KeyOptions kopts = new LG_KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      if (Lightgrep.lg_add_keyword(hParser, "WMD", 0, kopts, "ASCII") == 0) {
        throw new IllegalArgumentException();
      }

      ProgramHandle hProg = null;
      try {
        LG_ProgramOptions popts = new LG_ProgramOptions();
        popts.Determinize = true;        
        hProg = Lightgrep.lg_create_program(hParser, popts);

        ContextHandle hCtx = null;
        try {
          LG_ContextOptions copts = new LG_ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
          copts.TraceBegin = Long.MIN_VALUE;
          copts.TraceEnd = Long.MIN_VALUE;

          hCtx = Lightgrep.lg_create_context(hProg, copts);

          final byte[] buf = "Iraq".getBytes("ASCII");
  
          final List<LG_SearchHit> hits = new ArrayList<LG_SearchHit>();
          final Callback cb = new HitCollector(hits);
          final int ret = Lightgrep.lg_search(hCtx, buf, 0, buf.length, 0, cb);

          assertEquals(0, ret);

          Lightgrep.lg_closeout_search(hCtx, cb);

          assertEquals(0, hits.size());
        }
        finally {
          Lightgrep.lg_destroy_context(hCtx);
        }
      }
      finally {
        Lightgrep.lg_destroy_program(hProg);
      }
    }
    finally {
      Lightgrep.lg_destroy_parser(hParser);
    }
  }
  
  @Test
  public void searchHitsTest() throws UnsupportedEncodingException {
    ParserHandle hParser = null;
    try {
      hParser = Lightgrep.lg_create_parser(4);

      final LG_KeyOptions kopts = new LG_KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      if (Lightgrep.lg_add_keyword(hParser, "a+b", 0, kopts, "ASCII") == 0) {
        throw new IllegalArgumentException();
      }

      ProgramHandle hProg = null;
      try {
        LG_ProgramOptions popts = new LG_ProgramOptions();
        popts.Determinize = true;
        hProg = Lightgrep.lg_create_program(hParser, popts);

        ContextHandle hCtx = null;
        try {
          LG_ContextOptions copts = new LG_ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
          copts.TraceBegin = Long.MIN_VALUE;
          copts.TraceEnd = Long.MIN_VALUE;

          hCtx = Lightgrep.lg_create_context(hProg, copts);

          final byte[] buf = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");
  
          final List<LG_SearchHit> hits = new ArrayList<LG_SearchHit>();
          final Callback cb = new HitCollector(hits);
          final int ret = Lightgrep.lg_search(hCtx, buf, 0, buf.length, 0, cb);

          assertEquals(0, ret);

          Lightgrep.lg_closeout_search(hCtx, cb);

          assertEquals(3, hits.size());
          assertEquals(new LG_SearchHit(0, 4, 0), hits.get(0));
          assertEquals(new LG_SearchHit(7, 9, 0), hits.get(1));
          assertEquals(new LG_SearchHit(10, 12, 0), hits.get(2));
        }
        finally {
          Lightgrep.lg_destroy_context(hCtx);
        }
      }
      finally {
        Lightgrep.lg_destroy_program(hProg);
      }
    }
    finally {
      Lightgrep.lg_destroy_parser(hParser);
    }
  }

  @Test
  public void startsWithNoHitsTest() throws UnsupportedEncodingException {
    ParserHandle hParser = null;
    try {
      hParser = Lightgrep.lg_create_parser(4);

      final LG_KeyOptions kopts = new LG_KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      if (Lightgrep.lg_add_keyword(hParser, "x+", 0, kopts, "ASCII") == 0) {
        throw new IllegalArgumentException();
      }

      ProgramHandle hProg = null;
      try {
        LG_ProgramOptions popts = new LG_ProgramOptions();
        popts.Determinize = true;        
        hProg = Lightgrep.lg_create_program(hParser, popts);

        ContextHandle hCtx = null;
        try {
          LG_ContextOptions copts = new LG_ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
          copts.TraceBegin = Long.MIN_VALUE;
          copts.TraceEnd = Long.MIN_VALUE;

          hCtx = Lightgrep.lg_create_context(hProg, copts);

          final byte[] buf = "yyyy".getBytes("ASCII");
  
          final List<LG_SearchHit> hits = new ArrayList<LG_SearchHit>();
          final Callback cb = new HitCollector(hits);
          Lightgrep.lg_starts_with(hCtx, buf, 0, buf.length, 0, cb);

          assertEquals(0, hits.size());
        }
        finally {
          Lightgrep.lg_destroy_context(hCtx);
        }
      }
      finally {
        Lightgrep.lg_destroy_program(hProg);
      }
    }
    finally {
      Lightgrep.lg_destroy_parser(hParser);
    }
  }

  @Test
  public void startsWithHitsTest() throws UnsupportedEncodingException {
    ParserHandle hParser = null;
    try {
      hParser = Lightgrep.lg_create_parser(4);

      final LG_KeyOptions kopts = new LG_KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;

      if (Lightgrep.lg_add_keyword(hParser, "x+", 0, kopts, "ASCII") == 0) {
        throw new IllegalArgumentException();
      }

      ProgramHandle hProg = null;
      try {
        LG_ProgramOptions popts = new LG_ProgramOptions();
        popts.Determinize = true;        
        hProg = Lightgrep.lg_create_program(hParser, popts);

        ContextHandle hCtx = null;
        try {
          LG_ContextOptions copts = new LG_ContextOptions();
// FIXME: scary, do these become 2^64-1 when cast to unit64?
          copts.TraceBegin = Long.MIN_VALUE;
          copts.TraceEnd = Long.MIN_VALUE;

          hCtx = Lightgrep.lg_create_context(hProg, copts);

          final byte[] buf = "xxxx".getBytes("ASCII");
  
          final List<LG_SearchHit> hits = new ArrayList<LG_SearchHit>();
          final Callback cb = new HitCollector(hits);
          Lightgrep.lg_starts_with(hCtx, buf, 0, buf.length, 0, cb);

          assertEquals(1, hits.size());
          assertEquals(new LG_SearchHit(0, 4, 0), hits.get(0));
        }
        finally {
          Lightgrep.lg_destroy_context(hCtx);
        }
      }
      finally {
        Lightgrep.lg_destroy_program(hProg);
      }
    }
    finally {
      Lightgrep.lg_destroy_parser(hParser);
    }
  }
}
