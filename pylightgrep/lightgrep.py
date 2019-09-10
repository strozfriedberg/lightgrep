#!/usr/bin/python3
#
# Copyright (c) 2014, Lightbox Technologies, Inc. All Rights Reserved.
#
# These bindings work with Python 3 in both 32-bit and 64-bit versions
# lightgrep.dll architecture must, however, match the Python architecture
# otherwise an error will be generated.
#

import collections
from ctypes import *
import sys


#
# Library initialization
#

def load_library(base):
    if sys.platform == 'win32':
        ext = '.dll'
    elif sys.platform == 'darwin':
        ext = '.dylib'
    else:
        ext = '.so'

    name = base + ext

    try:
        return CDLL(name)
    except Exception as e:
        raise RuntimeError(f"Failed to load {name} from {sys.path}") from e


_LG = load_library('liblightgrep')

#
# Buffer handling crap
#

c_ssize_p = POINTER(c_ssize_t)


class Py_buffer(Structure):
    _fields_ = [
        ('buf', c_void_p),
        ('obj', py_object),
        ('len', c_ssize_t),
        ('itemsize', c_ssize_t),
        ('readonly', c_int),
        ('ndim', c_int),
        ('format', c_char_p),
        ('shape', c_ssize_p),
        ('strides', c_ssize_p),
        ('suboffsets', c_ssize_p),
        ('internal', c_void_p)
    ]


def buf_beg(buf, ptype):
    if isinstance(buf, bytes):
        # yay, we can get a pointer from a bytes
        return cast(buf, POINTER(ptype * 1))[0]
    elif len(buf) >= 8 and (not isinstance(buf, memoryview) or not buf.readonly):
        # we have a writable buffer; from_buffer requires len >= 8
        return (ptype * 1).from_buffer(buf)
    else:
        # we have a read-only memoryview or a short buffer
        obj = py_object(buf)
        pybuf = Py_buffer()
        try:
            pythonapi.PyObject_GetBuffer(obj, byref(pybuf), 0)
            return (ptype * pybuf.len).from_address(pybuf.buf)
        finally:
            pythonapi.PyBuffer_Release(byref(pybuf))


def buf_range(buf, ptype):
    beg = buf_beg(buf, ptype)
    end = cast(beg, POINTER(ptype * 1))[len(buf)]
    return beg, end


def buf_end(buf, ptype):
    return buf_range(buf, ptype)[1]


#
# Structs
#

def char_cast_bool(boolValue):
    return b'\x01' if boolValue else b'\x00'


def bool_cast_char(charValue):
    return charValue != b'\x00'


class Err(Structure):
    _fields_ = [
        ("Message", c_char_p),
        ("Pattern", c_char_p),
        ("Encoding", c_char_p),
        ("Source", c_char_p),
        ("Index", c_int),
        ("Next", c_void_p)
    ]


class PatternInfo(Structure):
    _fields_ = [
        ("Pattern", c_char_p),
        ("EncodingChain", c_char_p),
        ("UserIndex", c_uint64)
    ]

    # lg strings are always utf-8 to avoid cross-platform confusion

    def pat(self):
        return self.Pattern.decode("utf-8")

    def encChain(self):
        return self.EncodingChain.decode("utf-8")

    def userIdx(self):
        return self.UserIndex


class KeyOpts(Structure):
    _fields_ = [
        ("FixedString", c_char),
        ("CaseInsensitive", c_char)
    ]

    def __init__(self, fixedString = False, caseInsensitive = False):
        super().__init__()
        self.FixedString = char_cast_bool(fixedString)
        self.CaseInsensitive = char_cast_bool(caseInsensitive)

    def isFixed(self):
        return bool_cast_char(self.FixedString)

    def isCaseSensitive(self):
        # note that this returns "Sensitive", not "Insensitive"
        return not bool_cast_char(self.CaseInsensitive)


