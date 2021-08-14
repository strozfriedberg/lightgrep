#pragma once

#include <functional>

#include <tsk/libtsk.h>

#include "jsoncons_wrapper.h"
#include "inodeandblocktracker.h"

namespace TskReaderHelper {
  template <class Provider>
  void handleRuns(
    const TSK_FS_ATTR& a,
    uint64_t fsOffset,
    uint64_t blockSize,
    uint64_t inum,
    Provider tsk,
    InodeAndBlockTracker& tracker,
    void (InodeAndBlockTracker::*markDataRun)(uint64_t, uint64_t, uint64_t),
    jsoncons::json& jnrd_runs
  )
  {
    uint64_t skipBytes = a.nrd.skiplen;
    const uint64_t mainSize = (a.flags & TSK_FS_ATTR_COMP) ? a.nrd.allocsize : a.nrd.initsize;

    uint64_t fileOffset = 0;
    uint64_t slackOffset = 0;

    for (auto r = a.nrd.run; r; r = r->next) {
      if (r->flags == TSK_FS_ATTR_RUN_FLAG_FILLER) {
        // TODO: check on the exact semantics of TSK_FS_ATTR_RUN_FLAG_FILLER
        continue;
      }

      jnrd_runs.push_back(tsk.convertRun(*r));

      // Determine absolute offsets for the run
      uint64_t beg = fsOffset + r->addr * blockSize;
      const uint64_t runEnd = beg + r->len * blockSize;
      uint64_t end = runEnd;

      // Ensure that we've advanced past the initial skip.

      // The TSK structs are capable of representing an intial skip
      // which could exceed the length of one or more runs. Can that
      // ever happen? No idea.
      if (skipBytes > 0) {
        const uint64_t toSkip = std::min(end - beg, skipBytes);
        beg += toSkip;
        skipBytes -= toSkip;
      }

      if (beg < end) {
        // we've reached data
        bool trueSlack = false;
        uint64_t bytesRemaining = mainSize - fileOffset;
        if (beg + bytesRemaining < end) {
          // end is the start of true slack
          end = beg + bytesRemaining;
          trueSlack = true;
        }

        if (beg < end) {
          if (r->flags == TSK_FS_ATTR_RUN_FLAG_NONE) {
            // just normal data; sparse blocks will be made available
            // as unallocated (FIXME: still true?)
            (tracker.*markDataRun)(inum, beg, end);
          }
          // advance offset (even if data run is sparse)
          fileOffset += (end - beg);
        }

        if (trueSlack) {
          // mark slack at end of allocated space
          if (r->flags == TSK_FS_ATTR_RUN_FLAG_NONE) {
            // but only if not sparse (sparse slack is a thing!)

            // TODO: We're not marking slack right now because we
            // don't know what should claim it.
          }
          slackOffset += (runEnd - end);
        }
      }

      if (r == a.nrd.run_end) {
        // This is hopefully unnecessary, but what if
        // r->nrd.run_end.next isn't null?
        // paranoia is a feature
        // FIXME: Maybe we should throw here instead?
        break;
      }
    }
  }

  template <class Provider>
  void handleAttrs(
    const TSK_FS_META& meta,
    uint64_t fsOffset,
    uint64_t blockSize,
    uint64_t inum,
    Provider& tsk,
    InodeAndBlockTracker& tracker,
    jsoncons::json& jattrs
  )
  {
    if (!meta.attr) {
      return;
    }

    const bool deleted = meta.flags & TSK_FS_META_FLAG_UNALLOC;
    const auto markDataRun = deleted ? &InodeAndBlockTracker::markBlocksClaimed
                                     : &InodeAndBlockTracker::markBlocksAllocated;

    for (const TSK_FS_ATTR* a = meta.attr->head; a; a = a->next) {
      if (!(a->flags & TSK_FS_ATTR_INUSE)) {
        // This is an artifact of TSK's data structures, not a real run.
        continue;
      }

      jsoncons::json jattr = tsk.convertAttr(*a);

      if (a->flags & TSK_FS_ATTR_NONRES) {
        handleRuns(
          *a, fsOffset, blockSize, inum, tsk,
          tracker, markDataRun, jattr["nrd_runs"]
        );
      }

      jattrs.push_back(std::move(jattr));
    }
  }
}
