package com.lightboxtechnologies.lightgrep;

import org.junit.Test;

import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

public class LightgrepTest {
  @Test
  public void createDestroyPatternTest() {
    try (final PatternHandle hPattern = new PatternHandle()) {
      assertNotNull(hPattern);
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noParsePatternAfterDestroyPatternTest() throws Exception {
    final PatternHandle hPattern = new PatternHandle();
    hPattern.destroy();

    final KeyOptions kopts = new KeyOptions();
    kopts.FixedString = false;
    kopts.CaseInsensitive = false;
    kopts.UnicodeMode = false;

    hPattern.parsePattern("meh", kopts);
  }

  @Test
  public void doubleDestroyPatternTest() {
    final PatternHandle hPattern = new PatternHandle();
    hPattern.destroy();
    hPattern.destroy();
  }

  @Test
  public void parsePatternGoodTest() throws Exception {
    try (final PatternHandle hPattern = new PatternHandle()) {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;
      kopts.UnicodeMode = false;

      final int ret = hPattern.parsePattern("meh", kopts);
      assertTrue(ret != 0);
    }
  }

  @Test(expected=KeywordException.class)
  public void parsePatternMalformedTest() throws Exception {
    try (final PatternHandle hPattern = new PatternHandle()) {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;
      kopts.UnicodeMode = false;

      hPattern.parsePattern("(xyz", kopts);
    }
  }

  @Test(expected=NullPointerException.class)
  public void parsePatternNullTest() throws Exception {
    try (final PatternHandle hPattern = new PatternHandle()) {
      final KeyOptions kopts = new KeyOptions();
      kopts.FixedString = false;
      kopts.CaseInsensitive = false;
      kopts.UnicodeMode = false;

      hPattern.parsePattern(null, kopts);
    }
  }

  @Test(expected=NullPointerException.class)
  public void parsePatternNullOptionsTest() throws Exception {
    try (final PatternHandle hPattern = new PatternHandle()) {
      hPattern.parsePattern("meh", null);
    }
  }

  @Test
  public void createDestroyProgramTest() {
    try (final ProgramHandle hProg = new ProgramHandle(0)) {
      assertNotNull(hProg);
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void createProgramNegativeSizeHintTest() throws Exception {
    final ProgramHandle hProg = new ProgramHandle(-1);
    hProg.destroy();
  }

  @Test(expected=IllegalStateException.class)
  public void noSizeAfterDestroyProgramTest() throws Exception {
    final ProgramHandle hProg = new ProgramHandle(0);
    hProg.destroy();
    hProg.size();
  }

  @Test(expected=IllegalStateException.class)
  public void noGetPatternInfoAfterDestroyProgramTest() throws Exception {
    final ProgramHandle hProg = new ProgramHandle(0);
    hProg.destroy();
    hProg.getPatternInfo(0);
  }

  @Test(expected=IllegalStateException.class)
  public void noGetUserIndexAfterDestroyProgramTest() throws Exception {
    final ProgramHandle hProg = new ProgramHandle(0);
    hProg.destroy();
    hProg.getUserIndex(0);
  }

  @Test(expected=IllegalStateException.class)
  public void noSetUserIndexAfterDestroyProgramTest() throws Exception {
    final ProgramHandle hProg = new ProgramHandle(0);
    hProg.destroy();
    hProg.setUserIndex(0, 5);
  }

  @Test
  public void createDestroyFSMTest() {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      assertNotNull(hFsm);
    }
  }

  @Test
  public void doubleDestroyFSMTest() {
    final FSMHandle hFsm = new FSMHandle(0, 0);
    hFsm.destroy();
    hFsm.destroy();
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void createFSMNegativePatternCountHintTest() throws Exception {
    final FSMHandle hFsm = new FSMHandle(-1, 0);
    hFsm.destroy();
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void createFSMNegativeSizeHintTest() throws Exception {
    final FSMHandle hFsm = new FSMHandle(0, -1);
    hFsm.destroy();
  }

  @Test(expected=IllegalStateException.class)
  public void noAddPatternAfterDestroyFSMTest() throws Exception {
    final FSMHandle hFsm = new FSMHandle(0, 0);
    hFsm.destroy();

    try (final PatternHandle hPattern = new PatternHandle()) {
      hFsm.addPattern(hPattern, "ASCII", 0);
    }
  }

  @Test(expected=NullPointerException.class)
  public void addPatternNullPatternTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      hFsm.addPattern(null, "ASCII", 0);
    }
  }

  @Test(expected=NullPointerException.class)
  public void addPatternNullEncodingTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        hFsm.addPattern(hPattern, null, 0);
      }
    }
  }

