CREATE DATABASE IF NOT EXISTS 3Dbook DEFAULT CHARACTER SET = 'utf8' ;

USE 3Dbook ;

CREATE TABLE IF NOT EXISTS univers (
  id      INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  name    VARCHAR(255) DEFAULT 'Данные не предоставлены',
  abbr    VARCHAR(32) DEFAULT '',
  verif   BOOLEAN DEFAULT false,
  PRIMARY KEY (id)
) ENGINE=INNODB ;

CREATE TABLE IF NOT EXISTS users (
  id     INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  name    VARCHAR(32) NOT NULL,
  surname VARCHAR(32) NOT NULL,
  login   VARCHAR(32) UNIQUE KEY NOT NULL,
  passwd  CHAR(72) NOT NULL,
  email   VARCHAR(254) UNIQUE KEY NOT NULL,
  verif   BOOLEAN DEFAULT false,
  created DATETIME DEFAULT CURRENT_TIMESTAMP,
  lastlog DATETIME,
  unvid   INTEGER UNSIGNED NOT NULL DEFAULT 1,
  roleid  INTEGER UNSIGNED NOT NULL DEFAULT 1,
  PRIMARY KEY(id),
  FOREIGN KEY(unvid) REFERENCES univers(id) ON UPDATE CASCADE
) ENGINE=INNODB ;

CREATE TABLE IF NOT EXISTS chunkTypes  (
  id      INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  name    VARCHAR(16),
  titles  VARCHAR(255),
  brief   VARCHAR(255),
  example VARCHAR(255),
  PRIMARY KEY(id)
) ENGINE=INNODB ;

REPLACE into chunkTypes VALUES
  (1,'term','Понятие,Термин', 
    'Название математического объекта. Словосочетание в названии обычно содержит существительное в качестве главного слова',
    '"функция", "линейное пространство", "вполне упорядоченное множество"'), 
  (2,'rel','Отношение', 
    'Название связи между объектами. Словосочетание в названии обычно содержит глагол в качестве главного слова', 
    '"принадлежит","содержится","совпадают почти всюду"'), 
  (3,'def','Определение','Определение математического понятия', 
    'Группа &ndash это множество с одной ассоциативной, обратимой, бинарной операцией'), 
  (4,'axiom','Аксиома,Постулат','Математическое утверждение, принимаемое без доказательства', 
    'Существует множество, не содержащее элементов (пустое множество)'), 
  (5,'theor','Теорема,Утверждение,Предложение,Лемма','Математическое утверждение, требующее доказательства', 
    'Сумма размерностей ядра и образа линейного оператора равна размерности пространства'), 
  (6,'text','Комментарий','Текст, поясняющий то или иное понятие, определение или теорему','Произвольный текст ...') 
;

CREATE TABLE IF NOT EXISTS chunks (
  id      INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  name    VARCHAR(16),
  title   VARCHAR(255),
  short   VARCHAR(32),
  text    TEXT,
  formal  TEXT,
  created DATETIME DEFAULT CURRENT_TIMESTAMP,
  updated DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  uid     INTEGER UNSIGNED NOT NULL DEFAULT 0,
  tid     INTEGER UNSIGNED NOT NULL,
  INDEX(title), PRIMARY KEY(id), FULLTEXT(text),
  FOREIGN KEY(tid)    REFERENCES chunkTypes(id) ON UPDATE CASCADE,
  FOREIGN KEY(uid) REFERENCES users(id)   ON UPDATE CASCADE
) ENGINE=INNODB ;

CREATE TABLE IF NOT EXISTS rels (
  ch1     INTEGER UNSIGNED NOT NULL,
  ch2     INTEGER UNSIGNED NOT NULL,
  rtid    INTEGER UNSIGNED NOT NULL,
  UNIQUE  INDEX (ch1,ch2)
) ENGINE=INNODB ;

CREATE TABLE IF NOT EXISTS relTypes (
  id      INTEGER UNSIGNED NOT NULL,
  name    VARCHAR(16),
  title   VARCHAR(32),
  brief   VARCHAR(255),
  PRIMARY KEY(id)
) ENGINE=INNODB ;

REPLACE INTO relTypes VALUES
  (1,'parent','Предок',
    'Фрагмент, от которого напрямую логически зависит текущий фрагмент. Обратное понятие "Потомок"'),
  (2,'child','Потомок',
    'Фрагмент, напрямую логически зависящий от текущего фрагмента. Обратное понятие "Предок"'),
  (4,'friend','Аналог','Фрагмент, аналогичный текущему (характер аналогии произволен &ndash; фантазия автора)'),
  (8,'subchunk','Подфрагмент',
    'Фрагмент, содержащийся в данном. Например, понятие в опеределении. Обратное понятие "Надфрагмент"'),
  (16,'supchunk','Надфрагмент','Фрагмент, содержащий данный. Например, теорема содержит предикат. Обратное понятие "Подфрагмент"')
;


CREATE TABLE IF NOT EXISTS roles (
  id      INTEGER UNSIGNED NOT NULL,
  name    VARCHAR(16),
  title   VARCHAR(32),
  brief   VARCHAR(255),
  PRIMARY KEY (id)
) ENGINE=INNODB ;

REPLACE INTO roles VALUES
  (1,'user','Пользователь',
    'Роль предназначена для студентов, только начавших изучать предмет. Не предполагает редактирование материала'),
  (2,'moderator','Модератор',
    'Роль предназначена для продвинутых студентов, магистрантов и аспирантов. Допускает редактирование материала'),
  (4,'tutor','Преподаватель', 'Роль допускает редактирование материала и создание групп студентов'),
  (8,'admin','Администратор','Администратор системы. Полный доступ к системе.')
;

CREATE TABLE IF NOT EXISTS perms (
  id      INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  rid     INTEGER UNSIGNED NOT NULL DEFAULT 0,
  uid     INTEGER UNSIGNED NOT NULL DEFAULT 0,
  aid     INTEGER UNSIGNED NOT NULL DEFAULT 0,
  onoff   BOOLEAN,
  PRIMARY KEY(id)
) ENGINE=INNODB ;

CREATE TABLE IF NOT EXISTS actions (
  id      INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  name    VARCHAR(16),
  title   VARCHAR(32),
  brief   VARCHAR(255),
  PRIMARY KEY(id)
) ENGINE=INNODB ;

CREATE TABLE IF NOT EXISTS test (
  id      INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  name    VARCHAR(16),
  num     INTEGER,
  PRIMARY KEY(id)
) ENGINE=INNODB ;

# OPTIMIZE TABLE perms, actions, roles, users, chunks, chunkTypes, rels, relTypes
