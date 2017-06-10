#!/usr/bin/perl

$ans = `cat $ARGV[0] | grep %` ;
$usr_ans = `cat $ARGV[1]` ;
$ans =~ s/%//g ;

($empty,%val) = split /\n*([^\n]+)=\n/, $ans  ;
$usr_ans =~ y/,; /   /ds ;
$usr_ans =~ s/[^\d ]//g ;

$prog = $0 ;
$prog =~ s/\.pl$// ;

$test = `echo "$val{'A'} $val{'b'} $usr_ans $val{'mod'}" | $prog.run` ;

if ($test != 3) {
	err_mes_smpl("Задача решена неверно",0) ;
}
else {
	err_mes_smpl("Задача решена верно",1) ;
	$ret=7 ;
}

exit ($ret) ;

sub err_mes_smpl {
  print "<br><font color=green> $_[0] </font>\n" if $_[1] == 1 ;
  print "<br><font color=red>   $_[0] </font>\n" if $_[1] == 0 ;
}