  @Test
  public void zeroPatternsFSMCountTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      assertEquals(0, hFsm.count());
    }
  }

  @Test
  public void onePatternFSMCountTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        hPattern.parsePattern("bob", new KeyOptions());
        hFsm.addPattern(hPattern, "UTF-8", 0);
      }
      assertEquals(1, hFsm.count());
    }
  }

  @Test
  public void twoPatternFSMCountTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        hPattern.parsePattern("bob", new KeyOptions());
        hFsm.addPattern(hPattern, "UTF-8", 0);
        hFsm.addPattern(hPattern, "UTF-8", 1);
      }
      assertEquals(2, hFsm.count());
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noCountAfterDestroyFSMTest() throws Exception {
    final FSMHandle hFsm = new FSMHandle(0, 0);
    hFsm.destroy();
    hFsm.count();
  }

// FIMXE: Shouldn't this throw something?
/*
  @Test
  public void addPatternEmptyTest() throws Exception {
    final FSMHandle hFsm = new FSMHandle(0, 0);
    try {
      final ProgramHandle hProg = new ProgramHandle(0);
      try {
        final PatternHandle hPattern = new PatternHandle();
        try {
          hFsm.addPattern(hPattern, "UTF-8");
        }
        finally {
          hPattern.destroy();
        }
      }
      finally {
        hPatternMap.destroy();
      }
    }
    finally {
      hFsm.destroy();
    }
  }
*/

  @Test
  public void addPatternGoodTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("(xyzzy)+", kopts);
        final int ret = hFsm.addPattern(hPattern, "UTF-8", 0);
        assertEquals(0, ret);
      }
    }
  }

  @Test(expected=KeywordException.class)
  public void addPatternEmptyMatchesTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("x*", kopts);
        hFsm.addPattern(hPattern, "UTF-8", 0);
      }
    }
  }

