-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Хост: 127.0.0.1
-- Время создания: Фев 04 2016 г., 02:01
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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=25 ;

--
-- Дамп данных таблицы `players`
--

INSERT INTO `players` (`id`, `name`, `pass`, `email`, `banned`, `muted`, `kicks`, `bans`, `mutes`, `warns`, `sex`, `exp`, `lvl`, `money`, `donate`, `groupid`) VALUES
(1, 'Stanislav_Cherkasov', 'FFA5BCA9496243922131D1C65DA51F0C', 'ch3rkasov@gmail.com', 0, 0, 10, 0, 0, 0, 0, 0, 1, 0, 1488, 1),
(2, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(3, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(4, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(5, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(6, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(7, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(8, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(9, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(10, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(11, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(12, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(13, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(14, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(15, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(16, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(17, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(18, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(19, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(20, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(21, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(22, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(23, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1),
(24, 'Test_Test', 'FFA5BCA9496243922131D1C65DA51F0C', 'test@test.test', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `props`
--

CREATE TABLE IF NOT EXISTS `props` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `interiorid` int(11) NOT NULL,
  `vw` int(11) NOT NULL DEFAULT '0',
  `interior` int(11) NOT NULL DEFAULT '-1',
  `ownerid` int(11) NOT NULL,
  `ownertype` int(11) NOT NULL,
  `startprice` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=9 ;

--
-- Дамп данных таблицы `props`
--

INSERT INTO `props` (`id`, `x`, `y`, `z`, `interiorid`, `vw`, `interior`, `ownerid`, `ownertype`, `startprice`, `price`) VALUES
(1, 1743.72, -1864.46, 13.5738, 1, 0, 0, 0, 2, 0, 0),
(2, 1833.78, -1842.61, 13.5781, 36, 0, 0, 0, 0, 10000, 10000),
(3, 1854, -1914.26, 15.2568, 1, 0, 0, 0, 0, 0, 0),
(4, 1872.18, -1911.79, 15.2568, 2, 0, 0, 0, 0, 10000, 10000),
(5, 1891.93, -1914.39, 15.2568, 1, 0, 0, 0, 0, 0, 0),
(6, 1913.46, -1911.9, 15.2568, 2, 0, 0, 0, 0, 10000, 10000),
(7, 1928.61, -1915.9, 15.2568, 1, 0, 0, 0, 0, 0, 0),
(8, 1938.53, -1911.34, 15.2568, 2, 0, 0, 0, 0, 10000, 10000);

-- --------------------------------------------------------

--
-- Структура таблицы `rights`
--

CREATE TABLE IF NOT EXISTS `rights` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ownerid` int(11) NOT NULL,
  `rightid` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=22 ;

--
-- Дамп данных таблицы `rights`
--

INSERT INTO `rights` (`id`, `ownerid`, `rightid`) VALUES
(1, 1, 0),
(5, 1, 26),
(7, 1, 2),
(8, 1, 3),
(9, 1, 4),
(10, 1, 5),
(11, 1, 6),
(12, 1, 7),
(13, 1, 8),
(14, 1, 9),
(16, 1, 10),
(20, 1, 12),
(21, 1, 13);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
