#!/usr/bin/perl

use constant MAXDIV =>  3 ;
use constant MAXCOEF => 4 ;
use constant MAXX => 1000 ;
$prob1 = ( rand(4) > 3 ) ? 1 : 0 ; # probabilityi of 1 is ~0.25


@prime=(2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97) ;
#@a = ([1,2,3],[4,5,6],[7,8,9]) ;
#print det(@a) ;
$parts = (int(($#prime+1)/MAXDIV)) ;
$div_num = (rand(2)>1) ? MAXDIV-1 : MAXDIV ;
$modulo = 1 ;
for ($i=$div_num; ($i--) > 0;) {
	$mod_divs[$i] =	$prime[$i * $parts + int(rand($parts+1))] ;
	# print "div_num=$div_num\ni=$i\nmod_divs=$mod_divs[$i]\nparts=$parts\n" ;
	$modulo *= $mod_divs[$i] ;
	$str .= (($i == $div_num-1) ? "" : "*") . $mod_divs[$i] ;
}

	$nod = ($prob1 == 0) ? $mod_divs[$#mod_divs] : $mod_divs[$#mod_divs-1] ;

do {
	$a[1][0]=$a[2][0]=$a[2][1]=0 ;
	$a[0][0]=$prime[int(rand(MAXCOEF))] ;
	$a[1][1]=$prime[int(rand(MAXCOEF))] ;
	$a[2][2]=$nod ;
	$a[0][1]=int(rand(MAXCOEF))+1 ;
	$a[0][2]=int(rand(MAXCOEF))+1 ;
	$a[1][2]=int(rand(MAXCOEF))+1 ;
} while (det(@a)%$modulo == 0) ;

print "$str\nmodulo=$modulo\na=\n" ;

@a = sum_row(2,1,int(rand(MAXCOEF))+1,sum_row(2,0,int(rand(MAXCOEF))+1,sum_row(1, 0, int(rand(MAXCOEF))+1, @a))) ;
print "det a = " . det(@a) . "\n" ;

for $i (0 .. $#{$a[0]}) {
	$x[$i] = int(rand(MAXX)) ;
}

for $i (0 .. $#{$a[0]}) {
	for $j (0 .. $#a) {
		$b[$i] += $x[$j]*$a[$i][$j] ;
	}
}

foreach $z ( @{$a[0]}, @{$a[1]}, @{$a[2]}, @x, @b) {$z%=$modulo ; } ;

foreach (@a) {print join("\t",@{$_}) . "\n" ;} ;
print "x=" . join("\t", @x) ."\n" ;
print "b=" . join("\t", @b) ."\n" ;


################################################

sub det {
	return  $_[0][0]*$_[1][1]*$_[2][2]+$_[0][1]*$_[1][2]*$_[2][0]+$_[1][0]*$_[2][1]*$_[0][2]-
		$_[0][2]*$_[1][1]*$_[2][0]-$_[1][0]*$_[0][1]*$_[2][2]-$_[0][0]*$_[1][2]*$_[2][1] ;
}

sub sum_row {
	my ($to, $from, $coef, @a) = @_ ;
	print "\nto=$to\tfrom=$from\tcoef=$coef\n" ; 	
	foreach $i (0 .. $#{$a[$to]}) {
		$a[$to][$i] += $a[$from][$i]*$coef ;
#		print "str:\t $a[$to][$i] \t" . join("\t",@{$a[$to]}) . "\n" ;
	}
		return @a ;	
}

