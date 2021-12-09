#!/usr/bin/python3

import array
import ctypes
import mmap
import unittest

import lightgrep


PATLIST = [
    ("a+b", ['UTF-8', 'iso-8859-1'], lightgrep.KeyOpts(caseInsensitive=True)),
    ("a+b", ['UTF-8', 'iso-8859-1'], lightgrep.KeyOpts(fixedString=True))
]


def fuzz_args(arglist, subs):
    for i in range(0, len(arglist)):
        args = arglist.copy()
        for s in subs:
            args[i] = s
            yield args


def fuzz_it(testobj, func, arglist, subs):
    for args in fuzz_args(arglist, subs):
        with testobj.subTest(args=args):
            with testobj.assertRaises(Exception):
                func(*args)


class PointerTests(unittest.TestCase):
    sizes = (0, 1, 7, 8, 1024)
    buftypes = (
        bytes,
        bytearray,
        lambda n: array.array('b', [0]*n),
        lambda n: array.array('B', [0]*n)
    )

    def check_range(self, buf):
        # Is the range the right length?
        r_beg, r_end = lightgrep.buf_range(buf, ctypes.c_char)
        self.assertNotEqual(r_beg, 0)
        self.assertNotEqual(r_end, 0)
        self.assertEqual(ctypes.addressof(r_end)-ctypes.addressof(r_beg), len(buf))

        # Does buf_beg() == buf_range()[0]?
        beg = lightgrep.buf_beg(buf, ctypes.c_char)
        self.assertEqual(ctypes.addressof(beg), ctypes.addressof(r_beg))

        # Does buf_end() == buf_range()[1]?
        end = lightgrep.buf_end(buf, ctypes.c_char)
        self.assertEqual(ctypes.addressof(end), ctypes.addressof(r_end))

    def test_buf_range(self):
        for n in self.sizes:
            for buftype in self.buftypes:
                buf = buftype(n)
                with self.subTest(n=n, buf=buf):
                    self.check_range(buf)
                with self.subTest(n=n, buf=memoryview(buf)):
                    self.check_range(buf)

    def test_buf_range_mmap(self):
        with mmap.mmap(-1, 1024) as buf:
            self.check_range(buf)
            self.check_range(memoryview(buf))

    def test_buf_range_bad_args(self):
        arglist = [b'xxx', ctypes.c_char]
        subs = (None, '*', -1)
        fuzz_it(self, lightgrep.buf_range, arglist, subs)


class HandleTests(unittest.TestCase):
    def test_handle_open_good_closed_bad(self):
        h = lightgrep.Handle(42)
        self.assertTrue(h)
        self.assertEqual(h.handle, 42)
        h.close()
        self.assertFalse(h)
        self.assertEqual(h.handle, None)

    def test_throwIfClosed_open(self):
        h = lightgrep.Handle(42)
        h.throwIfClosed()

    def test_throwIfClosed_closed(self):
        h = lightgrep.Handle(42)
        h.close()
        with self.assertRaises(RuntimeError):
            h.throwIfClosed()

    def test_get_closed(self):
        h = lightgrep.Handle(42)
        h.close()
        with self.assertRaises(RuntimeError):
            h.get()

    def test_get_open(self):
        h = lightgrep.Handle(42)
        self.assertEqual(h.get(), 42)


class ErrorTests(unittest.TestCase):
    def test_close_unused(self):
        # test that closing an unused Error doesn't throw
        err = lightgrep.Error()
        err.close()


class KeyOptsTests(unittest.TestCase):
    def test_flags(self):
        for fixed_string in (False, True):
            for case_insensitive in (False, True):
                for unicode_mode in (False, True):
                    with self.subTest(fixed_string=fixed_string, case_insensitive=case_insensitive):
                        opts = lightgrep.KeyOpts(fixedString=fixed_string, caseInsensitive=case_insensitive, unicodeMode=unicode_mode)
                        self.assertEqual(opts.isFixed(), fixed_string)
                        self.assertEqual(opts.isCaseSensitive(), not case_insensitive)
                        self.assertEqual(opts.isUnicodeMode(), unicode_mode)