class ProgOpts(Structure):
    _fields_ = [("Determinize", c_char)]

    def __init__(self, shouldDet = True):
        super().__init__()
        self.Determinize = char_cast_bool(shouldDet)


class CtxOpts(Structure):
    # argh, this crap shouldn't even be exposed
    _fields_ = [
        ("TraceBegin", c_uint64),
        ("TraceEnd", c_uint64)
    ]

    def __init__(self):
        super().__init__()
        self.TraceBegin = 0xFFFFFFFFFFFFFFFF
        self.TraceEnd = 0


class SearchHit(Structure):
    _fields_ = [
        ("Start", c_uint64),
        ("End", c_uint64),
        ("KeywordIndex", c_uint32)
    ]


class Window(Structure):
    _fields_ = [
        ("Start", c_uint64),
        ("End", c_uint64)
    ]


_CBType = CFUNCTYPE(None, py_object, POINTER(SearchHit))


#
# Python handles
#

class Handle(object):
    def __init__(self, handle):
        self.handle = handle

    def __bool__(self):
        return bool(self.handle)

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close()

    def close(self):
        self.handle = None


class Error(Handle):
    def __init__(self):
        super().__init__(POINTER(Err)())

    def close(self):
        _LG.lg_free_error(self.handle)
        super().close()


class Pattern(Handle):
    def __init__(self):
        super().__init__(_LG.lg_create_pattern())

    def close(self):
        _LG.lg_destroy_pattern(self.handle)
        super().close()

    def parse(self, pat, opts, err):
        if not self.handle:
            raise RuntimeError("Pattern handle is closed")

        if _LG.lg_parse_pattern(self.handle, pat.encode("utf-8"), byref(opts), byref(err.handle)) <= 0:
# FIXME: check that pattern is in message
            raise RuntimeError(f"Error parsing pattern: {err.handle.contents.Message or ''}")


class Fsm(Handle):
    def __init__(self, size):
        super().__init__(_LG.lg_create_fsm(size))

    def close(self):
        _LG.lg_destroy_fsm(self.handle)
        super().close()

    def add_pattern(self, prog, pat, enc, userIdx, err):
        if not self.handle:
            raise RuntimeError("Fsm handle is closed")
        if not prog.handle:
            raise RuntimeError("Program handle is closed")
        if not pat.handle:
            raise RuntimeError("Pattern handle is closed")

        idx = _LG.lg_add_pattern(self.handle, prog.handle, pat.handle, enc.encode("utf-8"), userIdx, byref(err.handle))
        if idx < 0:
# FIXME: check that pattern is in message
            raise RuntimeError(f"Error adding pattern: {err.handle.contents.Message or ''}")
        return idx

    def add_patterns(self, prog, pat, patlist, err):
        # patlist is a list of ("pattern", ["encoding"], keyOpts)
        for i, p in enumerate(patlist):
            if not p[0]:
                raise IndexError(f"No pattern specified on pattern {i}")
            if not p[1]:
                raise IndexError(f"No encodings specified on pattern {i}")
            if not p[2]:
                raise IndexError(f"No keyword options specified on pattern {i}")
            pat.parse(p[0], p[2], err)

            for enc in p[1]:
                self.add_pattern(prog, pat, enc, i, err)


class Program(Handle):
    def __init__(self, arg):
        if isinstance(arg, int):
            # ints create fresh programs
            handle = _LG.lg_create_program(arg)
        else:
            # buffers unserialize programs
            c_buf = buf_beg(arg, c_char)
            handle = _LG.lg_read_program(c_buf, len(arg))

        super().__init__(handle)

    def close(self):
        _LG.lg_destroy_program(self.handle)
        super().close()

    def compile(self, fsm, opts):
        if not self.handle:
            raise RuntimeError("Program handle is closed")
        if not fsm.handle:
            raise RuntimeError("Fsm handle is closed")

        if _LG.lg_compile_program(fsm.handle, self.handle, byref(opts)) == 0:
            raise RuntimeError(f"Failed to compile program")

    def count(self):
        if not self.handle:
            raise RuntimeError("Program handle is closed")
        return _LG.lg_pattern_count(self.handle)

    def write(self):
        prog_len = _LG.lg_program_size(self.handle)
        buf = bytearray(prog_len)
        c_buf = (c_char * prog_len).from_buffer(buf)
        _LG.lg_write_program(self.handle, c_buf)
        return buf


