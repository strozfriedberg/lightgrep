#!/usr/bin/perl -w

use JSON;

printf(
  "\n%-16s %-16s %-8s  %-16s %-16s\n\n",
  'offset',
  'pc',
  'label',
  'start',
  'end'
);

while (<>) {
  # ignore lines which are not JSON
  next unless /^{/;

  my $frame = decode_json $_;

  foreach $thread (@{$frame->{'list'}}) {
    printf(
      "%016x %016x %08x [%016x,%016x)\n",
      $frame->{'offset'},
      $thread->{'pc'},
      $thread->{'Label'},
      $thread->{'Start'},
      $thread->{'End'}
    );
  }

  print "\n";
}
