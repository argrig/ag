<!DOCTYPE html>
<html lang="ru">
  <head>
    <title>
      3D!Book
    </title>
    <script src="/js/jquery-3.2.1.min.js"></script>
    <script src="/js/bootstrap.min.js"></script>
    <link rel="stylesheet" type="text/css" href="/css/bootstrap.min.css">
    
  </head>
  <body>
    <header>
      
      <nav class="navbar navbar-default">
        <div class="container-fluid">
          <div class="navbar-header">
            <a class="navbar-brand">
              <img src="img/ag2.png" height="130%">
            </a>
          </div>
          <div class="navbar-header">
            <a class="navbar-brand">
              Алгебра и Геометрия
            </a>
          </div>
          <ul class="nav navbar-nav">
            <li class="active">
              <a href="/" alt="Домой" title="Домой">
                <span class="glyphicon glyphicon-home"></span>
              </a>
            </li>
            <li class="active">
              <a href="/edit" title="Редактировать">
                <span class="glyphicon glyphicon-pencil"></span>
              </a>
            </li>
          </ul>
        </div>
      </nav>
      
    </header>
    
    
    
    <div class="container">
      <div class="col-md-6">
        <div class="jumbotron">
          <h2>
            Добро пожаловать на портал &laquo;<?php echo SITE_NAME ?>&raquo; !
          </h2>
          <p>
             Здесь изучают общую и линейную алгебру и аналитическую геометрию
            в пределах стандартных университетских курсов для математических специальностей.
            Для представления материала используется предложенная нами технология
            <b> 3D!Book</b>.
          </p>
        </div>
      </div>
      <div class="col-md-6">
        <div class="jumbotron">
          <h2>
            Технология 3D!Book
          </h2>
          <p>
            Основные идеи:
            <ul>
              <li>
                теоретический материал представлен <b>не</b> в виде плоского изложения в стандартном книжном формате,
                а в виде логического дерева понятий, определений и теорем
              </li>
              <li>
                каждый может сам сделать для себя нужную выборку и получить фрагмент в книжном формате или же
                пользоваться информацией в представленном виде
              </li>
              <li>
                в эту же структуру дерева включены и задачи, причем как теоретического так и практического характера
              </li>
            </ul>
          </p>
        </div>
      </div>
    </div>
    <hr>
    <footer>
      &copy; 2004 &ndash; <?php echo date("Y"),"&nbsp;&nbsp;",AUTHOR,". Все права защищены." ?>
    </footer>
  </body>
</html>