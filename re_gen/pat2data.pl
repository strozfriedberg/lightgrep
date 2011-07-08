#!/usr/bin/perl -w

#
# pat2test expects patterns, one per line, on STDIN.
#

use String::ShellQuote qw(shell_quote);

my $text = shift @ARGV;

# write the text to a temporary file
$text_file = 'text.tmp';
!-f $text_file or die "error: $text_file already exists!\n";
open(TEXT, ">$text_file") or die "$!\n";
print TEXT $text;
close TEXT;

my $patnum = 0;

# read the patterns
while (<>) {
  chomp;
  my $pat = $_;

  # make sure that the pattern is properly quoted
  $qpat = shell_quote($pat);

  # get matches from shitgrep
  system("./shitgrep -p $qpat $text_file 1>sg.stdout 2>sg.stderr");

  open(SGERR, '<sg.stderr') or die "$!\n";
  my $sgerr = join '', <SGERR>;
  my $zero = $sgerr =~ /state \d+ is not allowed as a final state of the NFA/;
  close SGERR;
  
  if ($zero) {
    # test this pattern for zero-length matches
  }
  else {
    # this pattern has no zero-length matches
    open(SGOUT, '<sg.stdout') or die "$!\n";
    my @sgout = <SGOUT>;
    close SGOUT;

    my @matches = ();
    foreach $m (@sgout) {
      push(@matches, [(split('\t', $m))[0..2]]);
    }

    print pack('L/aL/aL', $pat, $text, $#matches+1);

    foreach $m (@matches) {
      print pack('QQQ', $m->[0], $m->[1], 0);
    }

#    print "$pat $text ";
#    foreach $m (@matches) {
#      print "$m->[0] $m->[1]";
#    }
  }

  ++$patnum;
}

# cleanup
unlink $text_file or die "$!\n";
unlink 'sg.stdout' or die "$!\n";
unlink 'sg.stderr' or die "$!\n";
