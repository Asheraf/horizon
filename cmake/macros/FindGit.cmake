###################################################
#       _   _            _                        #
#      | | | |          (_)                       #
#      | |_| | ___  _ __ _ _______  _ __          #
#      |  _  |/ _ \| '__| |_  / _ \| '_  \        #
#      | | | | (_) | |  | |/ / (_) | | | |        #
#      \_| |_/\___/|_|  |_/___\___/|_| |_|        #
###################################################
# This file is part of Horizon (c).
# Copyright (c) 2018 Horizon Dev Team.
#
# Base Author - Sxyz (sagunxp@gmail.com)
#
# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this library.  If not, see <http://www.gnu.org/licenses/>.
###################################################

include(${CMAKE_SOURCE_DIR}/cmake/macros/EnsureVersion.cmake)

set(_REQUIRED_GIT_VERSION "1.7")

find_program(GIT_EXECUTABLE
  NAMES
    git git.cmd git-cmd.exe
  HINTS
    ENV PATH
	"C:\\Program Files\\Git"
  DOC "Full path to git commandline client"
)
MARK_AS_ADVANCED(GIT_EXECUTABLE)

if(NOT GIT_EXECUTABLE)
  message(FATAL_ERROR "
    Git was NOT FOUND on your system - did you forget to install a recent version, or setting the path to it?
    Observe that for revision hash/date to work you need at least version ${_REQUIRED_GIT_VERSION}")
else()
  message(STATUS "Found git binary : ${GIT_EXECUTABLE}")

  if (WIN32)
	set(GIT_EXECUTABLE "git")
  endif()

  execute_process(
    COMMAND "${GIT_EXECUTABLE}" --version
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE _GIT_VERSION
    ERROR_QUIET
  )

  # make sure we're using minimum the required version of git, so the "dirty-testing" will work properly
  ensure_version( "${_REQUIRED_GIT_VERSION}" "${_GIT_VERSION}" _GIT_VERSION_OK)

  # throw an error if we don't have a recent enough version of git...
  if(NOT _GIT_VERSION_OK)
    message(STATUS "Git version too old : ${_GIT_VERSION}")
    message(FATAL_ERROR "
      Git was found but is OUTDATED - did you forget to install a recent version, or setting the path to it?
      Observe that for revision hash/date to work you need at least version ${_REQUIRED_GIT_VERSION}")
  endif()
endif()