class PatternSimpleTests(unittest.TestCase):
    def test_close_unused(self):
        # test that closing an unused Pattern doesn't throw
        pat = lightgrep.Pattern()
        pat.close()


class PatternTests(unittest.TestCase):
    def setUp(self):
        self.pat = lightgrep.Pattern()
        self.addCleanup(self.pat.close)

    def test_pattern_good(self):
        self.pat.parse("a+b", lightgrep.KeyOpts())

    def test_parse_bad(self):
        with self.assertRaises(RuntimeError):
            self.pat.parse("+", lightgrep.KeyOpts())

    def test_parse_closed(self):
        self.pat.close()
        with self.assertRaises(RuntimeError):
            self.pat.parse("a", lightgrep.KeyOpts())

    def test_parse_bad_args(self):
        arglist = ["a", lightgrep.KeyOpts()]
        subs = (None, '*')
        fuzz_it(self, self.pat.parse, arglist, subs)


class FsmSimpleTests(unittest.TestCase):
    def test_ctor_bad_args(self):
        arglist = [0]
        subs = (None, '*', -1)
        fuzz_it(self, lightgrep.Fsm, arglist, subs)

    def test_close_unused(self):
        # test that closing an unused Fsm doesn't throw
        fsm = lightgrep.Fsm(0, 0)
        fsm.close()


class FsmTests(unittest.TestCase):
    def setUp(self):
        self.fsm = lightgrep.Fsm(0, 0)
        self.addCleanup(self.fsm.close)
        self.pat = lightgrep.Pattern()
        self.addCleanup(self.pat.close)

    def test_add_pattern_closed_pat(self):
        self.pat.parse("a+b", lightgrep.KeyOpts())
        self.pat.close()
        with self.assertRaises(RuntimeError):
            self.fsm.add_pattern(self.pat, 'UTF-8', 42)

    def test_add_pattern_bad_args(self):
        # fuzz add_pattern()
        self.pat.parse("a+b", lightgrep.KeyOpts())
        arglist = [self.pat, 'UTF-8', 42]
        subs = (None, 'bogus')
        fuzz_it(self, self.fsm.add_pattern, arglist, subs)

    def test_add_pattern_good(self):
        self.pat.parse("a+b", lightgrep.KeyOpts())
        idx = self.fsm.add_pattern(self.pat, 'UTF-8', 42)
        self.assertEqual(idx, 0)

    def test_add_patterns_bad_args(self):
        # fuzz add_patterns()
        arglist = [self.pat, PATLIST]
        subs = (None, 'bogus')
        fuzz_it(self, self.fsm.add_patterns, arglist, subs)

    def test_add_patterns(self):
        self.fsm.add_patterns(self.pat, PATLIST)

    def test_fsm_count_empty(self):
        with lightgrep.Fsm(0, 0) as fsm:
            self.assertEqual(fsm.count(), 0)

    def test_count_three(self):
        with lightgrep.Fsm(0, 0) as fsm:
            with lightgrep.Pattern() as pat:
                pat.parse("a+b", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 42)
                pat.parse("foo", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 1)
                pat.parse(".+", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 75)
            self.assertEqual(fsm.count(), 3)

    def test_count_closed(self):
        with lightgrep.Fsm(0, 0) as fsm:
            with lightgrep.Pattern() as pat:
                pat.parse("a+b", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 42)
                fsm.close()
                with self.assertRaises(RuntimeError):
                    fsm.count()


class ProgSimpleTests(unittest.TestCase):
    def test_ctor_bad_args(self):
        arglist = [0]
        subs = (None, '*', -1)
        fuzz_it(self, lightgrep.Program, arglist, subs)


