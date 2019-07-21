-- phpMyAdmin SQL Dump
-- version 4.5.2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: 2017-06-11 00:06:04
-- 服务器版本： 5.6.28
-- PHP Version: 5.5.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `shop`
--

-- --------------------------------------------------------

--
-- 表的结构 `shop_admin`
--

CREATE TABLE `shop_admin` (
  `admin_id` int(3) NOT NULL,
  `admin_name` varchar(10) NOT NULL,
  `admin_psw` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `shop_admin`
--

INSERT INTO `shop_admin` (`admin_id`, `admin_name`, `admin_psw`) VALUES
(1, 'admin', '123456');

-- --------------------------------------------------------

--
-- 表的结构 `shop_member`
--

CREATE TABLE `shop_member` (
  `mem_id` int(11) NOT NULL,
  `mem_name` varchar(15) NOT NULL,
  `mem_email` varchar(100) NOT NULL,
  `mem_cname` varchar(10) NOT NULL,
  `mem_phone` varchar(15) NOT NULL,
  `mem_address` varchar(100) NOT NULL,
  `mem_pwd` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `shop_member`
--

INSERT INTO `shop_member` (`mem_id`, `mem_name`, `mem_email`, `mem_cname`, `mem_phone`, `mem_address`, `mem_pwd`) VALUES
(1, 'zhangsan', 'zs@qq.com', '张三', '13711111111', '湖南长沙', '111'),
(2, 'lisi', 'ls@qq.com', '李四', '12411111111', '北京', '222');

-- --------------------------------------------------------

--
-- 表的结构 `shop_prod`
--

CREATE TABLE `shop_prod` (
  `type_id` int(4) NOT NULL,
  `prod_id` int(11) NOT NULL,
  `prod_name` varchar(60) NOT NULL,
  `prod_img` varchar(100) DEFAULT '/ec/img',
  `prod_price` int(10) NOT NULL DEFAULT '0',
  `prod_discount` int(2) DEFAULT NULL,
  `prod_content` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `shop_prod`
--

INSERT INTO `shop_prod` (`type_id`, `prod_id`, `prod_name`, `prod_img`, `prod_price`, `prod_discount`, `prod_content`) VALUES
(1, 1, '奥尔洛夫', 'images/1.jpg', 1200, 1000, '本品晶莹透亮'),
(2, 2, '蓝色至尊', 'images/2.jpg', 32615, 30000, '凸显高贵'),
(2, 3, '贝多芬的忧伤', 'images/3.jpg', 11500, 11250, '手感柔和'),
(2, 4, '仙希', 'images/4.jpg', 32700, 26900, '彰显尊贵高雅'),
(1, 5, '泰勒伯顿', 'images/5.jpg', 18900, 16500, '优雅'),
(3, 6, '蓝色希望', 'images/6.jpg', 32799, 29999, '可爱');

-- --------------------------------------------------------

--
-- 表的结构 `shop_prodtype`
--

CREATE TABLE `shop_prodtype` (
  `type_id` int(3) NOT NULL,
  `type_name` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `shop_prodtype`
--

INSERT INTO `shop_prodtype` (`type_id`, `type_name`) VALUES
(1, '手链'),
(2, '项链'),
(3, '戒指');

-- --------------------------------------------------------

--
-- 表的结构 `shop_track`
--

CREATE TABLE `shop_track` (
  `id` int(3) NOT NULL,
  `memid` varchar(30) NOT NULL,
  `prodid` varchar(15) NOT NULL,
  `prodnum` int(3) NOT NULL,
  `prodprice` int(6) NOT NULL,
  `prodtotal` int(6) NOT NULL,
  `date_add` date NOT NULL,
  `prodname` varchar(60) NOT NULL,
  `prodcontent` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `shop_admin`
--
ALTER TABLE `shop_admin`
  ADD PRIMARY KEY (`admin_id`);

--
-- Indexes for table `shop_member`
--
ALTER TABLE `shop_member`
  ADD PRIMARY KEY (`mem_id`);

--
-- Indexes for table `shop_prod`
--
ALTER TABLE `shop_prod`
  ADD PRIMARY KEY (`prod_id`);

--
-- Indexes for table `shop_prodtype`
--
ALTER TABLE `shop_prodtype`
  ADD PRIMARY KEY (`type_id`);

--
-- Indexes for table `shop_track`
--
ALTER TABLE `shop_track`
  ADD PRIMARY KEY (`id`);

--
-- 在导出的表使用AUTO_INCREMENT
--

--
-- 使用表AUTO_INCREMENT `shop_admin`
--
ALTER TABLE `shop_admin`
  MODIFY `admin_id` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- 使用表AUTO_INCREMENT `shop_member`
--
ALTER TABLE `shop_member`
  MODIFY `mem_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- 使用表AUTO_INCREMENT `shop_prod`
--
ALTER TABLE `shop_prod`
  MODIFY `prod_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
--
-- 使用表AUTO_INCREMENT `shop_prodtype`
--
ALTER TABLE `shop_prodtype`
  MODIFY `type_id` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- 使用表AUTO_INCREMENT `shop_track`
--
ALTER TABLE `shop_track`
  MODIFY `id` int(3) NOT NULL AUTO_INCREMENT;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
