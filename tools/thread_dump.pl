#!/usr/bin/perl -w

use JSON;

printf(
  "\n %-16s %-16s %-8s  %-16s %-16s\n",
  'id',
  'pc',
  'label',
  'start',
  'end'
);

while (<>) {
  next unless /^{/; # ignore lines which are not JSON
  print_frame($_); 
}

print "\n";

sub readabilify {
  my $byte = $_[0];
  my $c = chr($byte);
  return ($c =~ /[[:print:]]/) ? "'$c'" : sprintf('0x%02x', $byte);
}

sub print_frame {
  my $frame = decode_json $_[0];

  printf(
    "\n%016x <- %s\n\n",
    $frame->{'offset'},
    readabilify($frame->{'byte'})
  );

  foreach $thread (@{$frame->{'list'}}) {
    if ($thread->{'state'} == 0) {
      # thread birth is green
      print " \33[1;32m";
    }
    elsif ($thread->{'state'} == 1) {
      # pre-run
      print '-';
    }
    elsif ($thread->{'state'} == 2) {
      # post-run
      print '+';
    }
    elsif ($thread->{'state'} == 3) {
      # thread death is red
      print " \33[1;31m";
    }

    printf(
      " %016x %016x %08x [%016x,%016x]\n",
      $thread->{'Id'},
      $thread->{'PC'},
      $thread->{'Label'},
      $thread->{'Start'},
      $thread->{'End'}
    );

    if ($thread->{'state'} == 0 || $thread->{'state'} == 3) {
      # switch back to regular text color 
      print "\33[0m";
    }
  }
}
