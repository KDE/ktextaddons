# - Find Slimt
# Find the slimt library.
#
# This module defines
#  slimt_FOUND - whether the slimt library was found
#  slimt_LIBRARIES - the slimt library
#  slimt_INCLUDE_DIRS - the include path of the slimt library

# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
#
# SPDX-License-Identifier: BSD-3-Clause

if (slimt_INCLUDE_DIRS AND slimt_LIBRARIES)
  # Already in cache
  set (slimt_FOUND TRUE)
else ()
    find_path(slimt_INCLUDE_DIRS
        NAMES slimt.hh
        PATH_SUFFIXES slimt
    )

    MESSAGE(STATUS "slimt_INCLUDE_DIRS************** ${slimt_INCLUDE_DIRS}")

    find_library(slimt_LIBRARIES
        NAMES slimt
    )

    MESSAGE(STATUS "slimt_LIBRARIES **************** ${slimt_LIBRARIES}")

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(slimt DEFAULT_MSG slimt_LIBRARIES slimt_INCLUDE_DIRS)
endif()

mark_as_advanced(slimt_INCLUDE_DIRS slimt_LIBRARIES)
if (slimt_FOUND)
   add_library(slimt::Lib UNKNOWN IMPORTED)
   set_target_properties(slimt::Lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${slimt_INCLUDE_DIRS} IMPORTED_LOCATION ${slimt_LIBRARIES})
endif()
