package com.lightboxtechnologies.lightgrep;

import org.junit.Test;

import static org.junit.Assert.fail;

public abstract class AbstractDataDrivenTest {
  protected final Class<? extends Throwable> tclass;

  public AbstractDataDrivenTest(Class<? extends Throwable> tclass) {
    this.tclass = tclass;
  }

  @Test
  public void test() throws Throwable {
    if (tclass == null) {
      // We expect no exceptions.
      doTest();
    }
    else {
      // We expect an exception of type tclass.
      try {
        doTest();
      }
      catch (Throwable t) {
        if (tclass.isInstance(t)) {
          // Success! We got an exception if the expected type.
          return;
        }
        else {
          // Failure! We got some other kind of exception.
          throw t;
        }
      }

      // Failure! We got no exception.
      fail("Did not throw " + tclass.getSimpleName() + "!");
    } 
  }

  protected abstract void doTest() throws Throwable;
}
