#!/usr/bin/python3

import array
import ctypes
import unittest

import lightgrep


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


class HandleTests(unittest.TestCase):
    def test_handle_open_good_closed_bad(self):
        h = lightgrep.Handle(42)
        self.assertTrue(h)
        self.assertEqual(h.handle, 42)
        h.close()
        self.assertFalse(h)
        self.assertEqual(h.handle, None)


class ErrorTests(unittest.TestCase):
    def test_close_unused(self):
        # test that closing an unused Error doesn't throw
        err = lightgrep.Error()
        err.close()


class KeyOptsTests(unittest.TestCase):
    def test_flags(self):
        for fixed_string in (False, True):
            for case_insensitive in (False, True):
                with self.subTest(fixed_string=fixed_string, case_insensitive=case_insensitive):
                    opts = lightgrep.KeyOpts(fixedString=fixed_string, caseInsensitive=case_insensitive)
                    self.assertEqual(opts.isFixed(), fixed_string)
                    self.assertEqual(opts.isCaseSensitive(), not case_insensitive)


def fuzz_args(arglist, subs):
    for i in range(0, len(arglist)):
        args = arglist.copy()
        for s in subs:
            args[i] = s
            yield args


class PatternTests(unittest.TestCase):
    def test_close_unused(self):
        # test that closing an unused Pattern doesn't throw
        pat = lightgrep.Pattern()
        pat.close()

    def test_pattern_good(self):
        with lightgrep.Error() as err:
            with lightgrep.Pattern() as pat:
                pat.parse("a+b", lightgrep.KeyOpts(), err)

    def test_pattern_bad(self):
        with lightgrep.Error() as err:
            with lightgrep.Pattern() as pat:
                with self.assertRaises(RuntimeError):
                    pat.parse("+", lightgrep.KeyOpts(), err)

    def test_pattern_closed(self):
        with lightgrep.Error() as err:
            with lightgrep.Pattern() as pat:
                with self.assertRaises(RuntimeError):
                    pat.close()
                    pat.parse("a", lightgrep.KeyOpts(), err)


