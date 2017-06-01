<?php
include '../config/config.php' ; 

if( password_verify('22222222','$2y$10$NQxKq2EAalb2bGOh02urWet67G3AV.XktdQHh6LxsI2YvRvPGrCxu') ) {
  echo "OK\n" ;
} else { echo "NO";} ;
exit ;
/*
$db = new Db() ;

$val = array(
  array('num'=>444444444,'name'=>'qqqqsssss','id'=>6),
  array('name'=>'mymy','num'=>3434,'id'=>4),
  array('num'=>444444444,'name'=>'qqqqsssss','id'=>5)
) ;
$fld = array('id','name','num') ;
$db->insert('test',$fld,$val) ;

$res = $db->q("SELECT * FROM test") ;
print_r ($res) ;

/*
$ar = array(array(1,2,3,'"ok"'),array(4,5,6,'"no"')) ;
print_r(array_merge_recursive($ar)) ;
/*
  $one = '(' . implode(',', array_fill(0,count($ar[0]),'?')) . ')' ;
  $val_place = implode(',',array_fill(0,count($ar),$one)) ;

  print $val_place ;
*/
    function strip($str) {
      return preg_replace('/[^a-zA-Zа-яА-Я0-9_ ]/u','',$str) ;
    }
echo strip("qwe йцу qwerrr $#@!~ ФЫВ^&*(){}|ДЖ 097") ;
