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

message("..___________________________________________________________________")

project(G_unitmocktests LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

SET(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(".. PROJECT_NAME              :" ${PROJECT_NAME})
message(".. PROJECT_SOURCE_DIR        :" ${PROJECT_SOURCE_DIR})

if(NOT DEFINED QT_VERSION_MAJOR)
  find_package(
    QT
   NAMES
    Qt6
    Qt5
   COMPONENTS
    Widgets
   REQUIRED
   )
endif()
message(".. QT_VERSION_MAJOR   :" ${QT_VERSION_MAJOR})

find_package(
  Qt${QT_VERSION_MAJOR}
 COMPONENTS
 Widgets
 REQUIRED)

Include(FetchContent)

FetchContent_Declare(
  GTest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0)

FetchContent_MakeAvailable(GTest)

enable_testing()

add_executable(
    ${PROJECT_NAME}
    tst_My_test.cpp
    main.cpp
    )

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    gmock gmock_main
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    )

