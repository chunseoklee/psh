my $filename = 'inputA.txt';
open(my $fh, '>', $filename) or die "Could not open file '$filename' $!";

my $N = 100000;
print $fh "$N\n";
for (my $i=1;$i<=$N-1;$i++) {
    print $fh "$i ", $i+1, " 2\n";
}
close $fh;