class Context(Handle):
    def __init__(self, prog, opts):
        if not prog.handle:
            raise RuntimeError("Program handle is closed")

        super().__init__(_LG.lg_create_context(prog.handle, byref(opts)))
        self.prog = prog

    def close(self):
        _LG.lg_destroy_context(self.handle)
        super().close()

    def reset(self):
        if not self.handle:
            raise RuntimeError("Context handle is closed")
        _LG.lg_reset_context(self.handle)

    def search(self, data, startOffset, accumulator):
        if not self.handle:
            raise RuntimeError("Context handle is closed")
        if not self.prog.handle:
            raise RuntimeError("Program handle is closed")

        beg, end = buf_range(data, c_char)
        return _LG.lg_search(self.handle, beg, end, startOffset, (self.prog, accumulator.lgCallback), _the_callback_shim)

    def startswith(self, data, startOffset, accumulator):
        if not self.handle:
            raise RuntimeError("Context handle is closed")
        if not self.prog.handle:
            raise RuntimeError("Program handle is closed")

        beg, end = buf_range(data, c_char)
        _LG.lg_starts_with(self.handle, beg, end, startOffset, (self.prog, accumulator.lgCallback), _the_callback_shim);

    def closeout(self, accumulator):
        if not self.handle:
            raise RuntimeError("Context handle is closed")
        if not self.prog.handle:
            raise RuntimeError("Program handle is closed")

        _LG.lg_closeout_search(self.handle, (self.prog, accumulator.lgCallback), _the_callback_shim)

    def searchBuffer(self, data, accumulator):
        self.search(data, 0, accumulator)
        self.closeout(accumulator)
        self.reset()
        return len(accumulator.Hits)

    def searchBufferStartswith(self, data, accumulator):
        self.startswith(data, 0, accumulator)
        self.closeout(accumulator)
        self.reset()
        return len(accumulator.Hits)


def _the_callback_impl(holder, hitPtr):
    idx = hitPtr.contents.KeywordIndex
    hitinfo = _LG.lg_pattern_info(holder[0].handle, idx).contents
    holder[1](hitPtr.contents, hitinfo)


_the_callback_shim = _CBType(_the_callback_impl)


class HitDecoder(Handle):
    def __init__(self):
        super().__init__(_LG.lg_create_decoder())

    def close(self):
        _LG.lg_destroy_decoder(self.handle)
        super().close()

    def hit_context(self, buf, offset, hit, window_size=100):
        return self.full_hit_context(buf, offset, hit, window_size=window_size)['hit_context']

    def full_hit_context(self, buf, offset, hit, window_size=100):
        if not self.handle:
            raise RuntimeError("Decoder handle is closed")

        beg, end = buf_range(buf, c_char)
        hit_window = Window(Start=hit['start'], End=hit['end'])
        outer_range = Window()
        hit_string_location = Window()
        out = c_char_p()
        err = POINTER(Err)()
        _LG.lg_hit_context(
            self.handle,
            beg,
            end,
            offset,
            byref(hit_window),
            hit['encChain'].encode('utf-8'),
            window_size,
            ord(' '),
            byref(out),
            byref(outer_range),
            byref(hit_string_location),
            byref(err)
        )
        ret = out.value.decode('utf-8')
