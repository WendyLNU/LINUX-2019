/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50091
Source Host           : localhost:3306
Source Database       : bookinfo

Target Server Type    : MYSQL
Target Server Version : 50091
File Encoding         : 65001

Date: 2014-01-03 15:45:14
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `admin`
-- ----------------------------
DROP TABLE IF EXISTS `admin`;
CREATE TABLE `admin` (
  `id` int(11) NOT NULL auto_increment,
  `username` varchar(225) collate utf8_bin default NULL,
  `password` varchar(225) collate utf8_bin default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of admin
-- ----------------------------
INSERT INTO admin VALUES ('1', 'admin', 'admin');

-- ----------------------------
-- Table structure for `lend`
-- ----------------------------
DROP TABLE IF EXISTS `lend`;
CREATE TABLE `lend` (
  `id` int(6) NOT NULL auto_increment,
  `book_id` int(6) NOT NULL,
  `book_title` varchar(100) collate utf8_bin NOT NULL,
  `lend_time` date NOT NULL,
  `user_id` int(3) NOT NULL,
  PRIMARY KEY  (`id`,`user_id`)
) ENGINE=InnoDB AUTO_INCREMENT=67 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of lend
-- ----------------------------
INSERT INTO lend VALUES ('47', '37', '', '2013-10-23', '1');
INSERT INTO lend VALUES ('48', '37', '', '2013-10-23', '2');
INSERT INTO lend VALUES ('49', '37', '', '2013-10-23', '3');
INSERT INTO lend VALUES ('50', '26', '', '2013-10-23', '3');
INSERT INTO lend VALUES ('51', '2', '', '2013-10-23', '3');
INSERT INTO lend VALUES ('58', '39', '', '2013-12-05', '4');
INSERT INTO lend VALUES ('59', '41', '', '2013-12-05', '4');
INSERT INTO lend VALUES ('60', '37', '', '2013-12-05', '4');
INSERT INTO lend VALUES ('66', '41', '', '2014-01-03', '2');

-- ----------------------------
-- Table structure for `user`
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(225) collate utf8_bin default NULL,
  `password` varchar(225) collate utf8_bin default NULL,
  `email` varchar(225) collate utf8_bin default NULL,
  `tel` varchar(225) collate utf8_bin default NULL,
  `address` varchar(225) collate utf8_bin default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO user VALUES ('1', 'smiling', '35204591ae1edf5074ab088ec7d67934', 'smiling@qq.com', '13011253665', '北京市丰台区万柳桥南');
INSERT INTO user VALUES ('2', 'xiaoma', '0f0fadae4575dc905b5a4e19e711d622', 'xiaoma@qq.com', '12364997997', '12364997997');
INSERT INTO user VALUES ('3', 'xiaoxiao', '0f0fadae4575dc905b5a4e19e711d622', 'xiaoxiao@qq.com', 'xiaoxiao', 'xiaoxiao');
INSERT INTO user VALUES ('4', 'nihao', '194ce5d0b89c47ff6b30bfb491f9dc26', 'nihao@qq.com', '13256321556', '33166');

-- ----------------------------
-- Table structure for `yx_books`
-- ----------------------------
DROP TABLE IF EXISTS `yx_books`;
CREATE TABLE `yx_books` (
  `id` int(6) NOT NULL auto_increment,
  `name` varchar(20) character set gbk NOT NULL,
  `price` decimal(4,2) NOT NULL,
  `uploadtime` datetime NOT NULL,
  `type` varchar(10) character set gbk NOT NULL,
  `total` int(11) default NULL,
  `leave_number` int(11) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=42 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of yx_books
-- ----------------------------
INSERT INTO yx_books VALUES ('1', 'PHP100', '50.00', '2009-05-09 19:39:28', 'PHP编程', '5', '5');
INSERT INTO yx_books VALUES ('2', 'asp200', '50.36', '2009-05-09 19:39:46', 'ASP编程', '1', '0');
INSERT INTO yx_books VALUES ('3', 'ASP.net中文教程', '32.45', '2009-05-09 19:39:54', '网络营销', '4', '4');
INSERT INTO yx_books VALUES ('26', '数据库系统', '23.46', '0000-00-00 00:00:00', '网页美工', '5', '4');
INSERT INTO yx_books VALUES ('36', 'DB', '23.17', '2009-05-09 12:37:40', '软件开发', '8', '8');
INSERT INTO yx_books VALUES ('37', 'asp', '22.00', '2013-10-22 10:02:34', 'ASP编程', '7', '3');
INSERT INTO yx_books VALUES ('39', 'asp新手学习', '88.00', '2013-12-05 10:28:46', 'asp编程', '10', '7');
INSERT INTO yx_books VALUES ('40', 'php新手学习', '33.00', '2013-12-05 10:46:43', 'php编程', '8', '0');
INSERT INTO yx_books VALUES ('41', '经典php编程', '66.00', '2013-12-05 10:48:01', 'php编程', '22', '18');