class ProgTests(unittest.TestCase):
    def test_count_three(self):
        with lightgrep.Fsm(0, 0) as fsm:
            with lightgrep.Pattern() as pat:
                pat.parse("a+b", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 42)
                pat.parse("foo", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 1)
                pat.parse(".+", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 75)
            with lightgrep.Program(fsm, lightgrep.ProgOpts()) as prog:
               self.assertEqual(prog.count(), 3)

    def test_create_fsm_empty(self):
        with self.assertRaises(RuntimeError):
            lightgrep.Program(lightgrep.Fsm(0, 0), lightgrep.ProgOpts())

    def test_program_fsm_closed(self):
        with lightgrep.Fsm(0, 0) as fsm:
            fsm.close()
            with self.assertRaises(RuntimeError):
                lightgrep.Program(fsm, lightgrep.ProgOpts())

    def test_program_bad_args_1(self):
        arglist = [None]
        subs = (None,)
        fuzz_it(self, lightgrep.Program, arglist, subs)

    def test_program_bad_args_2(self):
        with lightgrep.Fsm(0, 0) as fsm:
            arglist = [fsm, lightgrep.ProgOpts()]
            subs = (None, 'bogus')
            fuzz_it(self, lightgrep.Program, arglist, subs)

    def test_size(self):
        with lightgrep.Fsm(0, 0) as fsm:
            with lightgrep.Pattern() as pat:
                pat.parse("a+b", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 42)
            with lightgrep.Program(fsm, lightgrep.ProgOpts()) as prog:
                self.assertTrue(prog.size() > 0)

    def test_write_read(self):
        with lightgrep.Fsm(0, 0) as fsm:
            with lightgrep.Pattern() as pat:
                pat.parse("a+b", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 42)
            with lightgrep.Program(fsm, lightgrep.ProgOpts()) as prog1:
                buf = prog1.write()

                with lightgrep.Program(buf) as prog2:
                    self.assertEqual(prog2.count(), prog1.count())
                    self.assertEqual(prog2.size(), prog1.size())

    def test_count_closed(self):
        with lightgrep.Fsm(0, 0) as fsm:
            with lightgrep.Pattern() as pat:
                pat.parse("a+b", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 42)
            with lightgrep.Program(fsm, lightgrep.ProgOpts()) as prog:
                prog.close()
                with self.assertRaises(RuntimeError):
                    prog.count()

    def test_size_closed(self):
        with lightgrep.Fsm(0, 0) as fsm:
            with lightgrep.Pattern() as pat:
                pat.parse("a+b", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 42)
            with lightgrep.Program(fsm, lightgrep.ProgOpts()) as prog:
                prog.close()
                with self.assertRaises(RuntimeError):
                    prog.count()

    def test_write_closed(self):
        with lightgrep.Fsm(0, 0) as fsm:
            with lightgrep.Pattern() as pat:
                pat.parse("a+b", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 42)
            with lightgrep.Program(fsm, lightgrep.ProgOpts()) as prog:
                prog.close()
                with self.assertRaises(RuntimeError):
                    prog.write()


