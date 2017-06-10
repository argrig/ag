#!/usr/bin/perl
use Data::Dumper ;

$file = $ARGV[0] ;
$txt = `cat $file` ;
@inc = $txt =~ /(extends|include)\s+(\S+)/g ;
#print Dumper(@inc) ;
foreach $f (@inc) {
  if ( $f ne 'extends' && $f ne 'include' ) {
    $out = `basename $f ".pug"` ; chomp $out ;
    $g = "view/dep/". $out . ".dep" ;
    `echo "$file" >> "$g"` if ! `grep "$file" "$g"` ;
  }
}
