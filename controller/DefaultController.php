<?php
class DefaultCtrl($rt_parts) {
  function handle() {
    echo "Here is default->handle()" ;
    foreach($rt_parts as $part) {echo $part," ";}
  }
}
