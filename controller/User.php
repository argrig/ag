<?php

class User {
  function login($parts){
    global $db ;
    header('Content-Type: application/json');
    strip($_POST['login']);
    strip($_POST['passwd']);
    $values = array($_POST['login'],$_POST['login']) ;
    $query = <<<EOF
      SELECT u.id uid, u.name name, surname, login, passwd, email, u.verif verif, created, lastlog, unvid, roleid,
        r.name rname, r.title rtitle, r.brief rbrief, unv.name unvname, abbr, unv.verif unvverif
        FROM users u, univers unv, roles r
        WHERE ( u.login = ? OR u.email = ? ) AND u.unvid=unv.id AND u.roleid = r.id ;
EOF;
    $qret = $db->q($query,$values) ;
    $user = (isset($qret[0])) ? $qret[0] : $qret ;
    if($qret['status']=='failed') {
      sendJSON(array('status'=>'failed','error'=>'Ошибка при попытке входа')) ; 
    }else if(isset($user['passwd']) && password_verify($_POST['passwd'],$user['passwd'])){
      unset($user['passwd']) ;
      foreach($user as $key=>$val) {$_SESSION[$key] = $val ;}
      foreach(array('unvid','roleid','rname','unvverif','secure') as $key) {unset($user[$key]);}
      sendJSON($user) ;
    }else {
      sendJSON(array('status'=>'failed','error'=>'Неверный логин/email/пароль')) ;
    }
  }  
  function register($parts) {
    global $db ;
    header('Content-Type: application/json') ;
    ini_set('display_errors',0) ;
    $values = array() ;
    $table  = 'users' ;
    $fields = array('name','surname','login','email','passwd') ;
    foreach($fields as $fld) {
      if ($fld != 'passwd') { array_push($values,$_POST[$fld]) ; }
      else { array_push($values,password_hash($_POST[$fld],PASSWORD_BCRYPT)); } 
    }
    $res = $db->insert($table,$fields,$values) ;
    //echo json_encode($values, JSON_UNESCAPED_UNICODE) ;
    //echo "my" . print_r($res) . "my" ;
    if($res['status'] == 'failed') {
      switch($res[0]) {
        case SQL_ERR_DUPLICATE:
          $match = array() ;
          preg_match_all("/'(\S+)'/",$res[2],$match) ;
          $return = array('status'=>'failed','error'=>$match[1][1]) ;
          sendJSON($return) ;
        break;
      }
    }
    else {
      sendJSON(array('status'=>'ok')) ;
    }
  }
}
