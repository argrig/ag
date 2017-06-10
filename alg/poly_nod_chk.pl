#!/usr/bin/perl

$ans = `cat $ARGV[0]` ;
$ans =~ /\%/ ;
$ans = $' ;
$ans =~ y/\n\t\r\%\+\,\; /        /s ;
$ans =~ s/ //g ;
$ans =~ /nod=/ ; $nod = $' ; 

$usr_ans = `cat $ARGV[1]` ;
$usr_ans =~ y/\n\t\r\%\+\,\; /        /s ;
$usr_ans =~ s/ //g ;
if ( $usr_ans =~ /nod=/ ) { $usr_nod = $'; } ; 

$ret = 0 ;

if ($usr_nod eq "") {
  print "<br><font color=red>Вы не ввели НОД</font>"
}
elsif ($nod eq $usr_nod) {
  print "<br><font color=green> НОД вычислен верно</font>" ;
  $ret += 7 ;
}
else {
    print "<br><font color=red>Неверно вычислен НОД</font>" ;
}

exit ($ret) ;
