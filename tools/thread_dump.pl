#!/usr/bin/perl -w

use JSON;

printf(
  "\n%-16s %-16s %-8s  %-16s %-16s\n",
  'offset',
  'pc',
  'label',
  'start',
  'end'
);

while (<>) {
  next unless /^{/; # ignore lines which are not JSON
  print_frame($_); 
}

sub print_frame {
  my $frame = decode_json $_[0];

  print "\n";

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
}
