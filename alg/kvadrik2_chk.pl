#!/usr/bin/perl

use func ;
use PDL  ;

$eps = 0.0001 ;
$0 =~ /.pl/ ; $run = $` ;
$ret=0 ;
$dim=2 ;
$my_ans = `cat $ARGV[0]` ;

my %a = hash_var($my_ans) ;
my %u = query_decode($ARGV[1]) ;

# print "$u{'name'}\n$a{'name'}" ; exit ;
%nam = (
  'name' => "тип кривой", 'eqn' => "канонический вид",
  'C' => "матрица перехода", 'd' => "вектор сдвига"
) ;

$u{'eqn'} =~ s/[^012+-=\^xy]//g ;
$a{'eqn'} =~ s/[^012+-=\^xy]//g ;

print "<table border=0>" ;
if( $u{'eqn'} ne $a{'eqn'} ) {
  wrong_input($nam{'eqn'}) ;
}
else {
  true_input($nam{'eqn'}) ;
  if ($u{'name'} ne $a{'name'}) {
    wrong_input($nam{'name'}) ;
  }
  else {
    true_input($nam{'name'}) ;
    $u{'C'} =~ s/s[^(]*\(/sqrt\(/g ;
    $u{'d'} =~ s/s[^(]*\(/sqrt\(/g ;
    $C = str2pdl($u{'C'}) ;
    goto L1 if '22' ne ( join '', dims($C) ) ;
    $b = str2pdl($a{'b'}) ;
    $Q = str2pdl($a{'Q'}) ;
    $Q_cn = str2pdl($a{'Q_cn'}) ;
    $Q1 = transpose($C) x $Q x $C ;
    $det = abs ($C->det()) ; 
    $C_ok = max ( abs ( transpose($C) x $Q x $C  - $Q_cn ) ) < $eps 
      && $det > $eps  ;
    $b_cn = pdl (0,1) if $a{'type'} == 1 && $a{'r'} == 1 ;
    $b_cn = pdl (0,0) if $a{'type'} == 2 ;
    $c_cn = $a{'a'} ;
    $c    = $a{'c'} ;

    if ($C_ok == 1) { true_input($nam{'C'}); $ret+=6 ;}
    else { wrong_input($nam{'C'}) ; goto L1; } ;

    $d = str2pdl($u{'d'}) ;
    goto L1 if '21' ne ( join '', dims($d) ) ;
    $dt = transpose($d) ;
    $b_ok = max ( abs ( 2*($d x $Q x $C) + $b x $C - $b_cn ) ) < $eps ;
    $c_ok = max ( abs ( $b x $dt + $d x $Q x $dt + $c -$c_cn ) ) < $eps ;
    if ($b_ok == 1 && $c_ok == 1) { true_input($nam{'d'}); $ret+=3 ; } 
    else { wrong_input($nam{'d'}) ;} ;

  }
}

L1: print "\n</table>" ;

exit ($ret) ;

