#include "encoder.h"

#include <boost/scoped_array.hpp>

void Encoder::write(const UnicodeSet& uset, NFA& g, Fragment& frag) const {
  frag.InList.clear();
  frag.OutList.clear();

  boost::scoped_array<byte> buf(new byte[maxByteLength() + 20]);
  ByteSet bs;

  for (const UnicodeSet::range& r : uset) {
    const uint32 l = r.first, h = r.second;
    for (uint32 cp = l; cp < h; ++cp) {
      const uint32 len = write(cp, buf.get());

      NFA::VertexDescriptor head = 0, tail;

      bs.reset();

      // find byte 0 in the in list
      for (const auto& v : frag.InList) {
        g[v].Trans->getBits(bs);
        if (bs[buf[0]]) {
          head = v;
          break;
        }
      }

      // add byte 0 to the in list if not there already
      if (!head) {
        head = g.addVertex();
        g[head].Trans = g.TransFac->getLit(buf[0]);
        frag.InList.push_back(head);

        if (len == 1) {
          // add trailing byte to out list
          frag.OutList.emplace_back(head, 0);
        }
      }

      tail = head;

      // move on to middle bytes, if any
      for (uint32 i = 1; i < len - 1; ++i) {
        bs.reset();
        const uint32 odeg = g.outDegree(head);
        for (uint32 e = 0; e < odeg; ++e) {
          tail = g.outVertex(head, e);
          g[tail].Trans->getBits(bs);
          if (bs[buf[i]]) {
            goto NEXT;
          }
        }

        tail = g.addVertex();
        g.addEdge(head, tail);
        g[tail].Trans = g.TransFac->getLit(buf[i]);

NEXT:
        head = tail;
      }

      if (len > 1) {
        // handle trailing byte
        if (g.outDegree(head)) {
          tail = g.outVertex(head, 0);
          bs.reset();
          g[tail].Trans->getBits(bs);
          bs[buf[len-1]] = true;
          g[tail].Trans = g.TransFac->getCharClass(bs);
        }
        else {
          tail = g.addVertex();
          g.addEdge(head, tail);
          bs.reset();
          bs[buf[len-1]] = true;
          g[tail].Trans = g.TransFac->getCharClass(bs);

          // add trailing byte to out list
          frag.OutList.emplace_back(tail, 0);
        }
      }
    }
  }
}
