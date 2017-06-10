<!DOCTYPE html>
<html lang="ru">
  <head>
    <title>
      3D!Book
    </title>
    <meta charset="UTF-8">
    <script src="/js/jquery-3.2.1.min.js"></script>
    <script src="/js/bootstrap.min.js"></script>
    <script src="/js/my.js"></script>
    <link rel="stylesheet" type="text/css" href="/css/bootstrap.min.css">
    <link rel="stylesheet" type="text/css" href="/css/my.css">
    
    <link rel="stylesheet" type="text/css" href="/css/vis.css">
    <script src="/js/vis.js"></script>
    <script src="/js/myvis.js"></script>
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
            <li class="navbar-text" id="userName">
              <?php if(isset($_SESSION['uid'])) {?>

              <?php echo $_SESSION['name'],' ',$_SESSION['surname']?>

              <?php }?>

            </li>
            <li>
              <a href="#schBox" data-toggle="collapse" title="Поиск">
                <span id="schButton" class="glyphicon glyphicon-search"></span>
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
                <span class="glyphicon glyphicon-log-in"></span>
              </a>
              <?php } else{?>

              <a href="#logoutBox" data-toggle="collapse" title="Выход">
                <span class="glyphicon glyphicon-log-out"></span>
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
      
      <div class="modal fade" id="modalDialog">
        <div class="modal-dialog">
          <div class="modal-content">
            <div class="modal-header">
              <button class="close" data-dismiss="modal">
                <span class="glyphicon glyphicon-remove"></span>
              </button>
              <h4 class="modal-title" id="modalTitle">
                <b>
                  <?php echo (isset($modalTitle)) ? $modalTitle : 'Информация';?>

                </b>
              </h4>
            </div>
            <form id="modalForm">
              <div class="modal-body" id="modalBody">
                <?php echo (isset($modalBody)) ? $modalBody : 'Нет информации' ;?>

              </div>
              <div class="modal-footer" id="modalFooter">
                <button class="btn btn-default" data-dismiss="modal">
                  Закрыть
                  <span class="glyphicon glyphicon-remove"></span>
                </button>
                <?php if(!isset($type)){$type='info';};
                switch($type){
                case 'send': ?>
                <button class="btn btn-primary" type="submit">
                  Отправить
                  <span class="glyphicon glyphicon-cloud-upload"></span>
                </button>
                <?php break;
                case 'info':
                break;} ?>
              </div>
            </form>
          </div>
        </div>
      </div>
    </header>
    
    
    <div class="container-fluid">
      
      <div class="modal fade" id="regBox">
        <div class="modal-dialog">
          <div class="modal-content">
            <div class="modal-header">
              <button class="close" data-dismiss="modal">
                <span class="glyphicon glyphicon-remove"></span>
              </button>
              <h4 class="modal-title">
                <b>
                  Регистрация
                </b>
              </h4>
            </div>
            <form id="regForm">
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
            </form>
          </div>
        </div>
      </div>
      <div class="col-md-3">
        <div class="panel panel-default">
          <div class="panel-heading">
            <b>
              Добро пожаловать на AG+ !
            </b>
          </div>
          <div class="panel-body">
             Здесь изучают общую и линейную алгебру и аналитическую геометрию
            в пределах стандартных университетских курсов для математических специальностей.
            Для представления материала используется предложенная нами технология
            <b>
              3D!Book
            </b>
          </div>
        </div>
        <button class="btn" type="button" data-toggle="modal" data-target="#modalDialog">
          Тест модалки
        </button>
      </div>
      <div class="col-md-6">
        <div class="container-fluid" id="myGraph" style="height:70vh"></div>
      </div>
      <div class="col-md-3">
        <div class="panel panel-default">
          <div class="panel-heading">
            <b>
              Технология 3D!Book
            </b>
          </div>
          <div class="panel-body">
            <ul>
              <li>
                представление теоретического материала в виде логического дерева определений, теорем, задач и коментариев
              </li>
              <li>
                возможность выборки элементов логического дерева для получения книжного представления
              </li>
            </ul>
          </div>
        </div>
      </div>
    </div>
    
    <div class="modal fade" id="modalDialog">
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-header">
            <button class="close" data-dismiss="modal">
              <span class="glyphicon glyphicon-remove"></span>
            </button>
            <h4 class="modal-title" id="modalTitle">
              <b>
                <?php echo (isset($modalTitle)) ? $modalTitle : 'Информация';?>

              </b>
            </h4>
          </div>
          <form id="modalForm">
            <div class="modal-body" id="modalBody">
              <?php echo (isset($modalBody)) ? $modalBody : 'Нет информации' ;?>

            </div>
            <div class="modal-footer" id="modalFooter">
              <button class="btn btn-default" data-dismiss="modal">
                Закрыть
                <span class="glyphicon glyphicon-remove"></span>
              </button>
              <?php if(!isset($type)){$type='info';};
              switch($type){
              case 'send': ?>
              <button class="btn btn-primary" type="submit">
                Отправить
                <span class="glyphicon glyphicon-cloud-upload"></span>
              </button>
              <?php break;
              case 'info':
              break;} ?>
            </div>
          </form>
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