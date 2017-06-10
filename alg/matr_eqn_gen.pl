#!/usr/bin/perl

if (! @ARGV) {
	print "Прграмма составления и решения матричных уравнений. Формат вызова:\n" ;
	print "$0 n=num x=char d1=num d2=num maxdet=num\n" ;
	print "n\t- размерность квадратной матрицы\n" ;
	print "x\t- l(eft) или r(ight), справа или слева неизвестная\n" ;
	print "d1\t- нижняя граница для целочисленных элементов матрицы\n" ;
	print "d2\t- верхняя граница для целочисленных элементов матрицы\n" ;
	print "maxdet\t- максимальное значение для определителя \n" ;
}

foreach $arg (@ARGV) {
	@a = (@a , split /=/, $arg) ;
}
%args = @a ;
$n	= ($args{n}) ? $args{n} : 0 ;
$x	= ($args{x} =~ /l/) ? 1 : 0 ; 
$d1	= ($args{d1}) ? $args{d1} : 0 ;
$d2	= ($args{d2}) ? $args{d2} : 0 ;
$maxdet = ($args{maxdet}) ? $args{maxdet} : 0 ;

@prog = split /\./, $0 ;
print `echo "$n $x $d1 $d2 $maxdet \n" | \.$prog[$#prog-1]` ;