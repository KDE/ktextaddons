# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
include_directories(${CMAKE_CURRENT_BINARY_DIR}/)
add_library(translator_bing MODULE)
ecm_qt_declare_logging_category(translator_debug_bing_SRCS
    HEADER bingtranslator_debug.h
    IDENTIFIER TRANSLATOR_BING_LOG
    CATEGORY_NAME org.kde.kf.texttranslator.bing
    OLD_CATEGORY_NAMES org.kde.kf6.texttranslator.bing
    DESCRIPTION "bing translator"
    EXPORT KTEXTADDONS
)
target_sources(
    translator_bing
    PRIVATE
        ${translator_debug_bing_SRCS}
        bingengineclient.cpp
        bingengineclient.h
        bingengineplugin.cpp
        bingengineplugin.h
)

target_link_libraries(
    translator_bing
    PRIVATE
        KF6::TextTranslator
        KF6::I18n
)

install(TARGETS translator_bing DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/translator/)
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
