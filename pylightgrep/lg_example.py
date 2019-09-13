import lightgrep as lg

# using the with statement correctly releases lightgrep resources when block
# closes; better to loop over files/string within the lightgrep with statement,
# of course, as Lightgrep initialization is relatively heavyweight
searchString = "hello, World O'Sullivan, please don't bl0w up Nain s\\09-123/12-002 s\\EU-12-23 s\\AU-13-059 "
testString = "hello, World"
searchData = searchString.encode('utf-8')
testData = testString.encode('utf-8')
print("searchString: %s" % searchString)
keys = [
    ("hello", ["UTF-8", "ISO-8859-1"], lg.KeyOpts(fixedString=True, caseInsensitive=False)),
    ("world", ["UTF-8"], lg.KeyOpts(fixedString=True, caseInsensitive=True)),
    # bl0w
    ("bl\\dw", ["UTF-8"], lg.KeyOpts(fixedString=False, caseInsensitive=True)),
    ("[^a-z]+", ["UTF-8"], lg.KeyOpts(fixedString=False, caseInsensitive=True)),
    # Backslash must be escaped once for Python, and again for Lightgrep
    ("s\\\\((A|E)U\\-)?\\d{1,3}-\\d{1,4}[^a-zA-Z0-9]", ["UTF-8"], lg.KeyOpts(fixedString=False, caseInsensitive=False))
]
# Using with to open a Lightgrep object and
# perform a search, passing keys and callback
# at init.
print("============================")
print("Results using 'with'")
withHits = lg.HitAccumulator()
with lg.make_program_from_patterns(keys, lg.ProgOpts()) as prog:
    with lg.Context(prog, lg.CtxOpts()) as ctx:
        # call .encode() on a string to get a bytes object back, then pass into bytearray
        withHitCount = ctx.searchBuffer(searchData, withHits)
        print("%d hits found" % withHitCount)
        for h in withHits.Hits:
            print("hit at [%d, %d) on keyindex %d, pattern is '%s' with encoding chain '%s'" %
                (h.get("start"), h.get("end"), h.get("keywordIndex"), h.get("pattern"), h.get("encChain")))
            # hBytes = searchData[h.get("start"):h.get("end")]
            # hText = hBytes.decode("utf-8)")
            # print("    hit text: '%s'" % hText)
        withHits.reset()

print("---------------------------")
print("Results creating program and pattern map separately from context")
# Creating the program and pattern map separately
# from the context
with lg.Program(0) as prog:
    with lg.Error() as err:
        with lg.Pattern() as pat:
            with lg.Fsm(0) as fsm:
                fsm.add_patterns(prog, pat, keys, err)
                prog.compile(fsm, lg.ProgOpts())

    myHits = lg.HitAccumulator()
    with lg.Context(prog, lg.CtxOpts()) as ctx:
        myHitCount = ctx.searchBuffer(searchData, myHits)

        print("%d hits found" % myHitCount)
        for h in myHits.Hits:
            print("hit at [%d, %d) on keyindex %d, pattern is '%s' with encoding chain '%s'" %
                (h.get("start"), h.get("end"), h.get("keywordIndex"), h.get("pattern"), h.get("encChain")))
        myHits.reset()

        print("---------------------------")
        print("Results reusing context with different data")
        myHitCount = ctx.searchBuffer(testData, myHits)
        print("%d hits found" % myHitCount)
        for h in myHits.Hits:
            print("hit at [%d, %d) on keyindex %d, pattern is '%s' with encoding chain '%s'" %
                (h.get("start"), h.get("end"), h.get("keywordIndex"), h.get("pattern"), h.get("encChain")))
        myHits.reset()

        print("---------------------------")
        print("Results reusing context again with and startswith()")
        myHitCount = ctx.searchBufferStartswith(searchData, myHits)
        print(f"{myHitCount} hits found")
        for h in myHits.Hits:
            print("hit at [%d, %d) on keyindex %d, pattern is '%s' with encoding chain '%s'" %
                (h.get("start"), h.get("end"), h.get("keywordIndex"), h.get("pattern"), h.get("encChain")))
        myHits.reset()
