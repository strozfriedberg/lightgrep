#!/usr/bin/python3
# Filename: lightgrep.py
#
# Copyright (c) 2014, Lightbox Technologies, Inc. All Rights Reserved.
#
# These bindings work with Python 3 in both 32-bit and 64-bit versions
# lightgrep.dll architecture must, however, match the Python architecture
# otherwise an error will be generated.
#

import sys, collections
from ctypes import *
from ctypes.util import find_library


# ***************** Structs *************************#

# seriously weird; I want to use this function in __init__s below
# to set char fields based on bool values, but ctypes always bitches
def _charBool(boolValue):
  b'\x01' if boolValue == True else b'\x00'

class Err(Structure):
  # need to come back to this, clean up Next pointer for one thing
  # why do we have so many members of our Error struct... hmm...
  _fields_ = [("Message", c_char_p),
              ("Pattern", c_char_p),
              ("Encoding", c_char_p),
              ("Source", c_char_p),
              ("Index", c_int),
              ("Next", c_void_p)]

class PatternInfo(Structure):
  _fields_ = [("Pattern", c_char_p),
              ("EncodingChain", c_char_p),
              ("UserData", c_void_p)]

  # lg strings are always utf-8 to avoid cross-platform confusion

  def pat(self):
    return self.Pattern.decode("utf-8")

  def encChain(self):
    return self.EncodingChain.decode("utf-8")

  def useridx(self):
    # ctypes converts a NULL pointer to None
    return self.UserData or 0

class KeyOpts(Structure):
  _fields_ = [("FixedString", c_char),
              ("CaseInsensitive", c_char)]

  def __init__(self, fixedString = False, caseInsensitive = False):
    super(Structure, self).__init__() # do I need to call Structure's __init__ like this?
    # self.FixedString = _charBool(fixedString) -- python/ctypes doesn't like helper function???
    self.FixedString = b'\x01' if fixedString == True else b'\x00'
    self.CaseInsensitive = b'\x01' if caseInsensitive == True else b'\x00'

  def isFixed(self):
    return self.FixedString == b'\x01'

  def isCaseSensitive(self): #note that this is "Sensitive", not "Insensitive"
    return self.CaseInsensitive != b'\x01'


class ProgOpts(Structure):
  _fields_ = [("Determinize", c_char)]

  def __init__(self, shouldDet = True):
    super(Structure, self).__init__()
    self.Determinize = b'\x01' if shouldDet == True else b'\x00'


class CtxOpts(Structure):
  # argh, this crap shouldn't even be exposed
  _fields_ = [("TraceBegin", c_uint64),
              ("TraceEnd", c_uint64)]

  def __init__(self):
    super(Structure, self).__init__()
    self.TraceBegin = 0xffffffffffffffff
    self.TraceEnd = 0


class SearchHit(Structure):
  _fields_ = [("Start", c_uint64),
              ("End", c_uint64),
              ("KeywordIndex", c_uint32)]


class Window(Structure):
  _fields_ = [("Start", c_uint64),
              ("End", c_uint64)]


# ***************** Library Init *************************#

def _openDll():
  # I think I should probably try to use ctypes.util.FindLibrary() here?
  liblg = find_library("lightgrep")
  if (liblg != None):
    return CDLL(liblg)
  elif sys.platform.startswith("win"):
    return CDLL('liblightgrep.dll')
  elif sys.platform.startswith("darwin"):
    return CDLL('liblightgrep.dylib')
  else:
    return CDLL('liblightgrep.so')

_LG = _openDll()

_CBType = CFUNCTYPE(None, c_void_p, POINTER(SearchHit))
# associate the struct with the return type, otherwise ctypes thinks the return type is an int
_CBType.restype = c_void_p

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

_LG.lg_create_pattern_map.argtypes = [c_uint]
_LG.lg_create_pattern_map.restype = c_void_p

_LG.lg_destroy_pattern_map.argtypes = [c_void_p]
_LG.lg_destroy_pattern_map.restype = None

_LG.lg_pattern_map_size.argtypes = [c_void_p]
_LG.lg_pattern_map_size.restype = c_int

_LG.lg_create_fsm.argtypes = [c_uint]
_LG.lg_create_fsm.restype = c_void_p

