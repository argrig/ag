#!/usr/bin/perl

use File::Basename ;
use lib  dirname($0) ;
use func ;
use Math::BigInt lib => "GMP" ;
use Math::BigRat lib => "GMP" ;
use Math::Polynomial ;

$ret=0 ;
$my_ans = `cat $ARGV[0]` ;
my %a = hash_var($my_ans) ;
my %u = query_decode($ARGV[1]) ;
%nam = ( 'p' => "многочлен <i>p</i>", 'q' => 'разложение <i>q</i>', 
    'pdivq' => "разложение <i>p/q</i>" );
($ap,$q,$p) = (str2poly($a{'p'}),str2poly($a{'q'}),str2poly($u{'p'})) ;
print "<table border=0>" ;
if (! defined $p) {
  no_input($nam{'p'}) ;
  goto L1 ;
}
if( $p != $ap ) {
  wrong_input($nam{'p'}) ;
}
else {
  true_input($nam{'p'}) ;
  $ret=3 ;
}
  $u{'pdivq'} =~ s/\s//g ;
  #print $u{'pdivq'}, "\n" ;
  $u{'pdivq'} =~ s/\++-|-\++/-/g ;
  $u{'pdivq'} =~ s/\++|--/\+/g ;
  $u{'pdivq'} =~ s/(\D)x/${1}1x/g ;
  #print $u{'pdivq'}, "\n\n" ;
  @poly = ( $u{'pdivq'} =~
      /\(?([^\(\)\/]+)\)?\/\(?([^\(\)]+)\)?(\^2)?/g ) ;
  #print join "\n", @poly, $#poly, "\n"; 
  for (my $i=0, $j=0; $i<=$#poly; $i++) {
    next if $poly[$i] eq "" || $poly[$i] eq "^2" ;
    my @tmp = ($poly[$i] =~ /[^\^][0-9]+|^[0-9]+/g) ;
    @tmp = reverse @tmp if $poly[$i] =~ m/(?<!\^)\d$/ ;    
    $pl[$j] = list2poly (@tmp) ;
    if (! defined $pl[$j] || $pl[$j] == 0) {
      wrong_input($nam{'pdivq'}) ;
      goto L1
    } ;  
    if ( $poly[$i+1] eq "^2" ) {
      $sqr = $pl[$j] ;
      goto L1 if $sqr == 0 ;
      $pl[$j] *= $pl[$j] ;
    }
      $j++ ;
  } ; 
    $pre_p = ( $pl[0]*$pl[3]*$pl[5]*$pl[7] +
               $pl[2]*$pl[1]*$pl[5]*$pl[7] +
               $pl[4]*$pl[1]*$pl[3]*$pl[7] +
               $pl[6]*$pl[1]*$pl[3]*$pl[5]
             ) / $sqr ;
    $pre_q = $pl[1]*$pl[3]*$pl[5]*$pl[7] / $sqr ;
#    $gcd = $pre_q->gcd($pre_p) ;
#    $gcd /= $gcd->coeff($gcd->degree) ;
#    $get_p = $pre_p/$gcd ;
#    $get_q = $pre_q/$gcd ;
#    print "\n$pre_p\n$pre_q\n" ; 
if ( $pre_q % $q == 0 && $pre_q->degree == $q->degree ) {
  true_input($nam{'q'}) ;
  $ret+=2 ;
}
else {
  wrong_input($nam{'q'}) ;
  goto L1 ;
}
if ($p != 0 && $q != 0 && $pre_p % $p == 0 && $pre_p->degree == $p->degree && $pre_p/$p == $pre_q/$q){
  true_input($nam{'pdivq'}) ;
  $ret+=7 ;
}
else {
  wrong_input($nam{'pdivq'}) ;
  # print "\n",$pre_p/$p, "\n" , $pre_q/$q ,"\n"
}

L1: print "</table>" ;
exit ($ret) ;

