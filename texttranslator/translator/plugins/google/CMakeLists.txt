# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none
include_directories(${CMAKE_CURRENT_BINARY_DIR}/)
add_library(translator_google MODULE)
ecm_qt_declare_logging_category(translator_debug_google_SRCS
    HEADER googletranslator_debug.h
    IDENTIFIER TRANSLATOR_GOOGLE_LOG
    CATEGORY_NAME org.kde.kf.texttranslator.google
    OLD_CATEGORY_NAMES org.kde.kf6.texttranslator.google
    DESCRIPTION "google translator"
    EXPORT KTEXTADDONS
)
target_sources(
    translator_google
    PRIVATE
        ${translator_debug_google_SRCS}
        googleengineclient.h
        googleengineclient.cpp
        googleengineplugin.h
        googleengineplugin.cpp
)

target_link_libraries(translator_google PRIVATE KF6::TextTranslator KF6::I18n)

install(
    TARGETS translator_google
    DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/translator/
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
