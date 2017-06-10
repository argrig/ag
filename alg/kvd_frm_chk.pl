#!/usr/bin/perl

use func ;
use PDL  ;

$dim=3 ;
$my_ans = `cat $ARGV[0]` ;
$ret=0 ;
$eps=0.00001 ;
@params=('rk','r_plus','r_minus','degen') ;
@matr=('Q1','Q_cn') ;

my %nam ;
my %a = hash_var($my_ans) ;
my %u = query_decode($ARGV[1]) ;

$a{'r_plus'} = $a{'rk'} - $a{'r_minus'} ;
$a{'degen'} = ($a{'rk'} != $dim) ? 1 : -1 ;

$nam{'rk'}="ранг <i>r</i>" ;
$nam{'r_plus'} = "положительный индекс инерции <i>r<sub>+</sub></i>" ;
$nam{'r_minus'}= "отрицательный индекс инерции <i>r<sub>-</sub></i>" ;
$nam{'degen'}="вырожденность/невырожденность" ;
$nam{'C'}="матрица перехода" ;
$nam{'Q_cn'}="матрица канонического вида" ;
$nam{'Q1'}="матрица квадратичной формы" ;

print "<table border=0>\n" ;
for $key (@matr) {
	${"u$key"} = str2pdl($u{$key}) ;
#    print "\n\n" . ${"u$key"} . "\n\n" ;
	if ("$dim$dim" eq join '', dims(${"u$key"})) {
	  ${"a$key"} = str2pdl($a{$key}) ;
	  if (max(abs(${"u$key"} - ${"a$key"}))<$eps) {
      $ok .= 1 ;
	    true_input($nam{$key}) ;
	  }
	  else {wrong_input($nam{$key}) ; }
	} ;
}

for $key (@params) {
	if ( $a{$key} == $u{$key} ) {
    $ok .= 1 ;
	  true_input($nam{$key}) ;
	}
	else {
	  wrong_input($nam{$key});
	}
}


if ($ok eq '111111') { $ret=4 ;}
else { goto L1 ; } ;

$u{'C'} =~ s/s[^(]*\(/sqrt\(/g ;
$C = str2pdl($u{'C'}) ;
goto L1 if "$dim$dim" ne join '', dims $C ;
$CT = transpose($C) ;
if ( max(abs($CT x $uQ1 x $C - $aQ_cn)) < $eps ) {
  $ret+=8 ;
  true_input($nam{'C'}) ;
}
else { wrong_input($nam{'C'}); } ;

L1: print "</table>" ;

exit ($ret) ;

sub str2pdl {
  my $str = $_[0] ;
  $str =~ y/\r \n/\n,\n/s ;
  $str =~ s/(^|\n),/$1/g ;
  $str =~ s/\n(.)/\],\[$1/g ;
  chomp($str) ;
  return pdl eval "[[$str]]" ;
}
