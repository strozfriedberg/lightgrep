package com.lightboxtechnologies.lightgrep;

public class SearchHit {
  public long Start;
  public long End;
  public int KeywordIndex;

  public SearchHit(long start, long end, int keywordIndex) {
    Start = start;
    End = end;
    KeywordIndex = keywordIndex;
  }

  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }

    if (!(o instanceof SearchHit)) {
      return false;
    }

    final SearchHit h = (SearchHit) o;
    return Start == h.Start && End == h.End && KeywordIndex == h.KeywordIndex;
  }

  public int hashCode() {
    return ((17*37 + KeywordIndex)*37 +
      ((int) (Start ^ (Start >> 32))))*37 + ((int) (End ^ (End >> 32)));
  }

  public String toString() {
    return KeywordIndex + "@[" + Start + "," + End + ")";
  }
}
