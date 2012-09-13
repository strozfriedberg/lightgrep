import com.lightboxtechnologies.lightgrep.Lightgrep;
import com.lightboxtechnologies.lightgrep.Lightgrep.ParserHandle;

class Test {
  public static void main(String[] args) {
    ParserHandle h = null;
    try {
      h = Lightgrep.lg_create_parser(1);
    }
    finally {
      Lightgrep.lg_destroy_parser(h);
    }
  }
}
