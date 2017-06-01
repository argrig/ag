<?php

class Db extends PDO {
  function __construct() {
    parent::__construct(DB_URI, DB_USER, DB_PASS) ;
    //parent::setAttribute(parent::ATTR_ERRMODE, parent::ERRMODE_EXCEPTION);
    //parent::setAttribute(parent::ATTR_EMULATE_PREPARES,false); 
  }
  function sql_error_handle($error, $status='failed') {
    return array_merge(array('status'=> $status),$error) ;
  }
  function q($query,$params=NULL) {
    if (is_null($params)) {
      if(! parent::query($query)) {
        return $this->sql_error_handle(parent::errorInfo()) ;
      }
      else{
        return $this->sql_error_handle($res->fetchall(parent::FETCH_ASSOC),'ok') ;
      }
    }
    else {
      foreach($params as $key=>$val) {strip($params[$key]);}
      if(! $data = parent::prepare($query)) {
        return $this->sql_error_handle($data->errorInfo());
      }
      else{
        if(! $data->execute($params)) {
          return $this->sql_error_handle($data->errorInfo());
        } 
        else {
          return $this->sql_error_handle($data->fetchall(parent::FETCH_ASSOC),'ok') ;
        }
      }
    }
  }
  function insert($table,$fields,$values,$mode='insert') {
    $command = ($mode == 'insert') ? "INSERT INTO " : "REPLACE INTO " ;
    $fld_list = '(' . implode(',',$fields) . ')' ;
    if(array_values($values) == $values && is_array($values[0])) {
      if(array_values($values[0]) != $values[0]) {
        foreach($values as $key=>$val) {
          $values[$key] = assoc2array($val,$fields) ;
        }
      }
      $one = '(' . implode(',', array_fill(0,count($values[0]),'?')) . ')' ;
      $val_place = implode(',', array_fill(0,count($values),$one)) ;
      $plain=array() ;
      foreach($values as $val) {
        $plain = array_merge($plain,$val) ;
      }
      $values = $plain ;
    }
    else {
      if(array_values($values) != $values) {
          $values = assoc2array($values,$fields) ;
      }
      $val_place = '(' . implode(',', array_fill(0,count($values),'?')) . ')' ;
    } ;
    $query = $command . $table . ' ' . $fld_list . ' VALUES ' . $val_place ;
    //print_r ($query) ;
    return $this->q($query, $values) ;
  }
}
