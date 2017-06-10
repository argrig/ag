<?php
function stripAll(&$str) {
  return preg_replace('/[^a-zA-Z0-9_]/','',$str) ;
}
function strip(&$str) {
  return preg_replace('/[^[:print:]]/','',$str) ;
}
function assoc2array($arr,$fields) {
  $tmp = array() ;
  foreach($fields as $fld) {
    array_push($tmp, $arr[$fld]) ;
  }
  return $tmp ;
}
function sendJSON($arr) {
  echo json_encode($arr, JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES); 
}
