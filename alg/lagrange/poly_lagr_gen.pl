#!/usr/bin/perl

if (! @ARGV) {
  print "Интерполяционный многочлен Лагранжа\n" ;
}

$prog = $0 ;
$prog =~ s/\.pl$// ;
@data = `$prog` ;

$n = @poly = split ' ', $data[0] ;
@x    = split ' ', $data[1] ;
@y    = split ' ', $data[2] ;

print "Найти многочлен \$f\$ степени не выше \$$n\$, \nпринимающий следующие значения:\\\\\n" ;
for $i (0 .. $#x) {
	print '$f('.$x[$i].") & = & ".$y[$i]." \$\\\\\n" ;
} 
