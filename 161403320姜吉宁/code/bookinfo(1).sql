-- phpMyAdmin SQL Dump
-- version 4.5.4.1deb2ubuntu2.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: 2019-06-04 14:49:15
-- 服务器版本： 5.7.11-0ubuntu6
-- PHP Version: 7.0.33-0ubuntu0.16.04.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `bookinfo`
--

-- --------------------------------------------------------

--
-- 表的结构 `admin`
--

CREATE TABLE `admin` (
  `id` int(11) NOT NULL,
  `username` varchar(225) COLLATE utf8_bin DEFAULT NULL,
  `password` varchar(225) COLLATE utf8_bin DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- 转存表中的数据 `admin`
--

INSERT INTO `admin` (`id`, `username`, `password`) VALUES
(1, 'admin', 'admin');

-- --------------------------------------------------------

--
-- 表的结构 `lend`
--

CREATE TABLE `lend` (
  `id` int(6) NOT NULL,
  `book_id` int(6) NOT NULL,
  `book_title` varchar(100) COLLATE utf8_bin NOT NULL,
  `lend_time` date NOT NULL,
  `user_id` int(3) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- 转存表中的数据 `lend`
--

INSERT INTO `lend` (`id`, `book_id`, `book_title`, `lend_time`, `user_id`) VALUES
(48, 37, '', '2013-10-23', 2),
(49, 37, '', '2013-10-23', 3),
(50, 26, '', '2013-10-23', 3),
(51, 2, '', '2013-10-23', 3),
(58, 39, '', '2013-12-05', 4),
(59, 41, '', '2013-12-05', 4),
(60, 37, '', '2013-12-05', 4),
(66, 41, '', '2014-01-03', 2);

-- --------------------------------------------------------

--
-- 表的结构 `user`
--

CREATE TABLE `user` (
  `id` int(11) NOT NULL,
  `name` varchar(225) COLLATE utf8_bin DEFAULT NULL,
  `password` varchar(225) COLLATE utf8_bin DEFAULT NULL,
  `email` varchar(225) COLLATE utf8_bin DEFAULT NULL,
  `tel` varchar(225) COLLATE utf8_bin DEFAULT NULL,
  `address` varchar(225) COLLATE utf8_bin DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- 转存表中的数据 `user`
--

INSERT INTO `user` (`id`, `name`, `password`, `email`, `tel`, `address`) VALUES
(1, 'smiling', 'smiling', 'smiling@qq.com', '13011253665', '北京市丰台区万柳桥南'),
(2, 'xiaoma', '0f0fadae4575dc905b5a4e19e711d622', 'xiaoma@qq.com', '12364997997', '12364997997'),
(3, 'xiaoxiao', '0f0fadae4575dc905b5a4e19e711d622', 'xiaoxiao@qq.com', 'xiaoxiao', 'xiaoxiao'),
(4, 'nihao', '194ce5d0b89c47ff6b30bfb491f9dc26', 'nihao@qq.com', '13256321556', '33166'),
(5, 'aa', 'aa', 'aa@qq.com', 'aa', 'aa');

-- --------------------------------------------------------

--
-- 表的结构 `yx_books`
--

CREATE TABLE `yx_books` (
  `id` int(6) NOT NULL,
  `name` varchar(20) CHARACTER SET gbk NOT NULL,
  `price` decimal(4,2) NOT NULL,
  `uploadtime` datetime NOT NULL,
  `type` varchar(10) CHARACTER SET gbk NOT NULL,
  `total` int(11) DEFAULT NULL,
  `leave_number` int(11) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- 转存表中的数据 `yx_books`
--

INSERT INTO `yx_books` (`id`, `name`, `price`, `uploadtime`, `type`, `total`, `leave_number`) VALUES
(1, 'PHP100', '50.00', '2009-05-09 19:39:28', 'PHP', 5, 5),
(2, 'asp200', '50.36', '2009-05-09 19:39:46', 'ASP编程', 1, 0),
(3, 'ASP.net中文教程', '32.45', '2009-05-09 19:39:54', '网络营销', 4, 4),
(26, '数据库系统', '23.46', '0000-00-00 00:00:00', '网页美工', 5, 4),
(36, 'DB', '23.17', '2009-05-09 12:37:40', '软件开发', 8, 8),
(37, 'asp', '22.00', '2013-10-22 10:02:34', 'ASP编程', 7, 1),
(39, 'asp新手学习', '88.00', '2013-12-05 10:28:46', 'asp编程', 10, 7),
(40, 'php新手学习', '33.00', '2013-12-05 10:46:43', 'php编程', 8, 0),
(41, '经典php编程', '66.00', '2013-12-05 10:48:01', 'php编程', 22, 16),
(44, '1987,我们的红楼梦', '98.00', '2019-06-04 02:32:09', '文学', 1, 1),
(43, '红楼梦', '88.00', '2019-06-04 01:47:25', '文学', 2, 2),
(45, '郭论', '49.80', '2019-06-04 02:32:49', '随笔', 1, 1),
(46, '我所理解的生活', '29.00', '2019-06-04 02:34:28', '杂文', 1, 1),
(47, '牡丹亭', '29.00', '2019-06-04 02:35:04', '文学', 1, 1),
(48, '西厢记', '26.80', '2019-06-04 02:35:55', '文学', 1, 1);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `lend`
--
ALTER TABLE `lend`
  ADD PRIMARY KEY (`id`,`user_id`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `yx_books`
--
ALTER TABLE `yx_books`
  ADD PRIMARY KEY (`id`);

--
-- 在导出的表使用AUTO_INCREMENT
--

--
-- 使用表AUTO_INCREMENT `admin`
--
ALTER TABLE `admin`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- 使用表AUTO_INCREMENT `lend`
--
ALTER TABLE `lend`
  MODIFY `id` int(6) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=68;
--
-- 使用表AUTO_INCREMENT `user`
--
ALTER TABLE `user`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
--
-- 使用表AUTO_INCREMENT `yx_books`
--
ALTER TABLE `yx_books`
  MODIFY `id` int(6) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=49;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
