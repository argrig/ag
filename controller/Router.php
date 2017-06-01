<?php

class Router {
  private $rtab, $route, $len, $parts, $act ;
  function __construct() {
    //$this->rtab = json_decode(file_get_contents(ROUTES_JSON), true) ;
    $this->route = filter_var($_SERVER['REQUEST_URI'], FILTER_SANITIZE_URL) ;
    $this->parts = explode('/', $this->route) ;
    array_shift($this->parts) ;
    $this->act = array_shift($this->parts) ;
    $this->len = count($this->parts) ;
  }
  function route() {
    switch($this->act) {
      case "edit":
        $edit = new ChunkEditor() ;
        $edit->handle($this->parts) ;
      break;
      case "login":
        $user = new User() ;
        $user->login($this->parts) ;
      break;
      case "register":
        $user = new User() ;
        $user->register($this->parts) ;
      break;
      default:
        $ctrl = new DefaultCtrl() ;
        $ctrl->handle($this->parts) ;
    }
    /*
        if(array_key_exists($this->parts[0],  $this->rtab)) {
          $key = array_shift($this->parts) ;
          $ctrl_name = $this->rtab[$key]['module'] ; 
        }
        else {
          $ctrl_name = 'DefaultCtrl' ;
        }
        $ctrl = new $ctrl_name ;
        $ctrl->handle($this->parts) ;
    */
  }
}
