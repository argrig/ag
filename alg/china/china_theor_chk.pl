#!/usr/bin/perl

use File::Basename ;
use lib  dirname($0) ;
use func ;
use Math::BigInt lib => "GMP" ;

$ret=0 ;
$my_ans = `cat $ARGV[0]` ;
my %a = hash_var($my_ans) ;
my %u = query_decode($ARGV[1]) ;
%nam = (  'x'   => "<i>x</i> есть решение системы", 
          'min' => "<i>x</i> &mdash; минимальное положительное решение" );
print "<table border=0>" ;
if ( ! defined $u{'x'} || $u{'x'} == 0 ) {
  no_input($nam{'x'}) ;
  goto L1 ;
} 
else {
  @data = split ' ', $a{'data'} ;
  for($i=0;$i<3;$i++) {
    if( ( $u{'x'} - $data[$i] ) % $data[$i+$a{'N'}] != 0 ) {
      wrong_input($nam{'x'}) ;
      goto L1 ;
    }
  }
  true_input($nam{'x'}) ;
  $ret+=4 ;
  if ($u{'x'} == $a{'x'}) {
    true_input($nam{'min'}) ;
    $ret+=3 ;
  }
  else {
    wrong_input($nam{'min'}) ;
  }
} 

L1: print "</table>" ;
exit ($ret) ;