# TODO: context handler
        _LG.lg_free_hit_context_string(out)
        return {
            'context_begin': outer_range.Start,
            'context_end': outer_range.End,
            'context_hit_begin': hit_string_location.Start,
            'context_hit_end': hit_string_location.End,
            'hit_context': ret
        }


#
# Function Prototypes
#

#
# api.h
#
_LG.lg_free_error.argtypes = [POINTER(Err)]
_LG.lg_free_error.restype = None

_LG.lg_create_pattern.argtypes = []
_LG.lg_create_pattern.restype = c_void_p

_LG.lg_destroy_pattern.argtypes = [c_void_p]
_LG.lg_destroy_pattern.restype = None

_LG.lg_parse_pattern.argtypes = [c_void_p, c_char_p, POINTER(KeyOpts), POINTER(POINTER(Err))]
_LG.lg_parse_pattern.restype = c_int

_LG.lg_create_fsm.argtypes = [c_uint]
_LG.lg_create_fsm.restype = c_void_p

_LG.lg_destroy_fsm.argtypes = [c_void_p]
_LG.lg_destroy_fsm.restype = None

_LG.lg_add_pattern.argtypes = [c_void_p, c_void_p, c_void_p, c_char_p, c_int, POINTER(POINTER(Err))]
_LG.lg_add_pattern.restype = c_int

_LG.lg_add_pattern_list.argtypes = [c_void_p, c_void_p, c_char_p, c_char_p, POINTER(c_char_p), c_uint, POINTER(KeyOpts), POINTER(POINTER(Err))]
_LG.lg_add_pattern_list.restype = c_int

_LG.lg_pattern_count.argtypes = [c_void_p]
_LG.lg_pattern_count.restype = c_int

_LG.lg_pattern_info.argtypes = [c_void_p, c_uint]
_LG.lg_pattern_info.restype = POINTER(PatternInfo)

_LG.lg_create_program.argtypes = [c_uint]
_LG.lg_create_program.restype = c_void_p

_LG.lg_compile_program.argtypes = [c_void_p, c_void_p, POINTER(ProgOpts)]
_LG.lg_compile_program.restype = c_int

_LG.lg_program_size.argtypes = [c_void_p]
_LG.lg_program_size.restype = c_int

_LG.lg_write_program.argtypes = [c_void_p, c_void_p]
_LG.lg_write_program.restype = None

_LG.lg_read_program.argtypes = [c_void_p, c_int]
_LG.lg_read_program.restype = c_void_p

_LG.lg_destroy_program.argtypes = [c_void_p]
_LG.lg_destroy_program.restype = None

_LG.lg_create_context.argtypes = [c_void_p, POINTER(CtxOpts)]
_LG.lg_create_context.restype = c_void_p

_LG.lg_destroy_context.argtypes = [c_void_p]
_LG.lg_destroy_context.restype = None

_LG.lg_starts_with.argtypes = [c_void_p, POINTER(c_char), POINTER(c_char), c_uint64, py_object, _CBType]
_LG.lg_starts_with.restype = None

_LG.lg_reset_context.argtypes = [c_void_p]
_LG.lg_reset_context.restype = None

_LG.lg_search.argtypes = [c_void_p, POINTER(c_char), POINTER(c_char), c_uint64, py_object, _CBType]
_LG.lg_search.restype = c_void_p

_LG.lg_closeout_search.argtypes = [c_void_p, py_object, _CBType]
_LG.lg_closeout_search.restype = None

_LG.lg_search_resolve.argtypes = [c_void_p, POINTER(c_char), POINTER(c_char), c_uint64, py_object, _CBType]
_LG.lg_search_resolve.restype = c_uint64

#
# util.h
#
_LG.lg_get_char_transform_id.argtypes = [c_char_p]
_LG.lg_get_char_transform_id.restype = c_int

_LG.lg_get_encoding_id.argtypes = [c_char_p]
_LG.lg_get_encoding_id.restype = c_int

