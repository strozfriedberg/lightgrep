import lightgrep as lg

print('')

#
# ASDF-2138: new, improved API
#
buf = b'aaaaaaaaaabbbbbb'

kopts = lg.KeyOpts(fixedString=False, caseInsensitive=False)

pats = [
    ('a+b', ['UTF-8'], kopts),
    ('ab+', ['UTF-8'], kopts)
]

hits = lg.HitAccumulator()

with lg.make_program_from_patterns(pats, lg.ProgOpts()) as prog:
    with lg.Context(prog, lg.CtxOpts()) as ctx:
        ctx.searchBuffer(buf, hits)

for h in hits.Hits:
    b = h['start']
    e = h['end']
    print(f"[{b},{e}), {h['pattern']}: {buf[b:e]}")

print('')
hits.reset()
input()

#
# ASDF-2138: save and reload a program 
#
with lg.make_program_from_patterns(pats, lg.ProgOpts()) as prog:
    pbuf = prog.write()
    with open('prog.lg', 'wb') as f:
        f.write(pbuf)

with open('prog.lg', 'rb') as f:
    pbuf = f.read()

with lg.Program(pbuf, shared=False) as prog:
    with lg.Context(prog, lg.CtxOpts()) as ctx:
        ctx.searchBuffer(buf, hits)

for h in hits.Hits:
    b = h['start']
    e = h['end']
    print(f"[{b},{e}), {h['pattern']}: {buf[b:e]}")

print('')
hits.reset()
input()

#
# ASDF-2137: ASCII mode for case folding
#

pats = [
    ('[ks]', ['UTF-8'], lg.KeyOpts(fixedString=False, caseInsensitive=False, asciiMode=False)),
    ('[ks]', ['UTF-8'], lg.KeyOpts(fixedString=False, caseInsensitive=True, asciiMode=False)),
    ('[ks]', ['UTF-8'], lg.KeyOpts(fixedString=False, caseInsensitive=False, asciiMode=True)),
    ('[ks]', ['UTF-8'], lg.KeyOpts(fixedString=False, caseInsensitive=True, asciiMode=True))
]

# U+017F = LATIN SMALL LETTER LONG S
# U+212A = KELVIN SIGN
buf = "kKsS\u212A\u017F".encode('UTF-8')

with lg.make_program_from_patterns(pats, lg.ProgOpts()) as prog:
    with lg.Context(prog, lg.CtxOpts()) as ctx:
        ctx.searchBuffer(buf, hits)

for h in hits.Hits:
    b = h['start']
    e = h['end']
    print(f"[{b},{e}), {h['keywordIndex']}: {buf[b:e]}")

print('')
hits.reset()
input()

#
# ASDF-2135: toggle case sensitivity, ASCII mode within patterns
#

pats = [
    ('(?i)x((?-i)x)x', ['UTF-8'], lg.KeyOpts(caseInsensitive=False, asciiMode=False)),
    ('(?i)k(?-i)k(?ai)k+', ['UTF-8'], lg.KeyOpts(caseInsensitive=False, asciiMode=False)),
    ('(?i)k(?-i)k(?i)k+', ['UTF-8'], lg.KeyOpts(caseInsensitive=False, asciiMode=False))
]

buf = 'XXX XxX xxx Kkkk Kk\u212AK'.encode('UTF-8')

with lg.make_program_from_patterns(pats, lg.ProgOpts()) as prog:
    with lg.Context(prog, lg.CtxOpts()) as ctx:
        ctx.searchBuffer(buf, hits)

for h in hits.Hits:
    b = h['start']
    e = h['end']
    print(f"[{b},{e}), {h['pattern']}: {buf[b:e]}")

print('')
hits.reset()
