<?php

class Router {
  private $rtab, $route, $len, $parts ;
  function __construct() {
    $this->rtab = json_decode(file_get_contents(ROUTES_JSON), true) ;
    $this->route = filter_var($_SERVER['REQUEST_URI'], FILTER_SANITIZE_SPECIAL_CHARS) ;
    $this->parts = explode('/', $this->route) ;
    array_shift($this->parts) ;
    $this->len = count($this->parts) ;
  }
  function route() {
    if(array_key_exists($this->parts[0],  $this->rtab)) {
      $key = array_shift($this->parts) ;
      $ctrl_name = $this->rtab[$key]['module'] ; 
    }
    else {
      $ctrl_name = 'DefaultCtrl' ;
    }
    $ctrl = new $ctrl_name ;
    $ctrl->handle($this->parts) ;
  }
}
