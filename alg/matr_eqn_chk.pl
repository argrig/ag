#!/usr/bin/perl

$answer = `egrep '%|^\$' $ARGV[0] | sed -e 's/%//'` ;
$answer =~ s/\n+// ;
%ans =  split "=\n|\n\n", $answer ;
foreach $val (values %ans) { $val =~ s/\s+//g  } ;

$usr_answer = `cat $ARGV[1] | sed -e's/\r//g'` ;
$usr_answer =~ s/\n{2,}/\n\n/g ;
%usr_ans =  split "=\n|\n\n", $usr_answer ;
foreach $val (values %usr_ans) { $val =~ s/\s+//g  } ;
$ret = 0 ;

if ($usr_ans{'det'} eq "") {
  print "<br><font color=red>Вы не ввели значение определителя</font>"
}
elsif ($usr_ans{'det'} != $ans{'det'}) {
  print "<br><font color=red>Неверно вычислен определитель</font>" ;
}
else {
  print "<br><font color=green> Определитель вычислен верно</font>" ;
  $ret += 1 ;
}

if ($usr_ans{'rvs'} eq "") {
  print "<br><font color=red>Вы не ввели значение присоединенной матрицы</font>"
}
elsif ($ans{'rvs'} ne $usr_ans{'rvs'}) {
  print "<br><font color=red>Неверно вычислена присоединенная матрица</font>" ;
}
else {
  print "<br><font color=green> Присоединенная матрица вычислена верно</font>" ;
  $ret += 2 ;
}

if ($usr_ans{'X'} eq "") {
  print "<br><font color=red>Вы не ввели значение матрицы X</font>"
}
elsif ($ans{'X'} ne $usr_ans{'X'}) {
  print "<br><font color=red>Неверно вычислена матрица X</font>" ;
}
elsif ($ans{'X'} eq $usr_ans{'X'}) {
  print "<br><font color=green> Матрица X вычислена верно</font>" ;
  $ret += 3  ;
}

exit ($ret) ;
