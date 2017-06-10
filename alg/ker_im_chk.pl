#!/usr/bin/perl

use File::Basename ;

$DIM = 6 ;
$dir = '.' ;
$ret = 0 ;

sub err_mes( @ ) {
  print "<br><font color=green> $_[0] </font>\n" if ($_[1]&1) == 1 ;
  print "<br><font color=red>   $_[0] </font>\n" if ($_[1]&1) == 0 ;
  exit ($ret) if ($_[1]&2) == 0;
}

$ans = `cat $ARGV[0] | grep % | sed -e's/%//g'` ;
$usr_ans = `cat $ARGV[1]` ;

y/\t \n\r/  \n/s foreach ($ans, $usr_ans);
s/ *\n */\n/g    foreach ($ans, $usr_ans);

%a = ($ans =~ /(\w+)=\n([^a-z^A-Z]+)/g) ;
%u = ($usr_ans =~ /(\w+)=\n([^a-z^A-Z]+)/g) ;
%names = (
    'g_ker'   , 'порождающая матрица ядра',
    'h_ker'   , 'проверочная матрица ядра',
    'g_im'    , 'порождающая матрица образа',
    'h_im'    , 'проверочная матрица образа',
    'g_its'   , 'порождающая матрица пересечения',
    'g_sum'   , 'порождающая матрица суммы',
    'dim_ker' , 'размерность ядра',
    'dim_im'  , 'размерность образа',
    'dim_its' , 'размерность пересечения',
    'dim_sum' , 'размерность суммы',
) ;

$dim_g_ker=$dim_h_im=$a{dim_ker} ;
$dim_h_ker=$dim_g_im=$a{dim_im} ;
$dim_g_its=$a{dim_its} ;
$dim_g_sum=$a{dim_sum} ;

$u_dim_g_ker=$u_dim_h_im=$u{dim_ker} ;
$u_dim_h_ker=$u_dim_g_im=$u{dim_im} ;
$u_dim_g_its=$u{dim_its} ;
$u_dim_g_sum=$u{dim_sum} ;

$prog    =  basename($0, '.pl') ;
$bad_input = "" ;
$ret = 0 ;

while( ($key,$val) =  each %u ) {
  $len = split / |\n/, $u{$key} ;
  $real_len = split / |\n/, $a{$key} ;
  if ($len != $real_len || $u{$key} =~ /[^0-9\+\-\n ]/) {
    err_mes("Неверный ввод: $names{$key}", 2) ;
    $bad_input .= "$key "
  }
  elsif ($key !~ /dim/) {
    $data = join " ",  ( ${"dim_".$key}, $DIM, $a{$key}, $u{$key} ) ; 
    $res = `echo "$data" | $dir/$prog` ;
    if ($res eq "ok") {
      err_mes("Попадание: $names{$key}", 3) ;
      $ret += 2 ;
      if ($key =~ "g_") {
        $cdim = "dim_" . $' ; 
        if ($bad_input !~ /$cdim/) {
          if ($u{$cdim} == $a{$cdim} ) {
            err_mes("Попадание: $names{$cdim}", 3) ;
            $ret += 1 ;
          }
          else {
            err_mes("Ошибка вычисления: $names{$cdim}", 2) ;
          }
        }
      }
    }
    else {
      err_mes("Ошибка вычисления: $names{$key}", 2) ;
    }
  }
}

exit($ret)