// FIXME: should throw some sort of encoding exception?
  @Test(expected=KeywordException.class)
  public void addPatternBadEncodingTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("meh", kopts);
        hFsm.addPattern(hPattern, "UTF-13", 0);
      }
    }
  }

  @Test(expected=IllegalStateException.class)
  public void countEmptyProgramTest() throws Exception {
    try (final ProgramHandle hProg = new ProgramHandle(0)) {
      assertEquals(0, hProg.count());
    }
  }

  @Test
  public void countNonEmptyProgramTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("(xyzzy)+", kopts);
        hFsm.addPattern(hPattern, "UTF-8", 0);
      }

      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        hProg.compile(hFsm, new ProgramOptions());
        assertEquals(1, hProg.count());
      }
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void getFSMPatternInfoNegativeIndexTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      hFsm.getPatternInfo(-1);
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void getFSMPatternInfoIndexTooLargeTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      hFsm.getPatternInfo(42);
    }
  }

  @Test
  public void getFSMPatternInfoIndexJustRightTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        final PatternInfo exp = new PatternInfo(
          "(xyzzy)+", "UTF-8", 42
        );

        hPattern.parsePattern(exp.Pattern, kopts);
        hFsm.addPattern(hPattern, exp.EncodingChain, 42);

        final PatternInfo act = hFsm.getPatternInfo(0);
        assertEquals(exp, act);
      }
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void setFSMUserIndexNegativeIndexTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      hFsm.setUserIndex(-1, 1);
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void setFSMUserIndexIndexTooLargeTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      hFsm.setUserIndex(42, 1);
    }
  }

  @Test
  public void setFSMUserIndexGetUserIndexProgramTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("(xyzzy)+", kopts);
        hFsm.addPattern(hPattern, "UTF-8", 0);

        hFsm.setUserIndex(0, 42);
        assertEquals(42, hFsm.getUserIndex(0));
      }
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void getProgramPatternInfoNegativeIndexTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("foo", kopts);
        hFsm.addPattern(hPattern, "UTF-8", 0);

        try (final ProgramHandle hProg = new ProgramHandle(0)) {
          hProg.compile(hFsm, new ProgramOptions());
          hProg.getPatternInfo(-1);
        }
      }
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void getProgramPatternInfoIndexTooLargeTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("foo", kopts);
        hFsm.addPattern(hPattern, "UTF-8", 0);

        try (final ProgramHandle hProg = new ProgramHandle(0)) {
          hProg.compile(hFsm, new ProgramOptions());
          hProg.getPatternInfo(42);
        }
      }
    }
  }

  @Test
  public void getProgramPatternInfoIndexJustRightTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        final PatternInfo exp = new PatternInfo(
          "(xyzzy)+", "UTF-8", 42
        );

        hPattern.parsePattern(exp.Pattern, kopts);
        hFsm.addPattern(hPattern, exp.EncodingChain, 42);

        try (final ProgramHandle hProg = new ProgramHandle(0)) {
          hProg.compile(hFsm, new ProgramOptions());
          final PatternInfo act = hProg.getPatternInfo(0);
          assertEquals(exp, act);
        }
      }
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void getProgramUserIndexNegativeIndexTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("foo", kopts);
        hFsm.addPattern(hPattern, "UTF-8", 0);

        try (final ProgramHandle hProg = new ProgramHandle(0)) {
          hProg.compile(hFsm, new ProgramOptions());
          hProg.getUserIndex(-1);
        }
      }
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void getProgramUserIndexIndexTooLargeTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("foo", kopts);
        hFsm.addPattern(hPattern, "UTF-8", 0);

        try (final ProgramHandle hProg = new ProgramHandle(0)) {
          hProg.compile(hFsm, new ProgramOptions());
          hProg.getUserIndex(42);
        }
      }
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void setProgramUserIndexNegativeIndexTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("foo", kopts);
        hFsm.addPattern(hPattern, "UTF-8", 0);

        try (final ProgramHandle hProg = new ProgramHandle(0)) {
          hProg.compile(hFsm, new ProgramOptions());
          hProg.setUserIndex(-1, 1);
        }
      }
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void setProgramUserIndexIndexTooLargeTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("foo", kopts);
        hFsm.addPattern(hPattern, "UTF-8", 0);

        try (final ProgramHandle hProg = new ProgramHandle(0)) {
          hProg.compile(hFsm, new ProgramOptions());
          hProg.setUserIndex(42, 1);
        }
      }
    }
  }

  @Test
  public void setProgramUserIndexGetUserIndexProgramTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("(xyzzy)+", kopts);
        hFsm.addPattern(hPattern, "UTF-8", 0);

        try (final ProgramHandle hProg = new ProgramHandle(0)) {
          hProg.compile(hFsm, new ProgramOptions());
          hProg.setUserIndex(0, 42);
          assertEquals(42, hProg.getUserIndex(0));
        }
      }
    }
  }

  @Test(expected=NullPointerException.class)
  public void compileNullFsmTest() throws Exception {
    try (final ProgramHandle hProg = new ProgramHandle(0)) {
      hProg.compile(null, new ProgramOptions());
    }
  }

  @Test(expected=NullPointerException.class)
  public void compileNullOptionsTest() throws Exception {
    try (final ProgramHandle hProg = new ProgramHandle(0)) {
      try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
        hProg.compile(hFsm, null);
      }
    }
  }

  @Test(expected=ProgramException.class)
  public void compileEmptyTest() throws Exception {
    try (final ProgramHandle hProg = new ProgramHandle(0)) {
      try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
        hProg.compile(hFsm, new ProgramOptions());
      }
    }
  }

  @Test
  public void compileProgramGoodTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("(xyzzy)+", kopts);
          hFsm.addPattern(hPattern, "UTF-8", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          assertTrue(hProg.compile(hFsm, popts) > 0);
        }
      }
    }
  }

  @Test(expected=ProgramException.class)
  public void doubleCompileProgramTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("(xyzzy)+", kopts);
        hFsm.addPattern(hPattern, "UTF-8", 0);
      }

      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        final ProgramOptions popts = new ProgramOptions();
        hProg.compile(hFsm, popts);
        hProg.compile(hFsm, popts);
      }
    }
  }

  @Test
  public void doubleDestroyProgramTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final PatternHandle hPattern = new PatternHandle()) {
        final KeyOptions kopts = new KeyOptions();
        kopts.FixedString = false;
        kopts.CaseInsensitive = false;
        kopts.UnicodeMode = false;

        hPattern.parsePattern("(xyzzy)+", kopts);
        hFsm.addPattern(hPattern, "UTF-8", 0);
      }

      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        final ProgramOptions popts = new ProgramOptions();
        popts.Determinize = true;

        hProg.compile(hFsm, popts);
        hProg.destroy();
        hProg.destroy();
      }
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noWriteAfterDestroyProgramTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("(xyzzy)+", kopts);
          hFsm.addPattern(hPattern, "UTF-8", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);
          final byte[] buf = new byte[hProg.size()];
          hProg.destroy();

          hProg.write(buf, 0);
        }
      }
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noCreateContextAfterDestroyProgramTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("(xyzzy)+", kopts);
          hFsm.addPattern(hPattern, "UTF-8", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);
          hProg.destroy();

          final ContextOptions copts = new ContextOptions();
          hProg.createContext(copts);
        }
      }
    }
  }

