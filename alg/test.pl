#!/usr/bin/perl

use Math::BigInt lib => 'GMP' ;
use Math::BigRat lib => 'GMP' ;
use Math::Polynomial ;

@test = (0,4,0,8,0,16,0) ;
for $i (@test) {
 $i=Math::BigInt->new($i) ; 
} ;
$gcd = Math::BigInt::bgcd(@test) ;

for $i (@test) {
 $i=Math::BigRat->new($i/$gcd) ; 
} ;
print "\n@test\n" ;
