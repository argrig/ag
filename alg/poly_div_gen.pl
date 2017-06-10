#!/usr/bin/perl

push @INC, ".." ;
use func ;
use Math::BigInt lib => "GMP"  ;
use Math::BigRat lib => "GMP"  ;
use Math::Polynomial ;

use constant { MAX1 => 7, MAX2 => 4 };
#generate polynomials
$f1 = gen_rand_poly( 1, MAX1, 1 ) ;
$f1 = gen_rand_poly( 1, MAX1, 1 ) until $f1->coeff(0) != 0 ;
$sqrt1 = $f1*$f1 ;
$f2 = gen_rand_poly( 1, MAX1, 1 ) ;
$f2 = gen_rand_poly( 1, MAX1, 1 ) until $f2->coeff(0) != 0 && $f2->coeff(0) != $f1->coeff(0) ;
do {
  $f3 =  gen_rand_poly( 2, MAX1 ) ;
  @tmp = $f3->coeff ;
} while ( $tmp[1]*$tmp[1] - 4*$tmp[0]*$tmp[2] >= 0 ) ;

($A,$B,$C,$D) = (gen_rand_poly(0,MAX1),gen_rand_poly(0,MAX1),
    gen_rand_poly(0,MAX1),gen_rand_poly(1,MAX1)) ;

$p = $f1*$f2*$f3*$A + $f2*$f3*$B + $f1*$f1*$f3*$C + $f1*$f1*$f2*$D ;
$q = $f1*$f1*$f2*$f3 ;
$gcd = $q->gcd($p) ;
$gcd /= $gcd->coeff($gcd->degree) ;
$p /= $gcd ;
$q /= $gcd ;

# points, where to calc p values:
$points = [[-2,-1,0,1,2],[-3,-2,0,1,3],[0,1,2,3,4],[-3,-2,-1,0,1],
  [-3,-1,0,2,3],[-3,-2,0,2,3],[-3,-1,0,1,3],[-3,-1,1,2,3],[-2,-1,1,2,3]] ;
@pnts = @{$points->[int(rand(9))]} ;

print "Разложить дробь \$\\frac{p}{q}\$ на простейшие дроби, где: \n\$\$\n" .
      "q=$q\n\$\$\nи многочлен \$p\$ задается условиями:\n\$\$\n" ;
for $pt (@pnts) { print "p($pt) =", $p->evaluate($pt), ",~"; } ;
print "\\deg(p) \\leq 4\n\$\$\n" ;

print "\n%p=\n%", join ( " ", $p->coeff ) , "\n" ;
print "\n%q=\n%", join ( " ", $q->coeff ) , "\n" ;

print STDERR "Ответ:\n\$\$p=$p\$\$\n\n\$\$\n\\frac{p}{q} = " .
      "\\frac{$A}{$f1} + \\frac{$B}{($f1)^2} + \\frac{$C}{$f2} + ".
      "\\frac{$D}{$f3}\n\$\$\n";

