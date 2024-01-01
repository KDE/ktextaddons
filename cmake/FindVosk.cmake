# - Find Vosk
# Find the Vosk library.
#
# This module defines
#  vosk_FOUND - whether the vosk library was found
#  vosk_LIBRARIES - the vosk library
#  vosk_INCLUDE_DIRS - the include path of the vosk library

# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
#
# SPDX-License-Identifier: BSD-3-Clause

if (vosk_INCLUDE_DIRS AND vosk_LIBRARIES)
  # Already in cache
  set (vosk_FOUND TRUE)
else ()
  find_library(vosk_LIBRARIES
    NAMES vosk libvosk
    NO_DEFAULT_PATH
  )
  MESSAGE(STATUS "vosk_LIBRARIES **************** ${vosk_LIBRARIES}")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(vosk DEFAULT_MSG vosk_LIBRARIES vosk_INCLUDE_DIRS)
endif()

mark_as_advanced(vosk_INCLUDE_DIRS vosk_LIBRARIES)
if (vosk_FOUND)
   add_library(vosk::Lib UNKNOWN IMPORTED)
   set_target_properties(vosk::Lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${vosk_INCLUDE_DIRS} IMPORTED_LOCATION ${vosk_LIBRARIES})
endif()

