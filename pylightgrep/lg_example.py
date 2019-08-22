from lightgrep import *

# using the with statement correctly releases lightgrep resources when block
# closes; better to loop over files/string within the lightgrep with statement,
# of course, as Lightgrep initialization is relatively heavyweight
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
        # print("    hit text: '%s'" % hText)
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
