<!DOCTYPE html>
<html lang="ru">
  <head>
    <title>
      3D!Book
    </title>
    <script src="/js/jquery-3.2.1.min.js"></script>
    <script src="/js/bootstrap.min.js"></script>
    <script src="/js/my.js"></script>
    <link rel="stylesheet" type="text/css" href="/css/bootstrap.min.css">
    <link rel="stylesheet" type="text/css" href="/css/my.css">
    
  </head>
  <body>
    <header>
      
      
      <nav class="navbar navbar-default">
        <div class="container-fluid">
          <div class="navbar-header">
            <a class="navbar-brand">
              <img src="img/ag2.png" height="160%">
            </a>
            <a class="navbar-brand">
              Алгебра и Геометрия
            </a>
          </div>
          <ul class="nav navbar-nav">
            <li class="active">
              <a href="/" title="Начало">
                <span class="glyphicon glyphicon-home"></span>
              </a>
            </li>
            <li>
              <a href="/edit" title="Редактирование">
                <span class="glyphicon glyphicon-pencil"></span>
              </a>
            </li>
            <li>
              <a href="/view" title="Изучение">
                <span class="glyphicon glyphicon-sunglasses"></span>
              </a>
            </li>
            <li>
              <a href="/solve" title="Задачи">
                <span class="glyphicon glyphicon-education"></span>
              </a>
            </li>
            <li>
              <a href="/test" title="Тесты">
                <span class="glyphicon glyphicon-saved"></span>
              </a>
            </li>
            <li>
              <a href="/stats" title="Статистика">
                <span class="glyphicon glyphicon-stats"></span>
              </a>
            </li>
          </ul>
          <ul class="nav navbar-nav navbar-right">
            <li>
              <a href="#schBox" data-toggle="collapse" title="Поиск">
                <span class="glyphicon glyphicon-search" onclick="javascript:navFormToggle(this,&#039;search&#039;)"></span>
              </a>
            </li>
            <li>
              <div class="collapse" id="schBox">
                <form class="navbar-form" role="search" action="" method="post">
                  <div class="input-group">
                    <input class="form-control" type="search" name="schStr" placeholder="Поиск...">
                      <div class="input-group-btn">
                        <button class="btn btn-default" type="submit">
                          <span class="glyphicon glyphicon-search">
                          </span>
                        </button>
                      </div>
                    </input>
                  </div>
                </form>
              </div>
            </li>
            <li>
              <a href="#regBox" data-toggle="modal" title="Регистрация">
                <span class="glyphicon glyphicon-user"></span>
              </a>
            </li>
            <li>
              <?php if(!isset($_SESSION['uid'])) {?>

              <a href="#loginBox" data-toggle="collapse" title="Вход">
                <span class="glyphicon glyphicon-log-in" onclick="navFormToggle(this,&#039;log-in&#039;)"></span>
              </a>
              <?php } else{?>

              <a href="#logoutBox" data-toggle="collapse" title="Выход">
                <span class="glyphicon glyphicon-log-out" onclick="navFormToggle(this,&#039;log-out&#039;)"></span>
              </a>
              <?php }?>

            </li>
            <li>
              <div class="collapse" id="loginBox">
                <form class="navbar-form" id="loginForm">
                  <div class="input-group">
                    <input class="form-control" type="text" name="login" placeholder="Логин (email)" required>
                  </div>
                  <div class="input-group">
                    <input class="form-control" type="password" name="passwd" placeholder="Пароль" required>
                      <div class="input-group-btn">
                        <button class="btn btn-default" type="submit">
                          <span class="glyphicon glyphicon-log-in"></span>
                        </button>
                      </div>
                    </input>
                  </div>
                </form>
              </div>
            </li>
          </ul>
        </div>
      </nav>
    </header>
    
    
    
    <div class="container-fluid">
      
      <form id="regForm">
        <div class="modal fade" id="regBox">
          <div class="modal-dialog">
            <div class="modal-content">
              <div class="modal-header">
                <button class="close" data-dismiss="modal">
                  <span class="glyphicon glyphicon-remove"></span>
                </button>
                <h4 class="modal-title">
                  Регистрация
                </h4>
              </div>
              <div class="modal-body" id="regBody">
                <div class="form-group row">
                  <div class="col-sm-6">
                    <input class="form-control" type="text" placeholder="Имя" title="Имя" name="name" required>
                  </div>
                  <div class="col-sm-6">
                    <input class="form-control" type="text" placeholder="Фамилия" title="Фамилия" name="surname" required>
                  </div>
                </div>
                <div class="form-group row">
                  <div class="col-sm-6">
                    <input class="form-control" id="login" type="text" placeholder="Логин" title="Логин" name="login">
                  </div>
                  <div class="col-sm-6">
                    <input class="form-control" id="email" type="email" placeholder="Адрес эл. почты" title="Эл. почта" name="email" required>
                  </div>
                </div>
                <div class="form-group row">
                  <div class="col-sm-6">
                    <input class="form-control" type="password" placeholder="Пароль (&gt;8 символов)" title="Пароль" name="passwd" pattern=".{8,}" required id="passwd">
                  </div>
                  <div class="col-sm-6">
                    <input class="form-control" type="password" placeholder="Пароль повторно" title="Пароль повторно" name="passwd2" required onblur="checkPasswd(this)">
                  </div>
                </div>
                <div class="form-group row">
                  <div class="col-sm-12">
                    <input class="form-control" type="select" placeholder="ВУЗ" title="ВУЗ" name="univ">
                  </div>
                </div>
              </div>
              <div class="modal-footer" id="regFooter">
                <button class="btn btn-default" type="submit">
                  Отправить
                  <span class="glyphicon glyphicon-cloud-upload"></span>
                </button>
              </div>
            </div>
          </div>
        </div>
      </form>
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
      <div class="container-fluid">
        &copy; 2004 &ndash; <?php echo date("Y"),"&nbsp;&nbsp;",AUTHOR,". Все права защищены." ?>
      </div>
    </footer>
  </body>
</html>