#!/usr/bin/perl
use Switch;

my $N = <STDIN>;
my @pwd;
my $cur = 0;

while(<STDIN>) {
    @foo = split /[\/\s|\n]/, $_;
    foreach $item(@foo) {
        switch($item) {
            case "pwd" {
                print "\/";
                foreach (0..($cur-1)) {
                    print "$pwd[$_]\/";
                }
                print "\n";
            }
            case "cd" {}
            case ""   { $cur = 0; }
            case ".." { $cur--; }
            else {
                $pwd[$cur++] = $item;
            }
        }
    }
}
