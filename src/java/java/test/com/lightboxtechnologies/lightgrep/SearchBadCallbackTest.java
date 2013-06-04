package com.lightboxtechnologies.lightgrep;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

@RunWith(Parameterized.class)
public class SearchBadCallbackTest {

  @Parameters
  public static Collection<Object[]> data()
  }

  public SearchBadCallbackTest() {

  }

  private static class CallbackExploder implements HitCallback {
    public void callback(SearchHit hit) {
      throw new RuntimeException("Out of cheese");
    }
  }

  @Test
  public void testSearchBadCallback() {
  }

  @Before
  public void setup() {
  }

  @After
  public void teardown() {
    if (hCtx) {
      hCtx.destroy();
    }
    if (hProg) {
      hProg.destroy();
    }
    if (hPattern) {
      hPattern.destroy();
    }
    if (hPatternMap) {
      hPatternMap.destroy();
    }
  }
}
