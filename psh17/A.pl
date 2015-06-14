#!/usr/bin/perl
use List::Util qw(min max);

my $ND = <STDIN>;
my @discounts = split(' ', <STDIN>);
my $minsize =  min @discounts;

my $NI = <STDIN>;
my @Items = split(' ', <STDIN>);
my @sorted_items = sort @Items;

my $s = -1;
my $t = $NI;



while($s<$t){
    if($s+$minsize >= $t) {
        $s = $t - 1;
    } else {
        $s = $s + $minsize;
    }
    $t = $t - 2;
}

my $sum = 0;
for my $i (0..$s) {
    $sum += $sorted_items[$i];
}

print $sum;
