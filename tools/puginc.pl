#!/usr/bin/perl

$file = $ARGV[0] ;
$txt = `cat $file` ;
%inc = $txt =~ /(extends|include)\s+(\S+)/g ;
foreach $f (values %inc) {
  print $f . " " ;
}
