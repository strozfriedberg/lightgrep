
# Copyright 2024 Aon Cyber Solutions
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import lightgrep as lg

# Using the with statement correctly releases lightgrep resources when block
# closes; better to loop over files/string within the lightgrep with statement,
# of course, as Lightgrep initialization is relatively heavyweight
searchString = "hello, World O'Sullivan, please don't bl0w up Nain s\\09-123/12-002 s\\EU-12-23 s\\AU-13-059 "
testString = "hello, World"
searchData = searchString.encode('utf-8')
testData = testString.encode('utf-8')
print(f"searchString: {searchString}")
keys = [
    ("hello", ["UTF-8", "ISO-8859-1"], lg.KeyOpts(fixedString=True, caseInsensitive=False)),
    ("world", ["UTF-8"], lg.KeyOpts(fixedString=True, caseInsensitive=True)),
    # bl0w
    ("bl\\dw", ["UTF-8"], lg.KeyOpts(fixedString=False, caseInsensitive=True)),
    ("[^a-z]+", ["UTF-8"], lg.KeyOpts(fixedString=False, caseInsensitive=True)),
    # Backslash must be escaped once for Python, and again for Lightgrep
    ("s\\\\((A|E)U\\-)?\\d{1,3}-\\d{1,4}[^a-zA-Z0-9]", ["UTF-8"], lg.KeyOpts(fixedString=False, caseInsensitive=False)),
    # Or you can use an r-string to avoid Python escaping
    (r'\\[\d-]+', ["UTF-8"], lg.KeyOpts(fixedString=False, caseInsensitive=False))
]

# Using with to open a Lightgrep object and  perform a search,
# passing keys and callback at init.
print("============================")
print("Results using 'with'")
withHits = lg.HitAccumulator()
with lg.make_program_from_patterns(keys, lg.ProgOpts()) as prog:
    with lg.Context(prog, lg.CtxOpts()) as ctx:
        # call .encode() on a string to get a bytes object back, then pass into bytearray
        withHitCount = ctx.searchBuffer(searchData, withHits)

    print(f"{withHitCount} hits found")
    for h in withHits.Hits:
        print(f"hit at [{h['start']},{h['end']}) on keyindex {h['keywordIndex']}, pattern is '{h['pattern']}' with encoding chain '{h['encChain']}'")
        # hBytes = searchData[h['start']:h['end']]
        # hText = hBytes.decode("utf-8")
        # print(f"    hit text: '{hText}'")
    withHits.reset()

# Bad input results in exceptions
print("---------------------------")
print("Exception due to a malformed pattern")

with lg.Pattern() as pat:
    try:
        pat.parse('+++', lg.KeyOpts())
    except RuntimeError as e:
        print(e)

print("---------------------------")
print("Results creating program and pattern map separately from context")
# Creating the program and pattern map separately from the context
with lg.Program(0) as prog:
    with lg.Pattern() as pat:
        with lg.Fsm(0) as fsm:
            fsm.add_patterns(prog, pat, keys)
            prog.compile(fsm, lg.ProgOpts())

    myHits = lg.HitAccumulator()
    with lg.Context(prog, lg.CtxOpts()) as ctx:
        myHitCount = ctx.searchBuffer(searchData, myHits)

        print(f"{myHitCount} hits found")
        for h in myHits.Hits:
            print(f"hit at [{h['start']},{h['end']}) on keyindex {h['keywordIndex']}, pattern is '{h['pattern']}' with encoding chain '{h['encChain']}'")
        myHits.reset()

        print("---------------------------")
        print("Results reusing context with different data")
        myHitCount = ctx.searchBuffer(testData, myHits)
        print(f"{myHitCount} hits found")
        for h in myHits.Hits:
            print(f"hit at [{h['start']},{h['end']}) on keyindex {h['keywordIndex']}, pattern is '{h['pattern']}' with encoding chain '{h['encChain']}'")
        myHits.reset()

        print("---------------------------")
        print("Results reusing context again with and startswith()")
        myHitCount = ctx.searchBufferStartswith(searchData, myHits)
        print(f"{myHitCount} hits found")
        for h in myHits.Hits:
            print(f"hit at [{h['start']},{h['end']}) on keyindex {h['keywordIndex']}, pattern is '{h['pattern']}' with encoding chain '{h['encChain']}'")
        myHits.reset()

print("---------------------------")
print("Results adding patterns one at a time")
# Creating the program and pattern map separately from the context
with lg.Program(0) as prog:
    with lg.Pattern() as pat:
        with lg.Fsm(0) as fsm:
            for i, k in enumerate(keys):
                pat.parse(k[0], k[2])
                for enc in k[1]:
                    fsm.add_pattern(prog, pat, enc, i)
            prog.compile(fsm, lg.ProgOpts())

    myHits = lg.HitAccumulator()
    with lg.Context(prog, lg.CtxOpts()) as ctx:
        myHitCount = ctx.searchBuffer(searchData, myHits)

        print(f"{myHitCount} hits found")
        for h in myHits.Hits:
            print(f"hit at [{h['start']},{h['end']}) on keyindex {h['keywordIndex']}, pattern is '{h['pattern']}' with encoding chain '{h['encChain']}'")
        myHits.reset()

        print("---------------------------")
        print("Results reusing context with different data")
        myHitCount = ctx.searchBuffer(testData, myHits)
        print(f"{myHitCount} hits found")
        for h in myHits.Hits:
            print(f"hit at [{h['start']},{h['end']}) on keyindex {h['keywordIndex']}, pattern is '{h['pattern']}' with encoding chain '{h['encChain']}'")
        myHits.reset()

        print("---------------------------")
        print("Results reusing context again with and startswith()")
        myHitCount = ctx.searchBufferStartswith(searchData, myHits)
        print(f"{myHitCount} hits found")
        for h in myHits.Hits:
            print(f"hit at [{h['start']},{h['end']}) on keyindex {h['keywordIndex']}, pattern is '{h['pattern']}' with encoding chain '{h['encChain']}'")
        myHits.reset()

print("---------------------------")
print("Results from a search across buffers")
keys = [('hijk', ['UTF-8'], lg.KeyOpts(fixedString=True, caseInsensitive=False)),]
hits = lg.HitAccumulator()
buf1 = b'abcdefghi'
buf2 = b'jklmnopqr'

with lg.make_program_from_patterns(keys, lg.ProgOpts()) as prog:
    with lg.Context(prog, lg.CtxOpts()) as ctx:
        ctx.search(buf1, 0, hits)
        ctx.search(buf2, len(buf1), hits)
        ctx.closeout(hits)

        print(f"{len(hits.Hits)} hits found")
        for h in hits.Hits:
            print(f"hit at [{h['start']},{h['end']}) on keyindex {h['keywordIndex']}, pattern is '{h['pattern']}' with encoding chain '{h['encChain']}'")
        hits.reset()
