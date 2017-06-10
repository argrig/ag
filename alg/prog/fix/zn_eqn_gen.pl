#!/usr/bin/perl

if (! @ARGV) {
  print "Арифметика конечных колец \n" ;
}

@prog = split /\./, $0 ;
print `\.$prog[$#prog-1]` ;