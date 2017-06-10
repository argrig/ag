<?php

//GLOBAL CONSTANTS
define('SITE_NAME','Алгебра и Геометрия') ;
define('AUTHOR','А.А. Григорянц') ;
define('MODEL_DIR','../model/') ;
define('CONTROLLER_DIR','../controller/') ;
define('VIEW_DIR','../view/') ;
define('CONFIG_DIR','../config/') ;
define('FILES_DIR','../files/') ;
define('ROUTES_JSON',CONFIG_DIR . 'routes.json') ;
define('DB_URI','mysql:host=localhost;dbname=3Dbook;charset=UTF8') ;
define('DB_USER','root') ;
define('DB_PASS','argr') ;
define('SQL_ERR_DUPLICATE',23000) ;
define('SESS_DURATION',4800) ;

//DEBUG SETTING -- MUST BE CHANGED FOR PRODUCTION
ini_set('display_errors', 1);

//AUTOLOADER
require '../vendor/autoload.php' ;
set_include_path(get_include_path() . PATH_SEPARATOR . MODEL_DIR . PATH_SEPARATOR . CONTROLLER_DIR) ;
spl_autoload_register(function($class){
  include $class . '.php' ;
}) ;

