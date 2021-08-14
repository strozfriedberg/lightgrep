import os
import subprocess
import tempfile


def run_grep(grep, pats, text, emptymsg):
    pf = None

    try:
        if len(pats) == 1:
            # specify single patterns on command line
            cmd = (grep, '-p', pats[0])
        else:
            # write multiple patterns to temporary pattern file
            fd, pfname = tempfile.mkstemp('w')
            pf = os.fdopen(fd, 'w')

            for p in pats:
                print(p, file=pf)
            pf.close()

            cmd = (grep, pfname)

        # get matches from grep
        proc = subprocess.Popen(
            cmd,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            encoding='UTF-8'
        )

        gout, gerr = proc.communicate(text)

        retval = proc.wait()
        if retval:
            raise Exception('{} returned {}, {}'.format(grep, retval, gerr))

    finally:
        if pf:
            # clean up pattern file, if we used one
            pf.close()
            os.unlink(pfname)

    if len(pats) == gerr.count(emptymsg):
        # every pattern in this pattern set has zero-length matches
        return None

    # parse the matches
    matches = []
    for m in gout.splitlines():
        s, e, l = m.split('\t', 3)[0:3]
        matches.append((int(s), int(e), int(l)))

    # sort the matches by start, end, label
    matches.sort()

    return matches


def run_shitgrep(sg, pats, text):
    return run_grep(sg, pats, text, 'is not allowed as a final state of the NFA')


def run_lightgrep(lg, pats, text):
    return run_grep(lg, pats, text, 'Empty matches on pattern')
