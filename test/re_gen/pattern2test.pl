#!/usr/bin/perl -w

my $text = pop @ARGV;

# write the text to a temporary file
$text_file = 'text.tmp';
!-f $text_file or die "error: $text_file already exists!\n";
open(TEXT, ">$text_file") or die "$!\n";
print TEXT $text;
close TEXT;

# print head stuff
print <<HEAD
#include <scope/test.h>

#include "test_helper.h"

HEAD

# read the patterns
while (<>) {
  chomp;

  # get matches from shitgrep
  my @matches = ();
  foreach $m (`./shitgrep -p '$_' $text_file 2>/dev/null`) {
    push(@matches, [(split('\t', $m))[0..2]]);
  }

  # print the scope test for this pattern and text
  print <<TEST;
SCOPE_FIXTURE_CTOR(autoPatternTest$., STest, STest("$_")) {
  const byte* text = (const byte*) "$text";
  fixture.search(text, text + @{[ length $text ]}, 0, fixture);
  SCOPE_ASSERT_EQUAL(@{[ $#matches + 1 ]}, fixture.Hits.size());
TEST

  for ($i = 0; $i <= $#matches; ++$i) {
    printf(
      "  SCOPE_ASSERT_EQUAL(SearchHit(%d, %d, %d), fixture.Hits[%d]);\n",
      $matches[$i]->[0], $matches[$i]->[1], $matches[$i]->[2], $i
    );
  }

  print "}\n\n";
}

# cleanup
unlink $text_file or die "$!\n";
