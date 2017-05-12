#!/usr/bin/perl

$file = $ARGV[0] ;
$txt = `cat $file` ;
%inc = $txt =~ /(extends|include)\s+(\S+)/g ;
foreach $f (values %inc) {
  $out = `basename $f ".pug"` ; chomp $out ;
  $g = "view/dep/". $out . ".dep" ;
  `echo "$file" >> "$g"` if ! `grep "$file" "$g"  2>/dev/null` ;
}
