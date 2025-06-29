# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
include_directories(${CMAKE_CURRENT_BINARY_DIR}/)
add_library(translator_deepl MODULE)
ecm_qt_declare_logging_category(translator_debug_deepl_SRCS
    HEADER deepltranslator_debug.h
    IDENTIFIER TRANSLATOR_DEEPL_LOG
    CATEGORY_NAME org.kde.kf.texttranslator.deepl
    OLD_CATEGORY_NAMES org.kde.kf6.texttranslator.deepl
    DESCRIPTION "deepl translator"
    EXPORT KTEXTADDONS
)
target_sources(
    translator_deepl
    PRIVATE
        ${translator_debug_deepl_SRCS}
        deeplengineclient.cpp
        deeplengineclient.h
        deeplengineplugin.cpp
        deeplengineplugin.h
        deeplengineconfiguredialog.h
        deeplengineconfiguredialog.cpp
        deeplengineconfigurewidget.h
        deeplengineconfigurewidget.cpp
        deeplengineutil.h
        deeplengineutil.cpp
)

target_link_libraries(
    translator_deepl
    PRIVATE
        KF6::TextTranslator
        KF6::I18n
        KF6::ConfigCore
        KF6::TextAddonsWidgets
        KF6::WidgetsAddons
)
target_link_libraries(translator_deepl PRIVATE qt6keychain)

install(TARGETS translator_deepl DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/translator/)
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
