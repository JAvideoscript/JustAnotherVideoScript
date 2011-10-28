-- MySQL dump 10.11
--
-- Host: localhost    Database: JAVS
-- ------------------------------------------------------
-- Server version	5.0.77

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `ban`
--

DROP TABLE IF EXISTS `ban`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ban` (
  `ip` varchar(15) NOT NULL default '',
  PRIMARY KEY  (`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `ban`
--

LOCK TABLES `ban` WRITE;
/*!40000 ALTER TABLE `ban` DISABLE KEYS */;
/*!40000 ALTER TABLE `ban` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `blocked`
--

DROP TABLE IF EXISTS `blocked`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `blocked` (
  `blocker_id` int(11) NOT NULL default '0',
  `blockee_id` int(11) NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `blocked`
--

LOCK TABLES `blocked` WRITE;
/*!40000 ALTER TABLE `blocked` DISABLE KEYS */;
/*!40000 ALTER TABLE `blocked` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `category`
--

DROP TABLE IF EXISTS `category`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `category` (
  `id` int(255) NOT NULL auto_increment,
  `name` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=1170 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `category`
--

LOCK TABLES `category` WRITE;
/*!40000 ALTER TABLE `category` DISABLE KEYS */;
INSERT INTO `category` VALUES (1,'Main Category');
/*!40000 ALTER TABLE `category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `email_text`
--

DROP TABLE IF EXISTS `email_text`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `email_text` (
  `ident` varchar(255) NOT NULL default '',
  `phrase` text NOT NULL,
  PRIMARY KEY  (`ident`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `email_text`
--

LOCK TABLES `email_text` WRITE;
/*!40000 ALTER TABLE `email_text` DISABLE KEYS */;
INSERT INTO `email_text` VALUES ('email_forgot','Hello,\r\nYou have requested a new username and password for [SITENAME].\r\n\r\nUsername: [USERNAME]\r\nPassword: [PASSWORD]\r\n\r\nThanks\r\n\r\nAdmin'),('email_newmedia','Hello, \r\nNew media has been posted by [POSTER]. To view it click the following link.\r\n\r\n[MEDIALINK]\r\n\r\nYou have received this message because you are subscribed to the above user.\r\n\r\nThanks\r\n\r\n[SITENAME]'),('email_activate','Hello,\r\nsomeone, probably you, has registered this e-mail address with us at [SITEURL].\r\n\r\nTo complete the registration process please activate your account by clicking on the following link:\r\n\r\n[ACTLINK]\r\n\r\nThank you for registering\r\n\r\n[SITENAME]'),('email_upload','Hello, \nNew media has been posted by [POSTER]. To view it click the following link: [MEDIALINK]\nLink to file: [FILELINK]\nManage Videos: [MANAGELINK]'),('admin_acc_act','Hello, [USERNAME];\r\n\r\nYour account has been activated by an administrator, on [SITENAME].');
/*!40000 ALTER TABLE `email_text` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `favorite`
--

DROP TABLE IF EXISTS `favorite`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `favorite` (
  `userid` int(11) NOT NULL default '0',
  `vidid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`userid`,`vidid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `favorite`
--

--
-- Table structure for table `friend`
--

DROP TABLE IF EXISTS `friend`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `friend` (
  `userid` int(11) NOT NULL default '0',
  `friendid` int(11) NOT NULL default '0',
  `friend_approved` tinyint(1) NOT NULL default '0',
  `friend_removed` tinyint(11) NOT NULL default '0',
  PRIMARY KEY  (`userid`,`friendid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `friend`
--

--
-- Table structure for table `media`
--

DROP TABLE IF EXISTS `media`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `media` (
  `id` int(255) NOT NULL auto_increment,
  `title` varchar(255) NOT NULL default '',
  `category` varchar(255) NOT NULL default '',
  `description` text NOT NULL,
  `tags` varchar(255) NOT NULL default '',
  `fileid` varchar(255) NOT NULL default '',
  `poster` varchar(255) NOT NULL default '0',
  `added` varchar(255) NOT NULL default '',
  `status` varchar(255) NOT NULL default 'false',
  `mobile` int(1) NOT NULL default '0',
  `hd` int(1) NOT NULL default '0',
  `embed` longtext NOT NULL,
  `featured` tinyint(1) NOT NULL default '0',
  `dayviews` int(11) NOT NULL default '0',
  `weekviews` int(11) NOT NULL default '0',
  `monthviews` int(11) NOT NULL default '0',
  `allviews` int(11) NOT NULL default '0',
  `checkday` varchar(64) NOT NULL default '',
  `checkweek` int(11) NOT NULL default '0',
  `checkmonth` int(11) NOT NULL default '0',
  `mediatype` varchar(10) NOT NULL default '',
  `flagged` tinyint(1) NOT NULL default '0',
  `lastviewed` bigint(20) NOT NULL,
  `vidad` text,
  `duration` varchar(255) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  FULLTEXT KEY `title` (`title`),
  FULLTEXT KEY `tags` (`tags`),
  FULLTEXT KEY `discription` (`description`)
) ENGINE=MyISAM AUTO_INCREMENT=572 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `media_comment`
--

DROP TABLE IF EXISTS `media_comment`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `media_comment` (
  `id` int(255) NOT NULL auto_increment,
  `vid_id` int(25) NOT NULL default '0',
  `date` varchar(255) NOT NULL default '',
  `text` text NOT NULL,
  `leftbyname` varchar(40) NOT NULL default '',
  `regdposter` tinyint(1) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=75 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;


--
-- Table structure for table `member`
--

DROP TABLE IF EXISTS `member`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `member` (
  `id` int(11) NOT NULL auto_increment,
  `username` varchar(20) NOT NULL default '',
  `password` varchar(32) NOT NULL default '',
  `email` varchar(255) NOT NULL default '',
  `cookie` varchar(32) NOT NULL default '',
  `session` varchar(32) NOT NULL default '',
  `ip` varchar(15) NOT NULL default '',
  `activationkey` varchar(32) NOT NULL default '',
  `history` text NOT NULL,
  `avatar` varchar(255) NOT NULL default '',
  `profile_privacy` smallint(6) NOT NULL default '0',
  `gender` tinyint(1) NOT NULL default '0',
  `age` int(11) default NULL,
  `aboutme` varchar(255) default '',
  `location` varchar(64) NOT NULL default '',
  `created` varchar(255) NOT NULL default '',
  `lastlogin` varchar(255) NOT NULL default '0',
  `profileviews` int(11) NOT NULL default '0',
  `agreed` tinyint(1) NOT NULL default '0',
  `viewerhistory` text NOT NULL,
  `optoutofviewerlist` tinyint(1) NOT NULL default '0',
  `banned` tinyint(1) NOT NULL default '0',
  `lookingfor` int(1) default '0',
  `favmovie` varchar(255) default '',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=MyISAM AUTO_INCREMENT=81 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `message`
--

DROP TABLE IF EXISTS `message`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `message` (
  `messageid` int(11) NOT NULL auto_increment,
  `fromid` int(11) NOT NULL default '0',
  `toid` int(11) NOT NULL default '0',
  `body` text NOT NULL,
  `sentdate` varchar(255) NOT NULL default '0',
  `msgread` tinyint(4) NOT NULL default '0',
  `auto` int(11) NOT NULL default '0',
  PRIMARY KEY  (`messageid`)
) ENGINE=MyISAM AUTO_INCREMENT=182 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `rating`
--

DROP TABLE IF EXISTS `rating`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `rating` (
  `id` varchar(11) NOT NULL default '',
  `total_votes` int(11) NOT NULL default '0',
  `total_value` int(11) NOT NULL default '0',
  `which_id` int(11) NOT NULL default '0',
  `used_ips` longtext,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `setting`
--

DROP TABLE IF EXISTS `setting`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `setting` (
  `setting` varchar(255) NOT NULL default '',
  `value` text NOT NULL,
  PRIMARY KEY  (`setting`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `setting`
--

LOCK TABLES `setting` WRITE;
/*!40000 ALTER TABLE `setting` DISABLE KEYS */;
INSERT INTO `setting` VALUES ('sitename','Demo JAVS'),('activation','1'),('membervideodelete','0'),('downmobileGuest','0'),('downnormalmembers','0'),('downmobilemember','0'),('restrictpc','0'),('audiobitrate','128'),('accountpageon','1'),('thumb_w1','160'),('hdvideo','1'),('thumb_h1','120'),('mobilevideo','1'),('sitetemplate','brown'),('avatar_w','160'),('avatar_h','120'),('contact_email','info@YOURDOMAIN.LTD'),('mediamaxsize','209715200'),('meta_toprated_key','Top Rated, Media'),('videobitrate','1024'),('framerate','12'),('encodesize','640x480'),('meta_toprated_desc','Top Rated Media'),('url_clean','1'),('comment_length','300'),('default_from','admin'),('default_thumbtime','20'),('mp_toprated','12'),('mp_inbox','8'),('downmembers','1'),('sitetitle','JAVS Demo site'),('mp_allvideos','12'),('sitefolder','/'),('meta_mostviewed_header','Most Viewed Media'),('relateduserpage','6'),('ffmpegpath','/usr/bin/ffmpeg'),('curlpath','/usr/bin/curl'),('flvtool2path','/usr/bin/flvtool2'),('meta_home_header','Home'),('player','jwplayer'),('audiofrequency','44100'),('downGuest','1'),('mp_outbox','8'),('maxresolution_w','1280'),('maxresolution_h','720'),('mp_mostviewed','12'),('mp_uploadedvideos','8'),('showdesc','1'),('mp4box','/usr/local/bin/MP4Box'),('meta_toprated_header','Top Rated Media'),('mp_friend','5'),('mp_fav','5'),('mp_sub','5'),('mp_media','5'),('captchaformembers','0'),('mp_sentrequests','8'),('mp_profileviews','8'),('mp_blockedmembers','8'),('mp_members','12'),('mp_category','12'),('meta_home_desc','Home Media'),('embed_videos','1'),('downhdguest','1'),('titledisplaylength','25'),('mp_favoritevideos','8'),('meta_home_key','Home, Media'),('mp_receivedrequests','8'),('mp_friends','8'),('videoaspect','4:3'),('mp_viewinghistory','8'),('removeorifile','1'),('autoacceptvideo','0'),('selplay','toprated'),('usegzip','0'),('passcron','cronpass'),('downhdmember','1'),('maxsizememberavatar','400'),('mp_mediasearch','12'),('directencode','1'),('skinjw','beelden.zip'),('smedia','485'),('meta_mostviewed_key','Most Viewed, media'),('meta_mostviewed_desc','Most viewed media'),('meta_allvideos_header','Javs demo video list'),('meta_allvideos_key','Javs demo, video list, all movies'),('meta_allvideos_desc','A list of videos to demonstrated javs demo'),('meta_members_header','Members'),('meta_members_key','members, video'),('meta_members_desc','Members list'),('meta_profile_header','Profile'),('meta_profile_key','Profile, members'),('meta_profile_desc','User Profile'),('meta_category_header','Category'),('meta_category_key','Category'),('meta_category_desc','Category'),('meta_search_header','Search'),('meta_search_key','Search, find'),('meta_search_desc','Search'),('mobile_encodesize_height','320'),('mobile_encodesize_width','480'),('showdmca','1'),('showsocial','1'),('show2257','1'),('showallvideos','1'),('showtoprated','1'),('showmostviewed','1'),('showcategorie','1'),('showembed','1'),('enablelogin','1'),('showmembers','1'),('showupload','1'),('showfrontpage','home'),('meta_catlist_header','categories List'),('meta_catlist_key','Category, list, Categories'),('meta_catlist_desc','A list of Categories, here you can pick the category you like very easy by clicking a sample picture.');
/*!40000 ALTER TABLE `setting` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sitead`
--

DROP TABLE IF EXISTS `sitead`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `sitead` (
  `adname` varchar(20) NOT NULL default '',
  `adtext` text NOT NULL,
  PRIMARY KEY  (`adname`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `sitead`
--

LOCK TABLES `sitead` WRITE;
/*!40000 ALTER TABLE `sitead` DISABLE KEYS */;
INSERT INTO `sitead` VALUES ('ad6',''),('ad5',''),('ad4',''),('ad3',''),('ad2',''),('ad1',''),('ad14',''),('ad13',''),('ad12',''),('ad11',''),('ad10',''),('ad9',''),('ad8',''),('ad7',''),('ad15',''),('ad16','');
/*!40000 ALTER TABLE `sitead` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `subscription`
--

DROP TABLE IF EXISTS `subscription`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `subscription` (
  `userid` int(11) NOT NULL default '0',
  `subscribedtoid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`userid`,`subscribedtoid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping routines for database 'JAVS'
--

/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2011-10-09 22:40:12
