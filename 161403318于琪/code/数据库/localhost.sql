-- phpMyAdmin SQL Dump
-- version 4.0.4
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2019 年 06 月 03 日 00:22
-- 服务器版本: 5.6.12-log
-- PHP 版本: 5.4.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 数据库: `bbs`
--
CREATE DATABASE IF NOT EXISTS `bbs` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `bbs`;

-- --------------------------------------------------------

--
-- 表的结构 `content`
--

CREATE TABLE IF NOT EXISTS `content` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `module_id` int(10) unsigned NOT NULL,
  `title` varchar(255) NOT NULL,
  `content` text NOT NULL,
  `time` datetime NOT NULL,
  `member_id` int(10) unsigned NOT NULL,
  `times` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=11 ;

--
-- 转存表中的数据 `content`
--

INSERT INTO `content` (`id`, `module_id`, `title`, `content`, `time`, `member_id`, `times`) VALUES
(1, 6, 'ÑÝÔ±±¾É«', 'ÑÝ¼¼ºÃ', '2019-05-21 08:52:41', 12, 0),
(2, 8, 'wdw', 'ÎÒ°®°®°®°®°¡', '2019-05-21 20:30:53', 12, 0),
(3, 8, 'Ó¦¸Ã', 'ÎÒÊÇÒ»¸ö', '2019-05-21 20:32:25', 12, 0),
(4, 9, 'ÃÀ', 'ÃÀÃÀÃÀÃÀÃÀ', '2019-05-30 13:42:24', 12, 0),
(5, 8, 'Ù¡Àöæ«', 'Îèµ¸¶à×Ë¶à²Ê', '2019-05-30 14:41:33', 12, 0),
(6, 9, '½ðÓ¥½±', 'Å®Éñ', '2019-05-30 14:45:58', 12, 0),
(7, 12, '½ðÓ¥½±', 'Å®Éñ', '2019-05-30 15:29:49', 12, 0),
(8, 12, '÷ÈÁ¦', 'ÐÂ½®ÈË', '2019-05-30 15:30:08', 12, 0),
(9, 13, 'Ñ¾Ñ¾', '¶à×Ë¶à²Ê', '2019-05-30 15:30:39', 12, 0),
(10, 16, 'ÐÂÉú´úÑÝÔ±', '¾Ü¾øÐ¡ÏÊÈâ', '2019-05-30 15:31:16', 12, 0);

-- --------------------------------------------------------

--
-- 表的结构 `father_module`
--

CREATE TABLE IF NOT EXISTS `father_module` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `module_name` varchar(66) NOT NULL,
  `sort` int(11) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COMMENT='父板块信息表' AUTO_INCREMENT=18 ;

--
-- 转存表中的数据 `father_module`
--

INSERT INTO `father_module` (`id`, `module_name`, `sort`) VALUES
(17, 'Mainland Female stars', 0),
(15, 'Mainland male stars', 0);

-- --------------------------------------------------------

--
-- 表的结构 `member`
--

CREATE TABLE IF NOT EXISTS `member` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL,
  `pw` varchar(32) NOT NULL,
  `photo` varchar(255) NOT NULL,
  `register_time` datetime NOT NULL,
  `last_time` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=13 ;

--
-- 转存表中的数据 `member`
--

INSERT INTO `member` (`id`, `name`, `pw`, `photo`, `register_time`, `last_time`) VALUES
(12, 'yu', 'e10adc3949ba59abbe56e057f20f883e', '', '2019-05-08 20:28:02', '0000-00-00 00:00:00');

-- --------------------------------------------------------

--
-- 表的结构 `son_module`
--

CREATE TABLE IF NOT EXISTS `son_module` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `father_module_id` int(10) unsigned NOT NULL,
  `module_name` varchar(66) NOT NULL,
  `info` varchar(255) NOT NULL,
  `member_id` int(10) unsigned NOT NULL DEFAULT '0',
  `sort` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=17 ;

--
-- 转存表中的数据 `son_module`
--

INSERT INTO `son_module` (`id`, `father_module_id`, `module_name`, `info`, `member_id`, `sort`) VALUES
(16, 15, '³ÂÐÇÐñ', '', 0, 0),
(15, 15, '°×Óî', '¿É°®', 0, 0),
(12, 17, 'µÏÀöÈÈ°Í', 'ÃÀ', 0, 0),
(14, 15, 'ÖìÒ»Áú', 'Ë§ ', 0, 0),
(13, 17, 'Ù¡Àöæ«', 'Æ¯ÁÁ', 0, 0);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