_LG.lg_get_byte_transform_id.argtypes = [c_char_p]
_LG.lg_get_byte_transform_id.restype = c_int

_LG.lg_create_decoder.argtypes = []
_LG.lg_create_decoder.restype = c_void_p

_LG.lg_destroy_decoder.argtypes = [c_void_p]
_LG.lg_destroy_decoder.restype = None

_LG.lg_read_window.argtypes = [c_void_p, POINTER(c_char), POINTER(c_char), c_uint64, POINTER(Window), c_char_p, c_size_t, c_size_t, POINTER(POINTER(c_int32)), POINTER(POINTER(c_size_t)), POINTER(c_size_t), POINTER(Window), POINTER(POINTER(Err))]
_LG.lg_read_window.restype = c_uint

_LG.lg_hit_context.argtypes = [c_void_p, POINTER(c_char), POINTER(c_char), c_uint64, POINTER(Window), c_char_p, c_size_t, c_uint32, POINTER(c_char_p), POINTER(Window), POINTER(Window), POINTER(POINTER(Err))]
_LG.lg_hit_context.restype = c_uint

_LG.lg_free_window_characters.argtypes = [POINTER(c_int32)]
_LG.lg_free_window_characters.restype = None

_LG.lg_free_window_offsets.argtypes = [POINTER(c_size_t)]
_LG.lg_free_window_offsets.restype = None

_LG.lg_free_hit_context_string.argtypes = [c_char_p]
_LG.lg_free_hit_context_string.restype = None


#
# Utility Functions
#

def make_program_from_patterns(patlist, progOpts):
    # pattern list + opts parses and compiles them

    prog = Program(len(patlist) * 10)
    try:
        with Fsm(len(patlist) * 10) as fsm:
            with Pattern() as pat:
                with Error() as err:
                    fsm.add_patterns(prog, pat, patlist, err)

                prog.compile(fsm, progOpts)
    except Exception as e:
        prog.close()
        raise e

    return prog

#####

# check for errors on handles
def _checkHandleForErrors(ret, func, args):
    if ret == 0:
        raise RuntimeError(f"Lightgrep could not create return object in call to {func.__name__}")
    return ret

_LG.lg_create_pattern.errcheck = _checkHandleForErrors
_LG.lg_create_fsm.errcheck = _checkHandleForErrors
_LG.lg_create_program.errcheck = _checkHandleForErrors
_LG.lg_create_context.errcheck = _checkHandleForErrors


def _gotHit_callback_impl(lg, hitPtr):
    idx = hitPtr.contents.KeywordIndex
    hitinfo = _LG.lg_pattern_info(lg.__prog__, idx).contents
    lg.Callback(hitPtr.contents, hitinfo)


_lg_gotHit_callback = _CBType(_gotHit_callback_impl)


# ***************** Lightgrep class for easy usage *************************#

class HitAccumulator(object):
    def __init__(self):
        self.reset()

    def reset(self):
        self.KeyCounts = collections.Counter()
        self.Hits = []

    def lgCallback(self, hitInfo, patInfo):
        d = {
            "start": hitInfo.Start,
            "end": hitInfo.End,
            "keywordIndex": patInfo.userIdx(),
            "pattern": patInfo.pat(),
            "encChain": patInfo.encChain()
        }
        self.KeyCounts[d["pattern"]] += 1
        self.Hits.append(d)


def parse_pattern_line(line, default_encs, default_key_opts):
    fields = line.strip().split('\t')
    num = len(fields)
    if num == 0:
        return None

    encs = default_encs
    opts = default_key_opts

    pat = fields[0]
    if num > 1:
        encs = fields[1].split(',')
        if len(encs) == 0: # reset
            encs = default_encs
        if num > 2:
            fixedString = True if fields[2] == '1' else False
            caseInsensitive = True if num > 3 and fields[3] == '1' else False
            opts = KeyOpts(fixedString, caseInsensitive)
    return (pat, encs, opts)
