#!/usr/bin/perl

use DBI();
 
my $db = DBI->connect("DBI:mysql:database=alg; host=localhost", "root", "argr");
$db->do("SET character_set_connection=koi8r") or die ("no conn") ;
$db->do("SET character_set_client=koi8r")  or die ("no client") ;

@t_id_ = split /_/ , $ARGV[0] ;
$t_id = $t_id_[1] ;
$db->do ( "delete from theor where type_id=" . $t_id ) ;

$text = `cat $ARGV[0]` ;
$text =~ s/(\n)+/\n/g ;
@que = split /\#/, $text ;

for $q (@que) {
  $i++ ;
  $q =~ /(\d)+;(\d)+;(\d)+\n/ ;
# print $& ;
  $htm = $` ; $params = $& ;
  $htm =~ s/\n/ /g ; 
  ($true, $t_id, $ch_id) = split /;/, $params ;
#  print $true  ."--". $t_id . "--". $ch_id ;
  $query =  "insert into theor set html=".$db->quote($htm). ", tr=$true, type_id=$t_id, ch_id=$ch_id" ;
#  print $query ;
  $st = $db->prepare($query) ;
  $st->execute()  or die ("наша ошибка $i");
}
	


