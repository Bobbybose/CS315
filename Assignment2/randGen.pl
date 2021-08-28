#!/usr/bin/perl -w

# Generate a stream of pseudo-random integers in the range [0 .. 2^31),
# where the initial seed is optionally specified as the first parameter.  This
# stream is not cryptographically secure, but it is adequate for Monte-Carlo
# methods.

# Author: Raphael Finkel 1/2020

use strict;

# constants
my $modulus = 2147483648; # 2^31

# global variables
my $seed = $ARGV[0];

srand($seed) if defined $seed;
while (1) {
	print int(rand($modulus)) . "\n";
}