_LG.lg_destroy_fsm.argtypes = [c_void_p]
_LG.lg_destroy_fsm.restype = None

_LG.lg_add_pattern.argtypes = [c_void_p, c_void_p, c_void_p, c_char_p, POINTER(POINTER(Err))]
_LG.lg_add_pattern.restype = c_int

_LG.lg_add_pattern_list.argtypes = [c_void_p, c_void_p, c_char_p, c_char_p, POINTER(c_char_p), c_uint, POINTER(KeyOpts), POINTER(POINTER(Err))]
_LG.lg_add_pattern_list.restype = c_int

_LG.lg_pattern_info.argtypes = [c_void_p, c_uint]
_LG.lg_pattern_info.restype = POINTER(PatternInfo)

_LG.lg_create_program.argtypes = [c_void_p, c_void_p]
_LG.lg_create_program.restype = c_void_p

_LG.lg_program_size.argtypes = [c_void_p]
_LG.lg_program_size.restype = c_int

_LG.lg_write_program.argtypes = [c_void_p, c_void_p]
_LG.lg_write_program.restype = None

_LG.lg_read_program.argtypes = [c_void_p, c_int]
_LG.lg_read_program.restype = c_void_p

_LG.lg_destroy_program.argtypes = [c_void_p]
_LG.lg_destroy_program.restype = None

_LG.lg_create_context.argtypes = [c_void_p, c_void_p]
_LG.lg_create_context.restype = c_void_p

_LG.lg_destroy_context.argtypes = [c_void_p]
_LG.lg_destroy_context.restype = None

_LG.lg_starts_with.argtypes = [c_void_p, POINTER(c_char), POINTER(c_char), c_uint64, c_void_p, _CBType]
_LG.lg_starts_with.restype = None

_LG.lg_reset_context.argtypes = [c_void_p]
_LG.lg_reset_context.restype = None

_LG.lg_search.argtypes = [c_void_p, POINTER(c_char), POINTER(c_char), c_uint64, c_void_p, _CBType]
_LG.lg_search.restype = c_void_p

_LG.lg_closeout_search.argtypes = [c_void_p, c_void_p, _CBType]
_LG.lg_closeout_search.restype = None

_LG.lg_search_resolve.argtypes = [c_void_p, POINTER(c_char), POINTER(c_char), c_uint64, c_void_p, _CBType]
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

_LG.lg_hit_context.argtypes =[c_void_p, POINTER(c_char), POINTER(c_char), c_uint64, POINTER(Window), c_char_p, c_size_t, c_uint32, POINTER(c_char_p), POINTER(Window), POINTER(Window), POINTER(POINTER(Err))]
_LG.lg_hit_context.restype = c_uint

_LG.lg_free_window_characters.argtypes = [POINTER(c_int32)]
_LG.lg_free_window_characters.restype = None

_LG.lg_free_window_offsets.argtypes = [POINTER(c_size_t)]
_LG.lg_free_window_offsets.restype = None

_LG.lg_free_hit_context_string.argtypes = [c_char_p]
_LG.lg_free_hit_context_string.restype = None

# check for errors on handles
def _checkHandleForErrors(ret, func, args):
  if (ret == 0):
    raise RuntimeError("Lightgrep could not create return object in call to %s" % (str(func.__name__)))
  else:
    return ret

_LG.lg_create_pattern.errcheck = _checkHandleForErrors
_LG.lg_create_pattern_map.errcheck = _checkHandleForErrors
_LG.lg_create_fsm.errcheck = _checkHandleForErrors
_LG.lg_create_program.errcheck = _checkHandleForErrors
_LG.lg_create_context.errcheck = _checkHandleForErrors


# ***************** Lightgrep class for easy usage *************************#
class HitAccumulator:
  def __init__(self):
    self.reset()

  def reset(self):
    self.KeyCounts = collections.Counter()
    self.Hits = []

  def lgCallback(self, hitInfo, patInfo):
    d = {
      "start": hitInfo.Start,
      "end": hitInfo.End,
      "keywordIndex": patInfo.useridx(),
      "pattern": patInfo.pat(),
      "encChain": patInfo.encChain()
    }
    self.KeyCounts[d["pattern"]] += 1
    self.Hits.append(d)

