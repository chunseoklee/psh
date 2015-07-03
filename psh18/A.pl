#!/usr/bin/perl

my $str = <STDIN>;
chomp $str;
my @chars = split //, $str;

my @facc;
my @racc;
my $num = 1;

foreach my $ch (@chars) {

    if($ch eq 'l'){
        push @racc, $num;
    }
    else {
        push @facc, $num;
    }
    $num++;
}

foreach my $n (@facc) {
    print $n, "\n"
}

foreach my $n (reverse @racc) {
    print $n, "\n"
}
