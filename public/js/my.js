$(document).ready(function() {
  user=[] ;
  urlParts = window.location.href.split('/') ;
  https = 'https://'+urlParts[2]+'/' ;
  $("#loginForm").submit(function(e) {
    e.preventDefault();
    $.ajax({
      type: "post",
      url:  https + "login",
      cache:false,
      data: $("#loginForm").serialize(),
      success: function(data) {
        console.log(data) ; 
      },
      error: ajax_JSON_errors 
    })
  }) ;

  $("#regForm").submit(function(e) {
    e.preventDefault();
    $.ajax({
      type:     "post",
      url:      https + "register",
      cache:    false,
      context:  this,
      data:     $("#regForm").serialize(),
      success:  function(data) {
        if(data['error']) {
          fld = document.getElementById(data['error']) ;
          fld.setCustomValidity("Этот "+data['error']+" уже занят. Измените.") ;
          this.reportValidity() ;
          setTimeout(function(){fld.setCustomValidity('')},3000) ;
        }
        else if(data['status'] == 'ok') {
         $('#regBody').html("<div class='alert alert-success'><b>Регистрация прошла успешно!<b></div>") ;
         $("#regFooter").html("<button class='btn btn-default' data-dismiss='modal'>Закрыть</button>") ;
         console.log(data,data['status']) ;
        }
        else {console.log(data,data['status'])} ;
      },
      error:    ajax_JSON_errors 
    })
  }) ;
}) ;

function checkPasswd (input) {
  if (input.value != document.getElementById('passwd').value) {
      input.setCustomValidity('Пароли должны совпадать...');
  } 
  else { input.setCustomValidity('');}
} 

function ajax_JSON_errors (jqXHR,exception) {
  var msg = '';
  if (jqXHR.status === 0) {
      msg = 'Нет связи.\n Проверьте сеть.';
  } else if (jqXHR.status == 404) {
      msg = 'Страничка не найдена. [404]';
  } else if (jqXHR.status == 500) {
      msg = 'Внутренняя ошибка сервера [500].';
  } else if (exception === 'parsererror') {
      msg = 'Не могу прочитать запрошенный JSON.';
  } else if (exception === 'timeout') {
      msg = 'Не дождались ответа...';
  } else if (exception === 'abort') {
      msg = 'Прервался запрос AJAX.';
  } else {
      msg = 'Неизвестная ошибка.\n' + jqXHR.responseText;
  }
  console.log(jqXHR.responseText) ;
  alert(msg) ;

}

function navFormToggle(btn, glyph) {
  setTimeout(function() {
    toggleglyph = 'chevron-right' ;
    btn.className = (btn.className.search(toggleglyph) == -1) ?
      'glyphicon glyphicon-' + toggleglyph : 'glyphicon glyphicon-' + glyph ;}, 200) 
} ;


