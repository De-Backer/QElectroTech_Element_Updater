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

find_package(
  QT
  NAMES
  Qt6
  Qt5
  COMPONENTS
  LinguistTools
  REQUIRED
  )

find_package(
  Qt${QT_VERSION_MAJOR}
  COMPONENTS
  LinguistTools
  REQUIRED
  )
set(TS_FILES QElectroTech_Element_Updater_nl_BE.ts)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR}${TS_FILES})
