#!/usr/bin/perl
 
use File::Basename ;
use DBI();
	my $db = DBI->connect("DBI:mysql:database=exam; host=localhost", "root", "argr");
	$db->do("SET character_set_connection=utf8") or die ("no conn") ;
	$db->do("SET character_set_client=utf8")  or die ("no client") ;

	$gen_prog = basename $ARGV[0], ".htm";
	$req = "select * from problems where gen_prog like \'$gen_prog\%\'" ;
	
	print "$req\t" ;
  	
	$st = $db->prepare($req) ;
  	$rowz = $st->execute()  or die ("Can't find problem !!!\n") ;
	print "$rowz\n" ;
	
if ($rowz == 1) { 
	$text = `cat $ARGV[0]` ;
	$req = 	"update problems set ans_code=".$db->quote($text).
			" where gen_prog like \'$gen_prog\%\'" ;
  	$st = $db->prepare($req) ;
  	$st->execute()  or die ("Can't update !!!\n") ;
}
