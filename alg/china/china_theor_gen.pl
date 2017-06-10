#!/usr/bin/perl

$N = 3 ; # number of equations 
$A_MIN = 0 ; # minimal module,  if 0 then =100 
$A_MAX = 0 ; # maximal module,  if 0 then =200 
$X_MIN = 0 ; # minimal residue, if 0 then =20 
$X_MAX = 0 ; # maximal residue, if 0 then =99 
# see corresponding c++ code for detailes

if (! @ARGV) {
  print "Китайская теорема об остатках \n" ;
  exit ;
}

$0 =~ /\.pl$/ ; $prg =  $` ;
($n,$x,$pre_x,$pre_a) = split ',', `echo $N $A_MIN $A_MAX $X_MIN $X_MAX | $prg` ;
@prob{split ' ', $pre_x} = split ' ', $pre_a ;

$out =  "Найти минимальное положительное решение системы сравнений:\n".
        "\$\$\n\\left\\{\n\\begin{array}{lcrcc}\n" ;
$mod_prod=1 ;
while (($key,$val) = each (%prob)) {
  $mod_prod*=$val ;
  $out .= "x & \\equiv & $key &  mod & $val \\\\\n"
}
$x%=$mod_prod ;
$out .= "\\end{array}\n\\right.\n\$\$\n\n".
        "\%N=\n\%$N\n\n\%x=\n\%$x\n\n\%data=\n\%$pre_x $pre_a" ;
print $out ;
$ans = "Ответ:\n\$\$\nx=$x\n\$\$\n" ;
print STDERR $ans ;
exit ;