// FIXME: output is not the same as it was, get new output
/*
  @Test(expected=IllegalStateException.class)
  public void writeProgramGoodTest() throws Exception {
    final FSMHandle hFsm = new FSMHandle(0, 0);
    try {
      final ProgramHandle hProg = new ProgramHandle(0);
      try {
        final PatternHandle hPattern = new PatternHandle();
        try {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII");

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          final ProgramHandle hProg = hFsm.createProgram(popts);
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
          hPattern.destroy();
        }
      }
      finally {
        hPatternMap.destroy();
      }
    }
    finally {
      hFsm.destroy();
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
*/

  @Test(expected=NullPointerException.class)
  public void writeProgramNullBufferTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);
          hProg.write(null, 0);
        }
      }
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void writeProgramNegativeOffsetTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);
          final byte[] buf = new byte[hProg.size()];
          hProg.write(buf, -1);
        }
      }
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void writeProgramOffsetOffEndTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);
          final byte[] buf = new byte[hProg.size()];
          hProg.write(buf, buf.length);
        }
      }
    }
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void writeProgramOffsetTooLargeTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);
          final byte[] buf = new byte[hProg.size()];
          hProg.write(buf, 1);
        }
      }
    }
  }

/*
  @Test
  public void writeReadProgramGoodTest() throws Exception {
    final ProgramHandle hProg1 = new ProgramHandle(0);
    try {
      final FSMHandle hFsm = new FSMHandle(0, 0);
      try {
        final PatternHandle hPattern = new PatternHandle();
        try {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;

          hPattern.parsePattern("a+b", kopts);
          hFsm.addPattern(hProg1, hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg1.compile(hFsm, popts);
        }
        finally {
          hPattern.destroy();
        }
      }
      finally {
        hFsm.destroy();
      }

      final int size = hProg1.size();
      final byte[] buf = new byte[size];
      hProg1.write(buf, 0);

      final ProgramHandle hProg2 = ProgramHandle.read(buf, 0, size);
      try {
        assertEquals(hProg1, hProg2);
      }
      finally {
        hProg2.destroy();
      }
    }
    finally {
      hProg1.destroy();
    }
  }
*/

  @Test(expected=NullPointerException.class)
  public void readProgramNullBufferTest() {
    final ProgramHandle hProg = ProgramHandle.read(null, 0, 1);
    hProg.destroy();
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void readProgramOffsetOffEndTest() {
    final byte[] exp = new byte[10];
    final ProgramHandle hProg = ProgramHandle.read(exp, exp.length, exp.length);
    hProg.destroy();
  }

  @Test(expected=IndexOutOfBoundsException.class)
  public void readProgramOffsetTooLargeTest() {
    final byte[] exp = new byte[10];
    final ProgramHandle hProg = ProgramHandle.read(exp, 1, exp.length);
    hProg.destroy();
  }

// FIXME: reading programs has no error-checking, pretty much
/*
  @Test(expected=ProgramException.class)
  public void readProgramGarbageTest() throws UnsupportedEncodingException {
    final byte[] ibuf = "balls balls balls balls balls balls".getBytes("ASCII");
    final ProgramHandle hProg = ProgramHandle.read(ibuf, 0, ibuf.length);
    final byte[] obuf = new byte[hProg.size()];
    hProg.write(obuf, 0);
    System.err.write(obuf, 0, obuf.length);
    hProg.destroy();
  }
*/

  @Test
  public void createContextGoodTest() throws Exception {
    try (final ProgramHandle hProg = new ProgramHandle(0)) {
      try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);
        }
      }

      final ContextOptions copts = new ContextOptions();
      try (final ContextHandle hCtx = hProg.createContext(copts)) {
        assertNotNull(hCtx);
      }
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noResetAfterDestroyContextTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);

          final ContextOptions copts = new ContextOptions();
          final ContextHandle hCtx = hProg.createContext(copts);
          hCtx.destroy();
          hCtx.reset();
        }
      }
    }
  }

  private static class DummyCallback implements HitCallback {
    public void callback(SearchHit hit) {}
  }

  @Test(expected=IllegalStateException.class)
  public void noSearchAfterDestroyContextTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);

          final ContextOptions copts = new ContextOptions();
          final ContextHandle hCtx = hProg.createContext(copts);
          hCtx.destroy();

          final byte[] buf = "a".getBytes("ASCII");
          final HitCallback cb = new DummyCallback();

          hCtx.search(buf, 0, buf.length, 0, cb);
        }
      }
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noCloseoutSearchAfterDestroyContextTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);

          final ContextOptions copts = new ContextOptions();
          final ContextHandle hCtx = hProg.createContext(copts);
          hCtx.destroy();

          final HitCallback cb = new DummyCallback();
          hCtx.closeoutSearch(cb);
        }
      }
    }
  }

  @Test(expected=IllegalStateException.class)
  public void noStartsWithAfterDestroyContextTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);

          final ContextOptions copts = new ContextOptions();
          final ContextHandle hCtx = hProg.createContext(copts);
          hCtx.destroy();

          final byte[] buf = "a".getBytes("ASCII");
          final HitCallback cb = new DummyCallback();

          hCtx.startsWith(buf, 0, buf.length, 0, cb);
        }
      }
    }
  }

  @Test
  public void doubleDestroyContextTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);

          final ContextOptions copts = new ContextOptions();
          final ContextHandle hCtx = hProg.createContext(copts);
          hCtx.destroy();
          hCtx.destroy();
        }
      }
    }
  }

  @Test(expected=NullPointerException.class)
  public void createContextNullOptionsTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);
          hProg.createContext(null);
        }
      }
    }
  }

  @Test
  public void resetContextTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("meh", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);

          final ContextOptions copts = new ContextOptions();
          try (final ContextHandle hCtx = hProg.createContext(copts)) {
            hCtx.reset();
// FIXME: test that we're now at the beginning for new input
          }
        }
      }
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

  @Test(expected=NullPointerException.class)
  public void searchArrayNullCallbackTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("a+b", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);

          final byte[] buf = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");
          final ContextOptions copts = new ContextOptions();
          try (final ContextHandle hCtx = hProg.createContext(copts)) {
            hCtx.search(buf, 0, buf.length, 0, null);
          }
        }
      }
    }
  }

  private static class CallbackExploder implements HitCallback {
    public void callback(SearchHit hit) {
      throw new RuntimeException("Out of cheese");
    }
  }

  @Test(expected=RuntimeException.class)
  public void searchArrayBadCallbackTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("a+b", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);

          final byte[] buf = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");
          final ContextOptions copts = new ContextOptions();
          try (final ContextHandle hCtx = hProg.createContext(copts)) {
            hCtx.search(buf, 0, buf.length, 0, new CallbackExploder());
          }
        }
      }
    }
  }

  @Test(expected=NullPointerException.class)
  public void searchDirectByteBufferNullCallbackTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("a+b", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);

          final byte[] arr = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");
          final ByteBuffer buf = ByteBuffer.allocateDirect(arr.length);
          buf.put(arr).flip();

          final ContextOptions copts = new ContextOptions();
          try (final ContextHandle hCtx = hProg.createContext(copts)) {
            hCtx.search(buf, arr.length, 0, null);
          }
        }
      }
    }
  }

  @Test(expected=RuntimeException.class)
  public void searchDirectByteBufferBadCallbackTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("a+b", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);

          final byte[] arr = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");
          final ByteBuffer buf = ByteBuffer.allocateDirect(arr.length);
          buf.put(arr).flip();

          final ContextOptions copts = new ContextOptions();
          try (final ContextHandle hCtx = hProg.createContext(copts)) {
            hCtx.search(buf, arr.length, 0, new CallbackExploder());
          }
        }
      }
    }
  }

  @Test(expected=NullPointerException.class)
  public void searchWrappedByteBufferNullCallbackTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("a+b", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);

          final byte[] arr = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");
          final ByteBuffer buf = ByteBuffer.wrap(arr);

          final ContextOptions copts = new ContextOptions();
          try (final ContextHandle hCtx = hProg.createContext(copts)) {
            hCtx.search(buf, arr.length, 0, null);
          }
        }
      }
    }
  }

  @Test(expected=RuntimeException.class)
  public void searchWrappedByteBufferBadCallbackTest() throws Exception {
    try (final FSMHandle hFsm = new FSMHandle(0, 0)) {
      try (final ProgramHandle hProg = new ProgramHandle(0)) {
        try (final PatternHandle hPattern = new PatternHandle()) {
          final KeyOptions kopts = new KeyOptions();
          kopts.FixedString = false;
          kopts.CaseInsensitive = false;
          kopts.UnicodeMode = false;

          hPattern.parsePattern("a+b", kopts);
          hFsm.addPattern(hPattern, "ASCII", 0);

          final ProgramOptions popts = new ProgramOptions();
          popts.Determinize = true;

          hProg.compile(hFsm, popts);

          final byte[] arr = "aaabaacabbabcacbaccbbbcbccca".getBytes("ASCII");
          final ByteBuffer buf = ByteBuffer.wrap(arr);

          final ContextOptions copts = new ContextOptions();
          try (final ContextHandle hCtx = hProg.createContext(copts)) {
            hCtx.search(buf, arr.length, 0, new CallbackExploder());
          }
        }
      }
    }
  }

/*
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
        final ContextOptions copts = new ContextOptions();

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
*/
}