class ContextTests(unittest.TestCase):
    def setUp(self):
        with lightgrep.Fsm(0, 0) as fsm:
            with lightgrep.Pattern() as pat:
                pat.parse("a+b", lightgrep.KeyOpts())
                fsm.add_pattern(pat, 'UTF-8', 42)
                self.prog = lightgrep.Program(fsm, lightgrep.ProgOpts())
                self.addCleanup(self.prog.close)

        self.ctx = lightgrep.Context(self.prog, lightgrep.CtxOpts())
        self.addCleanup(self.ctx.close)

    def test_ctor_bad_args(self):
        arglist = [self.prog, lightgrep.CtxOpts()]
        subs = (None, 'bogus')
        fuzz_it(self, lightgrep.Context, arglist, subs)

    def test_search_ctx_closed(self):
        self.ctx.close()
        acc = lightgrep.HitAccumulator()
        with self.assertRaises(RuntimeError):
            self.ctx.search(b'xxx', 0, acc)

    def test_search_prog_closed(self):
        self.prog.close()
        acc = lightgrep.HitAccumulator()
        with self.assertRaises(RuntimeError):
            self.ctx.search(b'xxx', 0, acc)

    def test_search_bad_args(self):
        arglist = [b'xxx', 0, lightgrep.HitAccumulator()]
        subs = (None, 'bogus')
        fuzz_it(self, self.ctx.search, arglist, subs)

    def test_search(self):
        buf = b'xxxyyyaaaabcdef'
        exp_hits = [
            {
                'start': 6,
                'end': 11,
                'keywordIndex': 42,
                'pattern': 'a+b',
                'encChain': 'UTF-8'
            }
        ]

        acc = lightgrep.HitAccumulator()
        self.ctx.search(buf, 0, acc)
        self.ctx.closeout(acc)
        self.assertEqual(acc.Hits, exp_hits)
        self.ctx.reset()

    def test_startswith_ctx_closed(self):
        self.ctx.close()
        acc = lightgrep.HitAccumulator()
        with self.assertRaises(RuntimeError):
            self.ctx.startswith(b'xxx', 0, acc)

    def test_startswith_prog_closed(self):
        self.prog.close()
        acc = lightgrep.HitAccumulator()
        with self.assertRaises(RuntimeError):
            self.ctx.startswith(b'xxx', 0, acc)

    def test_startswith_bad_args(self):
        arglist = [b'xxx', 0, lightgrep.HitAccumulator()]
        subs = (None, 'bogus')
        fuzz_it(self, self.ctx.startswith, arglist, subs)

    def test_startswith(self):
        buf = b'aaaabcdef'
        exp_hits = [
            {
                'start': 0,
                'end': 5,
                'keywordIndex': 42,
                'pattern': 'a+b',
                'encChain': 'UTF-8'
            }
        ]

        acc = lightgrep.HitAccumulator()
        self.ctx.startswith(buf, 0, acc)
        self.ctx.closeout(acc)
        self.assertEqual(acc.Hits, exp_hits)
        self.ctx.reset()

    def test_closeout_ctx_closed(self):
        self.ctx.close()
        acc = lightgrep.HitAccumulator()
        with self.assertRaises(RuntimeError):
            self.ctx.closeout(acc)

    def test_closeout_prog_closed(self):
        self.prog.close()
        acc = lightgrep.HitAccumulator()
        with self.assertRaises(RuntimeError):
            self.ctx.closeout(acc)

    def test_searchBuffer_ctx_closed(self):
        self.ctx.close()
        acc = lightgrep.HitAccumulator()
        with self.assertRaises(RuntimeError):
            self.ctx.searchBuffer(b'xxx', acc)

    def test_searchBuffer_prog_closed(self):
        self.prog.close()
        acc = lightgrep.HitAccumulator()
        with self.assertRaises(RuntimeError):
            self.ctx.searchBuffer(b'xxx', acc)

    def test_searchBuffer_bad_args(self):
        arglist = [b'xxx', lightgrep.HitAccumulator()]
        subs = (None, 'bogus')
        fuzz_it(self, self.ctx.searchBuffer, arglist, subs)

    def test_searchBuffer(self):
        buf = b'xxxyyyaaaabcdef'
        exp_hits = [
            {
                'start': 6,
                'end': 11,
                'keywordIndex': 42,
                'pattern': 'a+b',
                'encChain': 'UTF-8'
            }
        ]

        acc = lightgrep.HitAccumulator()
        self.ctx.searchBuffer(buf, acc)
        self.assertEqual(acc.Hits, exp_hits)

    def test_searchBufferStartswith_ctx_closed(self):
        self.ctx.close()
        acc = lightgrep.HitAccumulator()
        with self.assertRaises(RuntimeError):
            self.ctx.searchBufferStartswith(b'xxx', acc)

    def test_searchBufferStartswith_prog_closed(self):
        self.prog.close()
        acc = lightgrep.HitAccumulator()
        with self.assertRaises(RuntimeError):
            self.ctx.searchBufferStartswith(b'xxx', acc)

    def test_searchBufferStartswith_bad_args(self):
        arglist = [b'xxx', lightgrep.HitAccumulator()]
        subs = (None, 'bogus')
        fuzz_it(self, self.ctx.searchBufferStartswith, arglist, subs)

    def test_searchBufferStartswith(self):
        buf = b'aaaabcdef'
        exp_hits = [
            {
                'start': 0,
                'end': 5,
                'keywordIndex': 42,
                'pattern': 'a+b',
                'encChain': 'UTF-8'
            }
        ]

        acc = lightgrep.HitAccumulator()
        self.ctx.searchBufferStartswith(buf, acc)
        self.assertEqual(acc.Hits, exp_hits)


class HitDecoderSimpleTests(unittest.TestCase):
    def test_close_unused(self):
        # test that closing an unused Context doesn't throw
        dec = lightgrep.HitDecoder()
        dec.close()


