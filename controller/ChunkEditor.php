<?php
class ChunkEditor {
  function handle($route) {
    $db = (new MongoDB\Client)->book;
    $res = $db->chunk_types->find() ;
    foreach($res as $doc)
      foreach($doc as $key=>$value) {
      echo $key,"=>",var_dump($value),"<br>" ;
    };
  }
}
