#!/usr/bin/perl

use File::Basename ;
use lib  dirname($0) ;
use func ;
use Math::BigInt  ;
use Math::BigRat  ;
use Math::Polynomial ;

use constant { MAX1 => 7, MAX2 => 3 };
#generate polynomials
$deg_gcd = (rand()>0.5)+1 ;
$deg_p   = (rand()>0.5) ? 4 : 5 ;
$deg_q   = ($deg_p == 4) ? 5 : 4 ;

do {
	$pre_gcd = gen_rand_poly($deg_gcd,MAX1) ;
	$p_factr = gen_rand_poly($deg_p-$deg_gcd,MAX2) ;
	$q_factr = gen_rand_poly($deg_q-$deg_gcd,MAX2) ;
	$p = $pre_gcd * $p_factr ;
	$q = $pre_gcd * $q_factr ;
	@gcds = $p->xgcd($q) ;
	$div = ($pre_gcd->coeff($pre_gcd->degree))/($gcds[0]->coeff($gcds[0]->degree)) ;
	for $i (@gcds) {$i*=$div ; } ;
} while ($pre_gcd != $gcds[0]) ;

print "Найти многочлены \$u\$ и \$v\$, такие что:\n\n" ;
print "\$p\\cdot u + q\\cdot v = (p,~q)\$,\n\n" ;
print "где \$(p,~q)\$ -- НОД следующих многочленов:\n\n" ;
print "\$p=$p\$\n\n\$q=$q\$\n" ;
print "\n%agcd=\n%", ( join ' ', $gcds[0]->coeff ) ;
print "\n\n%p=\n%", ( join ' ', $p->coeff ) ;
print "\n\n%q=\n%", ( join ' ', $q->coeff ) , "\n";

print STDERR "Ответ:\n\nНОД: \$(p,~q)=$pre_gcd\$\n\n\$u=$gcds[1]\$\n\n\$v=$gcds[2]\$\n" ;

# print ($p*$gcds[1]+$q*$gcds[2]) ;