class HitDecoderTests(unittest.TestCase):
    def setUp(self):
        self.dec = lightgrep.HitDecoder()
        self.addCleanup(self.dec.close)

    def test_hit_context_closed(self):
        self.dec.close()
        buf = b'xxxyyyaaaabcdef'
        hit = {
            'start': 6,
            'end': 11,
            'keywordIndex': 42,
            'pattern': 'a+b',
            'encChain': 'UTF-8'
        }
        with self.assertRaises(RuntimeError):
            self.dec.full_hit_context(buf, 0, hit, window_size=3)

    def test_full_hit_context_bad_args(self):
        buf = b'xxxyyyaaaabcdef'
        hit = {
            'start': 6,
            'end': 11,
            'keywordIndex': 42,
            'pattern': 'a+b',
            'encChain': 'UTF-8'
        }
        arglist = [buf, 0, hit, 100]
        subs = (None, 'bogus')
        fuzz_it(self, self.dec.full_hit_context, arglist, subs)

    def test_hit_context(self):
        buf = b'xxxyyyaaaabcdef'
        hit = {
            'start': 6,
            'end': 11,
            'keywordIndex': 42,
            'pattern': 'a+b',
            'encChain': 'UTF-8'
        }

        hctx = self.dec.hit_context(buf, 0, hit, window_size=3)
        self.assertEqual(hctx, 'yyyaaaabcde')

    def test_full_hit_context_closed(self):
        self.dec.close()
        buf = b'xxxyyyaaaabcdef'
        hit = {
            'start': 6,
            'end': 11,
            'keywordIndex': 42,
            'pattern': 'a+b',
            'encChain': 'UTF-8'
        }
        with self.assertRaises(RuntimeError):
            self.dec.hit_context(buf, 0, hit, window_size=3)

    def test_hit_context_bad_args(self):
        buf = b'xxxyyyaaaabcdef'
        hit = {
            'start': 6,
            'end': 11,
            'keywordIndex': 42,
            'pattern': 'a+b',
            'encChain': 'UTF-8'
        }
        arglist = [buf, 0, hit, 100]
        subs = (None, 'bogus')
        fuzz_it(self, self.dec.hit_context, arglist, subs)

    def test_full_hit_context(self):
        buf = b'xxxyyyaaaabcdef'
        hit = {
            'start': 6,
            'end': 11,
            'keywordIndex': 42,
            'pattern': 'a+b',
            'encChain': 'UTF-8'
        }

        hctx = self.dec.full_hit_context(buf, 0, hit, window_size=3)

        exp = {
            'context_begin': 3,
            'context_end': 14,
            'context_hit_begin': 3,
            'context_hit_end': 8,
            'hit_context': 'yyyaaaabcde'
        }

        self.assertEqual(hctx, exp)


class UtilityTests(unittest.TestCase):
    def test_make_program_from_patterns_bad_args(self):
        progOpts = lightgrep.ProgOpts()
        arglist = [PATLIST, progOpts]
        subs = (None, 'bogus')
        fuzz_it(self, lightgrep.make_program_from_patterns, arglist, subs)

    def test_make_program_from_patterns_good(self):
        buf = b'aaaaabb a+b'

        patlist = [
            ("a+b", ['UTF-8'], lightgrep.KeyOpts()),
            ("a+b", ['UTF-8'], lightgrep.KeyOpts(fixedString=True))
        ]

        progOpts = lightgrep.ProgOpts()
        with lightgrep.make_program_from_patterns(patlist, progOpts) as prog:
            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                acc = lightgrep.HitAccumulator()
                ctx.searchBuffer(buf, acc)

        exp_hits = [
            {
                'start': 0,
                'end': 6,
                'keywordIndex': 0,
                'pattern': 'a+b',
                'encChain': 'UTF-8'
            },
            {
                'start': 8,
                'end': 11,
                'keywordIndex': 1,
                'pattern': 'a+b',
                'encChain': 'UTF-8'
            }
        ]

        self.assertEqual(acc.Hits, exp_hits)


if __name__ == "__main__":
    unittest.main()
