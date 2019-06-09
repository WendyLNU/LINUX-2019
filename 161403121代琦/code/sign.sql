-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: 2016-04-14 16:09:04
-- 服务器版本： 5.6.17
-- PHP Version: 5.5.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `sign`
--

-- --------------------------------------------------------

--
-- 表的结构 `course`
--

CREATE TABLE IF NOT EXISTS `course` (
  `C_id` varchar(22) COLLATE utf8_unicode_ci NOT NULL,
  `C_name` varchar(22) COLLATE utf8_unicode_ci NOT NULL,
  `C_start_time` time NOT NULL,
  `C_over_time` time NOT NULL,
  `C_room` varchar(22) COLLATE utf8_unicode_ci NOT NULL,
  `C_ip` varchar(22) COLLATE utf8_unicode_ci NOT NULL,
  `C_department` varchar(22) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- 转存表中的数据 `course`
--

INSERT INTO `course` (`C_id`, `C_name`, `C_start_time`, `C_over_time`, `C_room`, `C_ip`, `C_department`) VALUES
('1001', 'æ“ä½œç³»ç»Ÿ', '08:00:00', '09:00:00', '315', '192.168.1.1', 'ä¿¡æ¯å­¦é™¢'),
('1002', 'æ•°æ®åº“', '09:00:00', '10:00:00', '329', '192.168.2.1', 'æ•°å­¦é™¢'),
('1003', 'è®¡ç®—æœºåŸºç¡€', '10:00:00', '11:00:00', '201', '192.168.3.1', 'ä¿¡æ¯å­¦é™¢'),
('1004', 'æ•°æ®ç»“æž„', '00:00:13', '00:00:14', '315', '192.168.1.1', 'æ•°å­¦é™¢'),
('10009', 'å¤§å­¦ç‰©ç†', '16:00:00', '19:00:00', '321', '192.168.0.0', 'ä¿¡æ¯å­¦é™¢');

-- --------------------------------------------------------

--
-- 表的结构 `sign`
--

CREATE TABLE IF NOT EXISTS `sign` (
  `Q_C_id` varchar(22) COLLATE utf8_unicode_ci NOT NULL,
  `Q_S_id` varchar(22) COLLATE utf8_unicode_ci NOT NULL,
  `Q_T_id` varchar(22) COLLATE utf8_unicode_ci NOT NULL,
  `Q_sign1` tinyint(1) NOT NULL,
  `Q_sign2` tinyint(1) NOT NULL,
  `Q_sign3` tinyint(1) NOT NULL,
  `Q_sign4` tinyint(1) NOT NULL,
  `Q_count` tinyint(1) NOT NULL,
  `Q_a` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- 转存表中的数据 `sign`
--

INSERT INTO `sign` (`Q_C_id`, `Q_S_id`, `Q_T_id`, `Q_sign1`, `Q_sign2`, `Q_sign3`, `Q_sign4`, `Q_count`, `Q_a`) VALUES
('1001', '131401102', '', 0, 0, 0, 0, 1, 1),
('1003', '131401102', '', 0, 0, 0, 0, 1, 1),
('1001', '131401103', '', 0, 0, 0, 0, 1, 1),
('1003', '131401103', '', 0, 0, 0, 0, 1, 1),
('1001', '131401104', '', 0, 0, 0, 0, 1, 1),
('1003', '131401104', '', 0, 0, 0, 0, 1, 1),
('1001', '131401105', '', 0, 0, 0, 0, 1, 1),
('1003', '131401105', '', 0, 0, 0, 0, 1, 1),
('10006', '131401102', '', 0, 0, 0, 0, 1, 0),
('10006', '131401103', '', 0, 0, 0, 0, 1, 0),
('10006', '131401104', '', 0, 0, 0, 0, 1, 0),
('10006', '131401105', '', 0, 0, 0, 0, 1, 0),
('10009', '131401102', '', 0, 0, 0, 0, 1, 1),
('10009', '131401103', '', 0, 0, 0, 0, 1, 1),
('10009', '131401104', '', 1, 0, 0, 0, 1, 1),
('10009', '131401105', '', 0, 0, 0, 0, 1, 1);

-- --------------------------------------------------------

--
-- 表的结构 `student`
--

CREATE TABLE IF NOT EXISTS `student` (
  `S_id` varchar(22) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `S_name` varchar(22) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `S_depart` varchar(22) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `S_sex` varchar(22) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `S_passwd` varchar(22) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `path` varchar(22) COLLATE utf8_unicode_520_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_520_ci;

--
-- 转存表中的数据 `student`
--

INSERT INTO `student` (`S_id`, `S_name`, `S_depart`, `S_sex`, `S_passwd`, `path`) VALUES
('131401102', 'å¼ å››', 'ä¿¡æ¯å­¦é™¢', 'å¥³', '123456', ''),
('131401103', 'å¼ äº”', 'ä¿¡æ¯å­¦é™¢', 'ç”·', '123456', ''),
('131401104', 'æŽçŠ', 'ä¿¡æ¯å­¦é™¢', 'å¥³', '123456', './download/131401104/'),
('131401105', 'æ±ªå³°', 'ä¿¡æ¯å­¦é™¢', 'ç”·', '123456', ''),
('131401106', 'ç« å­æ€¡', 'æ•°å­¦é™¢', 'å¥³', '123456', ''),
('131401107', 'è°­æµ©å¼º', 'æ•°å­¦é™¢', 'ç”·', '123456', ''),
('131401108', 'å¼ ä¼Ÿ', 'æ•°å­¦é™¢', 'å¥³', '123456', ''),
('131401109', 'çŽ‹ä¼Ÿ', 'æ•°å­¦é™¢', 'ç”·', '123456', ''),
('131401110', 'æŽç™½', 'æ•°å­¦é™¢', 'å¥³', '123456', '');

-- --------------------------------------------------------

--
-- 表的结构 `student_message`
--

CREATE TABLE IF NOT EXISTS `student_message` (
  `stu_number` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `C_name` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `tea_num` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `Content` varchar(500) COLLATE utf8_unicode_ci NOT NULL,
  `datetime` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- 转存表中的数据 `student_message`
--

INSERT INTO `student_message` (`stu_number`, `C_name`, `tea_num`, `Content`, `datetime`) VALUES
('131401104', 'è®¡ç®—æœºåŸºç¡€', '10001', 'å®žéªŒè®¤çœŸï¼ŒæŠ¥å‘Šä¼˜ç§€ï¼', '2016-04-14 02:00:22');

-- --------------------------------------------------------

--
-- 表的结构 `teacher`
--

CREATE TABLE IF NOT EXISTS `teacher` (
  `T_id` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `T_name` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `T_depart` varchar(22) COLLATE utf8_unicode_ci NOT NULL,
  `T_passwd` varchar(22) COLLATE utf8_unicode_ci NOT NULL,
  `T_email` varchar(22) COLLATE utf8_unicode_ci NOT NULL,
  `T_profession` varchar(22) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- 转存表中的数据 `teacher`
--

INSERT INTO `teacher` (`T_id`, `T_name`, `T_depart`, `T_passwd`, `T_email`, `T_profession`) VALUES
('10001', 'admin', 'ä¿¡æ¯å­¦é™¢', 'admin', 'admin@admin.com', 'æ•™æŽˆ');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
