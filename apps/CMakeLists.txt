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
cmake_minimum_required(VERSION 3.14...3.19)

find_package(QT
  NAMES Qt6 Qt5
  COMPONENTS
  Widgets
  REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}
  COMPONENTS
  Widgets
  REQUIRED)

if(ANDROID)
  add_library(QElectroTech_Element_Updater SHARED
    main.cpp
    ${TS_FILES}
  )
else()
  add_executable(QElectroTech_Element_Updater
    main.cpp
    ${TS_FILES}
  )
endif()

target_compile_features(QElectroTech_Element_Updater PRIVATE cxx_std_17)

target_link_libraries(QElectroTech_Element_Updater
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  gui)
