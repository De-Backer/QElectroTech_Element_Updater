# Copyright 2006 The QElectroTech Team
# This file is part of QElectroTech.
#
# QElectroTech is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# QElectroTech is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with QElectroTech. If not, see <http://www.gnu.org/licenses/>.

# Note that headers are optional, and do not affect add_library,
# but they will not show up in IDEs unless they are listed in add_library.
cmake_minimum_required(VERSION 3.14...3.19)

find_package(
  QT
  NAMES
  Qt6
  Qt5
  COMPONENTS
  Core
  Xml
  REQUIRED
  )
find_package(
  Qt${QT_VERSION_MAJOR}
  COMPONENTS
  Core
  Xml
  REQUIRED
  )
set(HEADER_LIST
  "${QElectroTech_Element_Updater_SOURCE_DIR}/include/element/loadelement.h"
  )

# Make an automatic library - will be static or dynamic based on user setting
add_library(element
  loadelement.cpp
  ${HEADER_LIST}
  )

# We need this directory, and users of our library will need it too
target_include_directories(element
  PUBLIC
  ../../include/element
  )

# This depends on (header only) boost
target_link_libraries(element
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Xml
  )

# All users of this library will need at least C++11
target_compile_features(element
  PUBLIC
  cxx_std_11
  )

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include/element"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
  )
