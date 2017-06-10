#!/usr/bin/perl

use File::Basename ;
use lib  dirname($0) ;
use func ;
use Math::BigInt  ;
use Math::BigRat  ;
use Math::Polynomial ;

$ret=0 ;
$my_ans = `cat $ARGV[0]` ;
my %a = hash_var($my_ans) ;
my %u = query_decode($ARGV[1]) ;
my %all = (%a, %u) ;
%nam = ( 'gcd' => "НОД", 'uv' => "<i>u, v</i>" );
for $key ( keys %all ) {
  ${$key} = str2poly ( $all{$key} ) ; 
}

print "<table border=0>" ;
if (! defined $gcd) {
  no_input($nam{'gcd'}) ;
  goto L1 ;
}
if( $gcd % $agcd != 0 || $gcd->degree != $agcd->degree ) {
  wrong_input($nam{'gcd'}) ;
}
else {
  true_input($nam{'gcd'}) ;
  $ret=3 ;
	if (! defined $u || ! defined $v) {
	  no_input($nam{'uv'}) ;
	  goto L1 ;
	}
  if ( $p*$u + $q*$v != $gcd ) {
    wrong_input($nam{'uv'}) ;
# print "\np=$p\nq=$q\ngcd=$gcd\npu+qv=",($p*$u + $q*$v),"\n" ;
  }
  else {
    true_input($nam{'uv'}) ;
    $ret+=6 ;
  }
}

L1: print "</table>" ;
exit ($ret) ;

