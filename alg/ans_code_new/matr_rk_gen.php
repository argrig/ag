$form['rk'] = array ('#type'=>'textfield',
    '#title'=>t('Значение ранга матрицы'),'#weight'=>10) ;
$form['cols'] = array('#type'=>'textfield',
    '#title'=>t('Номера базисных столбцов'),'#weight'=>20) ;
$form['step'] = array('#type'=>'textarea','#cols'=>33,'#rows'=>7,
    '#title'=>t('Ступенчатый вид матрицы'),'#weight'=>30) ;
$form['submit'] = array('#type'=>'submit',
    '#value'=>t('Готово'),'#weight'=>40) ;

