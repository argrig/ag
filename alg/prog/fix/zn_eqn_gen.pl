#!/usr/bin/perl

if (! @ARGV) {
  print "���������� �������� ����� \n" ;
}

@prog = split /\./, $0 ;
print `\.$prog[$#prog-1]` ;