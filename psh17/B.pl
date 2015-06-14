#!/usr/bin/perl

my $N,$M;
($N, $M) = split(' ', <STDIN>);
my @art = split(' ', <STDIN>);

my @ar = sort @art;

foreach my $val (@ar){
    if($M == 0){
        break;
    }
    if($val < 0){
        $val = -$val;
    }
    else {
        if($M%2 == 0){
            break;
        }
        else{
            $val = -$val;
            break;
        }
    }
    $M = $M - 1;
}

$sum += $_ for @ar;
print $sum;
