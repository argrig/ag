<?php
include '../config/config.php' ;
include '../config/helper.php' ;

//Redirect all traffic to HTTPS
if(empty($_SERVER['HTTPS']) || $_SERVER['HTTPS'] == "off"){
  $redirect = 'https://' . $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI'];
  header('HTTP/1.1 301 Moved Permanently');
  header('Location: ' . $redirect);
  exit();
}

//Start SESSION
session_start() ;
session_regenerate_id() ;

//Init DATABASE
$db = new Db() ;

//Begin ROUTING
$router = new Router() ;
$router->route() ;

