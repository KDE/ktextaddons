# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
add_definitions(-DTRANSLATION_DOMAIN=\"libtextautogeneratetext\")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOGENERATETEXT
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetext_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextConfigVersion.cmake"
    SOVERSION 1
)

if(NOT WIN32 AND NOT APPLE)
    set(HAVE_KTEXTADDONS_TEXTAUTOGENERATE_DBUS_SUPPORT TRUE)
endif()

if(TARGET Qt6::TextToSpeech)
    set(HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT TRUE)
endif()

configure_file(config-textautogeneratetext.h.in ${CMAKE_CURRENT_BINARY_DIR}/config-textautogeneratetext.h)

add_subdirectory(core)
add_subdirectory(widgets)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_subdirectory(plugins)
add_subdirectory(tools)
