-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Хост: 127.0.0.1
-- Время создания: Фев 01 2016 г., 02:08
-- Версия сервера: 5.5.25
-- Версия PHP: 5.3.13

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `epicrp`
--

-- --------------------------------------------------------

--
-- Структура таблицы `groups`
--

CREATE TABLE IF NOT EXISTS `groups` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(33) NOT NULL,
  `leaderid` int(11) NOT NULL,
  `lvl` int(11) NOT NULL DEFAULT '1',
  `exp` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=43 ;

--
-- Дамп данных таблицы `groups`
--

INSERT INTO `groups` (`id`, `name`, `leaderid`, `lvl`, `exp`) VALUES
(1, 'Администрация', 1, 1, 0),
(2, 'SuchBigDildosWow', 0, 1, 0),
(3, 'Reserv', 0, 1, 0),
(4, 'Reserv', 0, 1, 0),
(5, 'Reserv', 0, 1, 0),
(6, 'Reserv', 0, 1, 0),
(7, 'Reserv', 0, 1, 0),
(8, 'Reserv', 0, 1, 0),
(9, 'Reserv', 0, 1, 0),
(10, 'Reserv', 0, 1, 0),
(11, 'Reserv', 0, 1, 0),
(12, 'Reserv', 0, 1, 0),
(13, 'Reserv', 0, 1, 0),
(14, 'Reserv', 0, 1, 0),
(15, 'Reserv', 0, 1, 0),
(16, 'Reserv', 0, 1, 0),
(17, 'Reserv', 0, 1, 0),
(18, 'Reserv', 0, 1, 0),
(19, 'Reserv', 0, 1, 0),
(20, 'Reserv', 0, 1, 0),
(21, 'Reserv', 0, 1, 0),
(22, 'Reserv', 0, 1, 0),
(23, 'Reserv', 0, 1, 0),
(24, 'Reserv', 0, 1, 0),
(25, 'Reserv', 0, 1, 0),
(26, 'Reserv', 0, 1, 0),
(27, 'Reserv', 0, 1, 0),
(28, 'Reserv', 0, 1, 0),
(29, 'Reserv', 0, 1, 0),
(30, 'Reserv', 0, 1, 0),
(31, 'Reserv', 0, 1, 0),
(32, 'Reserv', 0, 1, 0),
(33, 'Reserv', 0, 1, 0),
(34, 'Reserv', 0, 1, 0),
(35, 'Reserv', 0, 1, 0),
(36, 'Reserv', 0, 1, 0),
(37, 'Reserv', 0, 1, 0),
(38, 'Reserv', 0, 1, 0),
(39, 'Reserv', 0, 1, 0),
(40, 'Reserv', 0, 1, 0),
(41, 'Reserv', 0, 1, 0),
(42, 'Reserv', 0, 1, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `players`
--

CREATE TABLE IF NOT EXISTS `players` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(24) NOT NULL,
  `pass` varchar(33) NOT NULL,
  `email` varchar(64) NOT NULL,
  `banned` int(11) NOT NULL,
  `muted` int(11) NOT NULL,
  `kicks` int(11) NOT NULL,
  `bans` int(11) NOT NULL,
  `mutes` int(11) NOT NULL,
  `warns` int(11) NOT NULL,
  `sex` int(11) NOT NULL,
  `exp` int(11) NOT NULL,
  `lvl` int(11) NOT NULL DEFAULT '1',
  `money` float NOT NULL,
  `donate` float NOT NULL,
  `groupid` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Дамп данных таблицы `players`
--

INSERT INTO `players` (`id`, `name`, `pass`, `email`, `banned`, `muted`, `kicks`, `bans`, `mutes`, `warns`, `sex`, `exp`, `lvl`, `money`, `donate`, `groupid`) VALUES
(1, 'Stanislav_Cherkasov', 'FFA5BCA9496243922131D1C65DA51F0C', 'ch3rkasov@gmail.com', 0, 0, 10, 0, 0, 0, 0, 0, 1, 0, 1488, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `rights`
--

CREATE TABLE IF NOT EXISTS `rights` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ownerid` int(11) NOT NULL,
  `rightid` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=18 ;

--
-- Дамп данных таблицы `rights`
--

INSERT INTO `rights` (`id`, `ownerid`, `rightid`) VALUES
(1, 1, 0),
(5, 1, 26),
(6, 1, 1),
(7, 1, 2),
(8, 1, 3),
(9, 1, 4),
(10, 1, 5),
(11, 1, 6),
(12, 1, 7),
(13, 1, 8),
(14, 1, 9),
(16, 1, 10);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
