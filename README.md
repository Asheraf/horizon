

# The Horizon Project
Horizon is a free software project (authored by [@sagunkho](https://gitlab.com/sagunkho) aka [@Smokexyz](https://gitlab.com/Smokexyz)) revolving around the
creation of a robust Massively Multiplayer Online Role-Playing Game (MMORPG)
server package. Written in C++ and Lua, the program is very versatile and provides NPCs, playable jobs and easily modifiable gameplay via its Lua extension. The project aims to provide a high quality and performant codebase that accurately emulates mechanics of the official servers.

Some static database files and client packet information were converted from [HerculesWS](https://github.com/HerculesWS/Hercules) into a suitable format for our project.

Table of Contents
---------
1. What is Horizon?
2. Prerequisites
3. Installation
4. Troubleshooting

Prerequisites
-------------
Before installing Horizon, you will need to install certain tools and applications.

#### Supported Operating Systems
- Linux
- Unix / MacOS
- Windows (Installable but not entirely supported)

#### Pre-requisites
  - git
  - g++ or clang (version 4.5 or newer, recommended 5.0 or newer)
  - [CMake 3.7+](https://cmake.org/)
  - [MySQL 8.0.14+](https://dev.mysql.com/downloads/mysql/)
  - [MySQL C++ Connector](https://dev.mysql.com/downloads/connector/cpp/8.0.html)
  - [Boost v1.60+](https://www.boost.org/)
  - [Readline](https://tiswww.case.edu/php/chet/readline/rltop.html)
  - [CryptoPP](https://www.cryptopp.com/)
  - [LuaJit 5.1](http://luajit.org)
  - [SPDLog](https://github.com/gabime/spdlog)
  - [Sol2](https://github.com/ThePhD/sol2)

#### Optional, useful tools
  - MySQL GUI clients
    - [MySQL Workbench](http://www.mysql.com/downloads/workbench/) (cross-platform)
    - [HeidiSQL](http://www.heidisql.com/) (Windows)
    - [Sequel Pro](http://www.sequelpro.com/) (Mac OS X)
  - GUI Git clients
    - [Atlassian SourceTree](https://www.sourcetreeapp.com/) (Windows, Mac OS X)
    - [TortoiseGit](https://tortoisegit.org/) (Windows)

Installation
------------
#### Unix
1. Before installing the pre-requisites, you need to install the `mysql apt config` by typing in the following commands (For MacOS, please install MySQL and C++ Connector 8.0.14+) from their website) -
    - `yum/apt-get -y update`
    - `yum/apt-get -y install wget lsb-release gnupg unzip`
    - `wget https://dev.mysql.com/get/mysql-apt-config_0.8.12-1_all.deb`
    - `dpkg -i mysql-apt-config_0.8.12-1_all.deb`
    - `yum/apt-get -y update`
3. Now install the prerequisites through your distribution's package manager
    -  `yum/apt-get install -y cmake mysql-server libmysqlcppconn-dev libboost-all-dev libreadline-dev libcrypto++-dev libluajit-5.1-dev zlib1g-dev clang`
    - For MacOS:
    - `brew install cmake boost readline cryptopp luajit zlib`
  4. Next, install Sol2 after cloning the repository `git clone https://github.com/ThePhD/sol2 ~/sol2`
       - `cd ~/sol2; mkdir build; cd build; cmake ..; make install;`
  5. Now clone Horizon  `git clone https://gitlab.com/horizon_/horizoncpp.git ~/Horizon`
  6. Configure the MySQL server and start it.
  7. Connect to the MySQL server as root:
    - Create a database (hercules): `CREATE DATABASE horizon;`
    - Create a user (hercules): `CREATE USER 'ragnarok'@'localhost' IDENTIFIED BY 'ragnarok';`.
    - Give permissions (GRANT SELECT,INSERT,UPDATE,DELETE) to the user: `GRANT SELECT,INSERT,UPDATE,DELETE ON horizon.* TO 'ragnarok'@'localhost';`
  8. Connect to the MySQL server as the new user:
    - Import the .sql files in sql-files/ into the new database.
  9. Enter the Horizon directory and try building it -
    - Enter the root directory: `cd ~/Horizon`
    - Make the build folder: `mkdir build; cd build;`
    - Configure the build: `cmake ../ -DCMAKE_INSTALL_PREFIX=<path/to/installation/folder>`
    - If configuration succeeds: `make install`
  10. Your installations should be located in the `path/to/installation/folder` entered above.
  11. Enter the installation directory and create a log directory by typing `mkdir log`
  12. Copy the `npc`, `db`, `scripts` and `config` files into the installation directory and rename the `config/*.dist.conf` files to `config/*.conf`
  13. Start the auth, char and zone servers from the directory and you should be good to go!
