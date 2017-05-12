<?php
define('SITE_NAME','Алгебра и Геометрия') ;
define('AUTHOR','А.А. Григорянц') ;
define('MODEL_DIR','../model/') ;
define('CONTROLLER_DIR','../controller/') ;
define('CONFIG_DIR','../config/') ;
define('ROUTES_JSON',CONFIG_DIR . 'routes.json') ;
define("DB_NAME","book") ;

//DEBUG SETTING -- MUST BE CHANGED FOR PRODUCTION
ini_set('display_errors', 1);


//AUTOLOADER
require '../vendor/autoload.php' ;
set_include_path(get_include_path() . PATH_SEPARATOR . MODEL_DIR . PATH_SEPARATOR . CONTROLLER_DIR) ;
spl_autoload_register(function($class){
  include $class . '.php' ;
}) ;

