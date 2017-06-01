<?php
session_start() ;
include '../config/config.php' ;
include '../config/helper.php' ;
$db = new Db() ;
$router = new Router() ;
$router->route() ;

