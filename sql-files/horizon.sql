#           _   _            _
#          | | | |          (_)
#          | |_| | ___  _ __ _ _______  _ __
#          |  _  |/ _ \| '__| |_  / _ \| '_ \
#          | | | | (_) | |  | |/ / (_) | | | |
#          \_| |_/\___/|_|  |_/___\___/|_| |_|
#
# This file is part of Horizon (c).
# Copyright (c) 2018 Horizon Dev Team.
#
# Base Author - Sagun Khosla. (sagunxp@gmail.com)
#
# Under a proprietary license this file is not for use
# or viewing without permission.
#########################################################

# Login Table
CREATE TABLE IF NOT EXISTS `game_account` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(23) NOT NULL DEFAULT '',
  `password` varchar(64) NOT NULL DEFAULT '',
  `gender` enum('M','F','S') NOT NULL DEFAULT 'M',
  `email` varchar(39) NOT NULL DEFAULT '',
  `group_id` tinyint(3) NOT NULL DEFAULT 0,
  `state` int(11) unsigned NOT NULL DEFAULT 0,
  `unban_time` int(11) unsigned NOT NULL DEFAULT 0,
  `expiration_time` int(11) unsigned NOT NULL DEFAULT 0,
  `login_count` mediumint(9) unsigned NOT NULL DEFAULT 0,
  `last_login` datetime DEFAULT NULL,
  `last_ip` varchar(100) NOT NULL DEFAULT '',
  `birth_date` date DEFAULT NULL,
  `character_slots` tinyint(3) unsigned NOT NULL DEFAULT 0,
  `pincode` varchar(4) NOT NULL DEFAULT '',
  `pincode_expiry` int(11) unsigned NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  KEY `name` (`username`)
) ENGINE = MyISAM AUTO_INCREMENT = 2000000 DEFAULT CHARSET=utf8;
