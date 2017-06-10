#!/usr/bin/perl

use PDL ;

$A = pdl [[1,0,0],[0,2,0],[0,0,3]] ;
$det = $A->det() ;
print $A , $det ;