def parse_pattern_line(line, default_encs, default_key_opts):
  fields = line.strip().split('\t')
  num = len(fields)
  encs = default_encs
  opts = default_key_opts
  if (num > 0):
    pat = fields[0]
    if (num > 1):
      encs = fields[1].split(',')
      if (len(encs) == 0): # reset
        encs = default_encs
      if (num > 2):
        fixedString = True if fields[2] == '1' else False
        caseInsensitive = True if num > 3 and fields[3] == '1' else False
        opts = KeyOpts(fixedString, caseInsensitive)
    return (pat, encs, opts)
  else:
    return None

def check_keywords_file(keywords_file):
    # will throw if there are any problems with patterns in file
    if not keywords_file:
      raise ValueError("keywords file not specified")
    with open(keywords_file, 'r') as f:
        encs = ['UTF-8']
        opts = KeyOpts(False, False)
        pats = [parse_pattern_line(line, encs, opts) for line in f]
        hits = HitAccumulator()
        with Lightgrep(pats, hits.lgCallback):
            return keywords_file

class Lightgrep():
  def __init__(self, patList=None, callback=None, **kwargs):
    if (patList is not None and callback is not None):
      # Create program from patterns
      self._createProgram(patList)
      # Create context
      self._createContext(self.__prog__, self.__pmap__, callback)

  def __enter__(self):
    return self

  def __exit__(self, type, value, traceback):
    self.close()

  def _kill(self, attr, func):
    if (hasattr(self, attr) and getattr(self, attr) != None):
      func(getattr(self, attr))
      setattr(self, attr, None)

  def num_patterns(self):
    return _LG.lg_pattern_map_size(self.__pmap__)

  def search(self, data):
    if not isinstance(data, bytes):
      raise TypeError("a bytes-like object is required, not {}".format(type(data)))
    # get a pointer range of the buffer, probably what I'm least sure of
    size = len(data)
    beg = cast(data, POINTER(c_char))
    end = cast(addressof(beg.contents)+size, POINTER(c_char))
    _LG.lg_search(self.__ctx__, beg, end, self.CurOffset, 0, self.Callback)
    self.CurOffset += size

  def startswith(self, data):
    if not isinstance(data, bytes):
      raise TypeError("a bytes-like object is required, not {}".format(type(data)))
    size = len(data)
    beg = cast(data, POINTER(c_char))
    end = cast(addressof(beg.contents)+size, POINTER(c_char))
    _LG.lg_starts_with(self.__ctx__, beg, end, 0, 0, self.Callback);

  def hit_context(self, buf, offset, hit, window_size=100):
    return self.full_hit_context(buf, offset, hit, window_size=window_size)['hit_context']

  def full_hit_context(self, buf, offset, hit, window_size=100):
    if not hasattr(self, "__dec__"):
      self.__dec__ = _LG.lg_create_decoder()
    buf_beg = cast(buf, POINTER(c_char))
    buf_end = cast(addressof(buf_beg.contents)+len(buf), POINTER(c_char))
    hit_window = Window(Start=hit['start'], End=hit['end'])
    outer_range = Window()
    hit_string_location = Window()
    out = c_char_p()
    err = POINTER(Err)()
    _LG.lg_hit_context(
      self.__dec__,
      buf_beg,
      buf_end,
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
    _LG.lg_free_hit_context_string(out)
    return {
      'context_begin': outer_range.Start,
      'context_end': outer_range.End,
      'context_hit_begin': hit_string_location.Start,
      'context_hit_end': hit_string_location.End,
      'hit_context': ret
    }

  def close(self):
    # attrs may or may not be defined, depending on exceptions generated in __init__
    self._kill("__ctx__", _LG.lg_destroy_context)
    self._kill("__prog__", _LG.lg_destroy_program)
    self._kill("__fsm__", _LG.lg_destroy_fsm)
    self._kill("__pmap__", _LG.lg_destroy_pattern_map)
    self._kill("__pat__", _LG.lg_destroy_pattern)
    self._kill("__Err__", _LG.lg_free_error)
    self._kill("__dec__", _LG.lg_destroy_decoder)

  def closeContext(self):
    # attrs may or may not be defined, depending on exceptions generated in __init__
    self._kill("__ctx__", _LG.lg_destroy_context)

  def reset(self):
    _LG.lg_reset_context(self.__ctx__)
    self.CurOffset = 0

  def _createProgram(self, patList):
    if (len(patList) == 0):
      raise IndexError("Please specify a list of patterns for Lightgrep as {\"pattern\", [\"encodings\"], keyOpts}")
    self.__pat__ = _LG.lg_create_pattern()
    self.__pmap__ = _LG.lg_create_pattern_map(len(patList))
    self.__fsm__ = _LG.lg_create_fsm(len(patList) * 10)
    err = POINTER(Err)()
    self._parsePatterns(err, patList)
    progOpts = ProgOpts()
    self.__prog__ = _LG.lg_create_program(self.__fsm__, byref(progOpts))
    if (self.__prog__ == 0):
      raise RuntimeError("Could not create bytecode program")
    _LG.lg_destroy_fsm(self.__fsm__)
    self.__fsm__ = None
    return self.__prog__, self.__pmap__

  @staticmethod
  def createProgram(patList, self=None):
    if (self is None):
      self = Lightgrep()
    return self._createProgram(patList)

  def _createContext(self, prog, pmap, callback):
    self.__prog__ = c_void_p(prog)
    self.__pmap__ = c_void_p(pmap)
    if (self.__prog__ == 0):
      raise RuntimeError("Bytecode program cannot be accessed")
    if (self.__pmap__ == 0):
      raise RuntimeError("Pattern map cannot be accessed")
    ctxOpts = CtxOpts()
    self.__ctx__ = _LG.lg_create_context(self.__prog__, byref(ctxOpts))
    self.CurOffset = 0
    def _gotHit(user, hitPtr):
      idx = hitPtr.contents.KeywordIndex
      hitinfo = _LG.lg_pattern_info(self.__pmap__, idx).contents
      callback(hitPtr.contents, hitinfo)
    self.Callback = _CBType(_gotHit)

  def createContext(self, prog, pmap, callback):
    return self._createContext(prog, pmap, callback)

  def _parsePatterns(self, err, keyList):
    # keyList is a list of ("pattern", ["encoding"], keyOpts)
    ct = 0
    for i, pat in enumerate(keyList):
      if (len(pat[0]) == 0):
        raise IndexError("No pattern specified on keyword %d" % ct)
      if (len(pat[1]) == 0):
        raise IndexError("No encodings specified on keyword %d" % ct)
      if (pat[2] is None):
        raise IndexError("No keyword options specified on keyword %d" % ct)
      result = _LG.lg_parse_pattern(self.__pat__, pat[0].encode("utf-8"), byref(pat[2]), byref(err))
      if (result > 0):
        for enc in pat[1]:
          idx = _LG.lg_add_pattern(self.__fsm__, self.__pmap__, self.__pat__, enc.encode("utf-8"), byref(err))
          if (idx >= 0):
            # lg_add_pattern_list handles this automatically
            pinfo = _LG.lg_pattern_info(self.__pmap__, idx).contents
            pinfo.UserData = ct
          else:
            self.__Err__ = err
            raise RuntimeError("Error parsing keyword #%s: Could not add %s for encoding %s: %s" % (i, pat[0], enc, err.contents.Message if err.contents.Message != None else ""))
      else:
        raise RuntimeError("Could not parse pattern #%s: %s: %s" % (i, pat[0], err.contents.Message if err.contents.Message != None else ""))
      ct += 1

  def keywordsFromPatterns(patternList, encodings, fixedString, caseInsensitive):
    # Convert list of pattern strings into Lightgrep keyword tuples
    # using the same encoding and keyOpts for all
    keyOpts = KeyOpts(fixedString = fixedString, caseInsensitive = caseInsensitive)
    keyList = []
    for pat in patternList:
      keyList.append((pat, encodings, keyOpts));
    return keyList

  def done(self):
    _LG.lg_closeout_search(self.__ctx__, 0, self.Callback)
    _LG.lg_reset_context(self.__ctx__)

  def searchBuffer(self, data, accumulator):
    self.search(data)
    self.done() # done can generate hits, too, and then will reset context
    self.reset()
    return len(accumulator.Hits)

  def searchBufferStartswith(self, data, accumulator):
    self.startswith(data)
    self.done() # done can generate hits, too, and then will reset context
    self.reset()
    return len(accumulator.Hits)

if __name__ == "__main__":
  # using the with statement correctly releases lightgrep resources when block closes
  # better to loop over files/string within the lightgrep with statement, of course,
  # as Lightgrep initialization is relatively heavyweight
  searchString = "hello, World O'Sullivan, please don't bl0w up Nain s\\09-123/12-002 s\\EU-12-23 s\\AU-13-059 "
  testString = "hello, World"
  searchData = searchString.encode('utf-8')
  testData = testString.encode('utf-8')
  print("searchString: %s" % searchString)
  keys = [
    ("hello", ["UTF-8", "ISO-8859-1"], KeyOpts(fixedString = True, caseInsensitive = False)),
    ("world", ["UTF-8"], KeyOpts(fixedString = True, caseInsensitive = True)),
    # bl0w
    ("bl\\dw", ["UTF-8"], KeyOpts(fixedString = False, caseInsensitive = True)),
    ("[^a-z]+", ["UTF-8"], KeyOpts(fixedString = False, caseInsensitive = True)),
    # Backslash must be escaped once for Python, and again for Lightgrep
    ("s\\\\((A|E)U\\-)?\\d{1,3}-\\d{1,4}[^a-zA-Z0-9]", ["UTF-8"], KeyOpts(fixedString = False, caseInsensitive = False))
  ]
  # Using with to open a Lightgrep object and
  # perform a search, passing keys and callback
  # at init.
  print("============================")
  print("Results using 'with'")
  withHits = HitAccumulator()
  with Lightgrep(keys, withHits.lgCallback) as lg:
    # call .encode() on a string to get a bytes object back, then pass into bytearray
    withHitCount = lg.searchBuffer(searchData, withHits)
    print("%d hits found" % withHitCount)
    for h in withHits.Hits:
      print("hit at (%s, %s) on keyindex %s, pattern is '%s' with encoding chain '%s'" %
        (str(h.get("start")), str(h.get("end")), str(h.get("keywordIndex")), h.get("pattern"), h.get("encChain")))
      # hBytes = searchData[h.get("start"):h.get("end")]
      # hText = hBytes.decode("utf-8)")
      # print("  hit text: '%s'" % hText)
    withHits.reset()
  print("---------------------------")
  print("Results creating program and pattern map separately from context")
  # Creating the program and pattern map separately
  # from the context
  myLgProg, myLgPmap = Lightgrep.createProgram(keys)
  myLg = Lightgrep()
  myHits = HitAccumulator()
  myLg.createContext(myLgProg, myLgPmap, myHits.lgCallback)
  myHitCount = myLg.searchBuffer(searchData, myHits)
  print("%d hits found" % myHitCount)
  for h in myHits.Hits:
    print("hit at (%s, %s) on keyindex %s, pattern is '%s' with encoding chain '%s'" %
      (str(h.get("start")), str(h.get("end")), str(h.get("keywordIndex")), h.get("pattern"), h.get("encChain")))
  myHits.reset()
  print("---------------------------")
  print("Results reusing context with different data")
  myHitCount = myLg.searchBuffer(testData, myHits)
  print("%d hits found" % myHitCount)
  for h in myHits.Hits:
    print("hit at (%s, %s) on keyindex %s, pattern is '%s' with encoding chain '%s'" %
      (str(h.get("start")), str(h.get("end")), str(h.get("keywordIndex")), h.get("pattern"), h.get("encChain")))
  myHits.reset()
  print("---------------------------")
  print("Results reusing context again with and startswith()")
  myHitCount = myLg.searchBufferStartswith(searchData, myHits)
  print("%d hits found" % myHitCount)
  for h in myHits.Hits:
    print("hit at (%s, %s) on keyindex %s, pattern is '%s' with encoding chain '%s'" %
      (str(h.get("start")), str(h.get("end")), str(h.get("keywordIndex")), h.get("pattern"), h.get("encChain")))
  myHits.reset()
  myLg.closeContext() # If you need to reuse the program and pattern map, only call closeContext()
  myLg.close() # Call close() explicitly, since we didn't use 'with'
