#!/usr/bin/perl

if (! @ARGV) {
  print "Вычисление НОД двух многочленов \n" ;
}

@prog = split /\./, $0 ;

while ($ans !~ /Найти/) {
  $ans = `\.$prog[$#prog-1]` ;
}

print $ans ;