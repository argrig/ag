#!/usr/bin/perl

if (! @ARGV) {
  print "���������������� ��������� ��������\n" ;
}

$prog = $0 ;
$prog =~ s/\.pl$// ;
@data = `$prog` ;

$n = @poly = split ' ', $data[0] ;
@x    = split ' ', $data[1] ;
@y    = split ' ', $data[2] ;

print "����� ��������� \$f\$ ������� �� ���� \$$n\$, \n����������� ��������� ��������:\\\\\n" ;
for $i (0 .. $#x) {
	print '$f('.$x[$i].") & = & ".$y[$i]." \$\\\\\n" ;
} 
