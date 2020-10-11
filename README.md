

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
  - [Boost v1.60+](https://www.boost.org/)
  - [Readline](https://tiswww.case.edu/php/chet/readline/rltop.html)
  - [LuaJit 5.1](http://luajit.org)
  - [Sol2](https://github.com/ThePhD/sol2)
  - [Argon2] (https://github.com/P-H-C/phc-winner-argon2)
  - [SQLPP11] (https://github.com/rbock/sqlpp11) + [SQLPP11-MYSQL] (https://github.com/rbock/sqlpp11-connector-mysql)

#### Optional, useful tools
  - MySQL GUI clients
    - [MySQL Workbench](http://www.mysql.com/downloads/workbench/) (cross-platform)
    - [HeidiSQL](http://www.heidisql.com/) (Windows)
    - [Sequel Pro](http://www.sequelpro.com/) (Mac OS X)
  - GUI Git clients
    - [Atlassian SourceTree](https://www.sourcetreeapp.com/) (Windows, Mac OS X)
    - [TortoiseGit](https://tortoisegit.org/) (Windows)
