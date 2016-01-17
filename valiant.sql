-- phpMyAdmin SQL Dump
-- version 3.5.8.2
-- http://www.phpmyadmin.net
--
-- Хост: 217.106.106.176:3306
-- Время создания: Сен 28 2014 г., 13:47
-- Версия сервера: 5.5.37-0+wheezy1
-- Версия PHP: 5.3.28

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `EVE_H3961`
--

-- --------------------------------------------------------

--
-- Структура таблицы `accounts`
--

CREATE TABLE IF NOT EXISTS `accounts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(24) COLLATE cp1251_bin NOT NULL,
  `pass` varchar(50) COLLATE cp1251_bin NOT NULL,
  `email` varchar(50) COLLATE cp1251_bin NOT NULL,
  `perm` int(10) NOT NULL DEFAULT '0',
  `baned` int(10) NOT NULL DEFAULT '0',
  `muted` int(10) NOT NULL DEFAULT '0',
  `bans` int(10) NOT NULL DEFAULT '0',
  `warns` int(10) NOT NULL DEFAULT '0',
  `kicks` int(10) NOT NULL DEFAULT '0',
  `mutes` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=cp1251 COLLATE=cp1251_bin AUTO_INCREMENT=4 ;

--
-- Дамп данных таблицы `accounts`
--

INSERT INTO `accounts` (`id`, `name`, `pass`, `email`, `perm`, `baned`, `muted`, `bans`, `warns`, `kicks`, `mutes`) VALUES
(3, 'ch3rkasov', 'EE242948E855E80B05AE474530566D98', 'ch3rkasov@gmail.com', 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `factions`
--

CREATE TABLE IF NOT EXISTS `factions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ownerid` int(10) NOT NULL,
  `name` varchar(30) COLLATE cp1251_bin NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=cp1251 COLLATE=cp1251_bin AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Структура таблицы `houses`
--

CREATE TABLE IF NOT EXISTS `houses` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ownerid` int(10) NOT NULL,
  `interiorid` int(10) NOT NULL,
  `price` int(10) NOT NULL DEFAULT '10000',
  `sell` int(10) NOT NULL DEFAULT '0',
  `name` varchar(30) COLLATE cp1251_bin NOT NULL,
  `desc` varchar(256) COLLATE cp1251_bin NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `virtualworld` int(10) NOT NULL,
  `interior` int(10) NOT NULL,
  `lock` int(10) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=cp1251 COLLATE=cp1251_bin AUTO_INCREMENT=2 ;

-- --------------------------------------------------------

--
-- Структура таблицы `items`
--

CREATE TABLE IF NOT EXISTS `items` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `itemid` int(11) NOT NULL DEFAULT '0',
  `ownerid` int(11) NOT NULL DEFAULT '0',
  `amount` int(11) NOT NULL DEFAULT '1',
  `comment` varchar(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Структура таблицы `permissions`
--

CREATE TABLE IF NOT EXISTS `permissions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `permid` int(11) NOT NULL DEFAULT '0',
  `ownerid` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `permissions`
--

INSERT INTO `permissions` (`id`, `permid`, `ownerid`) VALUES
(1, 0, 1),
(2, 25, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `players`
--

CREATE TABLE IF NOT EXISTS `players` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ownerid` int(10) NOT NULL,
  `name` varchar(24) COLLATE cp1251_bin NOT NULL,
  `skin` int(10) NOT NULL DEFAULT '0',
  `faction` int(10) NOT NULL DEFAULT '0',
  `homeid` int(10) NOT NULL DEFAULT '0',
  `exitx` float NOT NULL DEFAULT '-1976.02',
  `exity` float NOT NULL DEFAULT '137.888',
  `exitz` float NOT NULL DEFAULT '27.6875',
  `exitvw` int(10) NOT NULL DEFAULT '0',
  `exitint` int(10) NOT NULL DEFAULT '0',
  `lvl` int(11) NOT NULL DEFAULT '1',
  `exp` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=cp1251 COLLATE=cp1251_bin AUTO_INCREMENT=4 ;

--
-- Дамп данных таблицы `players`
--

INSERT INTO `players` (`id`, `ownerid`, `name`, `skin`, `faction`, `homeid`, `exitx`, `exity`, `exitz`, `exitvw`, `exitint`, `lvl`, `exp`) VALUES
(3, 3, 'Vincent_Orre', 0, 0, 0, -2029.77, 144.049, 28.8359, 0, 0, 1, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `vehicles`
--

CREATE TABLE IF NOT EXISTS `vehicles` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `modelid` int(10) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `a` float NOT NULL,
  `color1` int(10) NOT NULL DEFAULT '0',
  `color2` int(10) NOT NULL DEFAULT '0',
  `respawn` int(10) NOT NULL DEFAULT '300',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=cp1251 COLLATE=cp1251_bin AUTO_INCREMENT=1 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