class FsmTests(unittest.TestCase):
    def test_close_unused(self):
        # test that closing an unused Fsm doesn't throw
        fsm = lightgrep.Fsm(0)
        fsm.close()

    def test_add_pattern_closed_prog(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    pat.parse("a+b", lightgrep.KeyOpts(), err)
                    with lightgrep.Fsm(0) as fsm:
                        prog.close()
                        with self.assertRaises(RuntimeError):
                            idx = fsm.add_pattern(prog, pat, 'UTF-8', 42, err)

    def test_add_pattern_closed_pat(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    pat.parse("a+b", lightgrep.KeyOpts(), err)
                    with lightgrep.Fsm(0) as fsm:
                        pat.close()
                        with self.assertRaises(RuntimeError):
                            idx = fsm.add_pattern(prog, pat, 'UTF-8', 42, err)

    def test_add_pattern_bad_args(self):
        # fuzz add_pattern()
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    pat.parse("a+b", lightgrep.KeyOpts(), err)
                    with lightgrep.Fsm(0) as fsm:
                        enc = 'UTF-8'
                        idx = 42
                        arglist = [prog, pat, enc, idx, err]
                        subs = (None, 'bogus')
                        for args in fuzz_args(arglist, subs):
                            with self.subTest(args=args):
                                with self.assertRaises(Exception):
                                    fsm.add_pattern(*args)

    def test_add_pattern_good(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    pat.parse("a+b", lightgrep.KeyOpts(), err)
                    with lightgrep.Fsm(0) as fsm:
                        idx = fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        self.assertEqual(idx, 0)

    PATLIST = [
        ("a+b", ['UTF-8', 'iso-8859-1'], lightgrep.KeyOpts(caseInsensitive=True)),
        ("a+b", ['UTF-8', 'iso-8859-1'], lightgrep.KeyOpts(fixedString=True))
    ]

    def test_add_patterns_bad_args(self):
        # fuzz add_patterns()
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        arglist = [prog, pat, self.PATLIST, err]
                        subs = (None, 'bogus')
                        for args in fuzz_args(arglist, subs):
                            with self.subTest(args=args):
                                with self.assertRaises(Exception):
                                    fsm.add_patterns(*args)

    def test_add_patterns(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        fsm.add_patterns(prog, pat, self.PATLIST, err)


class ProgTests(unittest.TestCase):
    def test_close_unused(self):
        # test that closing an unused Program doesn't throw
        prog = lightgrep.Program(0)
        prog.close()

    def test_count_unused(self):
        with lightgrep.Program(0) as prog:
            self.assertEqual(prog.count(), 0)

    def test_count_closed(self):
        with lightgrep.Program(0) as prog:
            prog.close()
            with self.assertRaises(RuntimeError):
                prog.count()

    def test_count_three(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        pat.parse("foo", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 1, err)
                        pat.parse(".+", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 75, err)
                        self.assertEqual(prog.count(), 3)

    def test_compile_nothing(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        with self.assertRaises(RuntimeError):
                            prog.compile(fsm, lightgrep.ProgOpts())

    def test_compile_prog_closed(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        prog.close()
                        with self.assertRaises(RuntimeError):
                            prog.compile(fsm, lightgrep.ProgOpts())

    def test_compile_fsm_closed(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        fsm.close()
                        with self.assertRaises(RuntimeError):
                            prog.compile(fsm, lightgrep.ProgOpts())

    def test_compile_bad_args(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        arglist = [fsm, lightgrep.ProgOpts()]
                        subs = (None, 'bogus')
                        for args in fuzz_args(arglist, subs):
                            with self.subTest(args=args):
                                with self.assertRaises(Exception):
                                    prog.compile(*args)

#    def test_write_read(self):



class ContextTests(unittest.TestCase):
    def test_ctor_prog_closed(self):
        with lightgrep.Program(0) as prog:
            prog.close()
            with self.assertRaises(RuntimeError):
                lightgrep.Context(prog, lightgrep.CtxOpts())

    def test_ctor_bad_args(self):
        with lightgrep.Program(0) as prog:
            arglist = [prog, lightgrep.CtxOpts()]
            subs = (None, 'bogus')
            for args in fuzz_args(arglist, subs):
                with self.subTest(args=args):
                    with self.assertRaises(Exception):
                        lightgrep.Context(*args)

    def test_search_ctx_closed(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                ctx.close()
                acc = lightgrep.HitAccumulator()
                with self.assertRaises(RuntimeError):
                    ctx.search(b'xxx', 0, acc)

    def test_search_prog_closed(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                prog.close()
                acc = lightgrep.HitAccumulator()
                with self.assertRaises(RuntimeError):
                    ctx.search(b'xxx', 0, acc)

    def test_search_bad_args(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                acc = lightgrep.HitAccumulator()
                arglist = [b'xxx', 0, acc]
                subs = (None, 'bogus')
                for args in fuzz_args(arglist, subs):
                    with self.assertRaises(Exception):
                        ctx.search(*args)

    def test_search(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())
            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
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
                ctx.search(buf, 0, acc)
                ctx.closeout(acc)
                self.assertEqual(acc.Hits, exp_hits)
                ctx.reset()

    def test_startswith_ctx_closed(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                ctx.close()
                acc = lightgrep.HitAccumulator()
                with self.assertRaises(RuntimeError):
                    ctx.startswith(b'xxx', 0, acc)

    def test_startswith_prog_closed(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                prog.close()
                acc = lightgrep.HitAccumulator()
                with self.assertRaises(RuntimeError):
                    ctx.startswith(b'xxx', 0, acc)

    def test_startswith_bad_args(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                acc = lightgrep.HitAccumulator()
                arglist = [b'xxx', 0, acc]
                subs = (None, 'bogus')
                for args in fuzz_args(arglist, subs):
                    with self.assertRaises(Exception):
                        ctx.startswith(*args)

    def test_startswith(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())
            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
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
                ctx.startswith(buf, 0, acc)
                ctx.closeout(acc)
                self.assertEqual(acc.Hits, exp_hits)
                ctx.reset()

    def test_closeout_ctx_closed(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                ctx.close()
                acc = lightgrep.HitAccumulator()
                with self.assertRaises(RuntimeError):
                    ctx.closeout(acc)

    def test_closeout_prog_closed(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                prog.close()
                acc = lightgrep.HitAccumulator()
                with self.assertRaises(RuntimeError):
                    ctx.closeout(acc)

    def test_searchBuffer_ctx_closed(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                ctx.close()
                acc = lightgrep.HitAccumulator()
                with self.assertRaises(RuntimeError):
                    ctx.searchBuffer(b'xxx', acc)

    def test_searchBuffer_prog_closed(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                prog.close()
                acc = lightgrep.HitAccumulator()
                with self.assertRaises(RuntimeError):
                    ctx.searchBuffer(b'xxx', acc)

    def test_searchBuffer_bad_args(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                acc = lightgrep.HitAccumulator()
                arglist = [b'xxx', acc]
                subs = (None, 'bogus')
                for args in fuzz_args(arglist, subs):
                    with self.assertRaises(Exception):
                        ctx.searchBuffer(*args)

    def test_searchBuffer(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())
            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
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
                ctx.searchBuffer(buf, acc)
                self.assertEqual(acc.Hits, exp_hits)

    def test_searchBufferStartswith_ctx_closed(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                ctx.close()
                acc = lightgrep.HitAccumulator()
                with self.assertRaises(RuntimeError):
                    ctx.searchBufferStartswith(b'xxx', acc)

    def test_searchBufferStartswith_prog_closed(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                prog.close()
                acc = lightgrep.HitAccumulator()
                with self.assertRaises(RuntimeError):
                    ctx.searchBufferStartswith(b'xxx', acc)

    def test_searchBufferStartswith_bad_args(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())

            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
                acc = lightgrep.HitAccumulator()
                arglist = [b'xxx', acc]
                subs = (None, 'bogus')
                for args in fuzz_args(arglist, subs):
                    with self.assertRaises(Exception):
                        ctx.searchBufferStartswith(*args)

    def test_searchBufferStartswith(self):
        with lightgrep.Program(0) as prog:
            with lightgrep.Error() as err:
                with lightgrep.Pattern() as pat:
                    with lightgrep.Fsm(0) as fsm:
                        pat.parse("a+b", lightgrep.KeyOpts(), err)
                        fsm.add_pattern(prog, pat, 'UTF-8', 42, err)
                        prog.compile(fsm, lightgrep.ProgOpts())
            with lightgrep.Context(prog, lightgrep.CtxOpts()) as ctx:
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
                ctx.searchBufferStartswith(buf, acc)
                self.assertEqual(acc.Hits, exp_hits)


class HitDecoderTests(unittest.TestCase):
    def test_close_unused(self):
        # test that closing an unused Context doesn't throw
        dec = lightgrep.HitDecoder()
        dec.close()

    def test_hit_context_closed(self):
        with lightgrep.HitDecoder() as dec:
            dec.close()
            buf = b'xxxyyyaaaabcdef'
            hit = {
                'start': 6,
                'end': 11,
                'keywordIndex': 42,
                'pattern': 'a+b',
                'encChain': 'UTF-8'
            }
            with self.assertRaises(RuntimeError):
                dec.full_hit_context(buf, 0, hit, window_size=3)

    def test_full_hit_context_bad_args(self):
        with lightgrep.HitDecoder() as dec:
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
            for args in fuzz_args(arglist, subs):
                with self.assertRaises(Exception):
                    hctx = dec.full_hit_context(*args)

    def test_hit_context(self):
        with lightgrep.HitDecoder() as dec:
            buf = b'xxxyyyaaaabcdef'
            hit = {
                'start': 6,
                'end': 11,
                'keywordIndex': 42,
                'pattern': 'a+b',
                'encChain': 'UTF-8'
            }

            hctx = dec.hit_context(buf, 0, hit, window_size=3)
            self.assertEqual(hctx, 'yyyaaaabcde')

    def test_full_hit_context_closed(self):
        with lightgrep.HitDecoder() as dec:
            dec.close()
            buf = b'xxxyyyaaaabcdef'
            hit = {
                'start': 6,
                'end': 11,
                'keywordIndex': 42,
                'pattern': 'a+b',
                'encChain': 'UTF-8'
            }
            with self.assertRaises(RuntimeError):
                dec.hit_context(buf, 0, hit, window_size=3)

    def test_hit_context_bad_args(self):
        with lightgrep.HitDecoder() as dec:
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
            for args in fuzz_args(arglist, subs):
                with self.assertRaises(Exception):
                    hctx = dec.hit_context(*args)

    def test_full_hit_context(self):
        with lightgrep.HitDecoder() as dec:
            buf = b'xxxyyyaaaabcdef'
            hit = {
                'start': 6,
                'end': 11,
                'keywordIndex': 42,
                'pattern': 'a+b',
                'encChain': 'UTF-8'
            }

            hctx = dec.full_hit_context(buf, 0, hit, window_size=3)

            exp = {
                'context_begin': 3,
                'context_end': 14,
                'context_hit_begin': 3,
                'context_hit_end': 8,
                'hit_context': 'yyyaaaabcde'
            }

            self.assertEqual(hctx, exp)


if __name__ == "__main__":
    unittest.main()
