# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none
include_directories(${CMAKE_CURRENT_BINARY_DIR}/)
add_library(translator_lingva MODULE)

ecm_qt_declare_logging_category(translator_lingva_debug_SRCS
    HEADER lingvatranslator_debug.h
    IDENTIFIER TRANSLATOR_LINGVA_LOG
    CATEGORY_NAME org.kde.kf.texttranslator.lingva
    OLD_CATEGORY_NAMES org.kde.kf6.texttranslator.lingva
    DESCRIPTION "lingva translator"
    EXPORT KTEXTADDONS
)

target_sources(
    translator_lingva
    PRIVATE
        ${translator_lingva_debug_SRCS}
        lingvaengineclient.cpp
        lingvaengineclient.h
        lingvaengineplugin.cpp
        lingvaengineplugin.h
        lingvaenginedialog.h
        lingvaenginedialog.cpp
        lingvaenginewidget.h
        lingvaenginewidget.cpp
        lingvaengineutil.h
        lingvaengineutil.cpp
)

target_link_libraries(
    translator_lingva
    PRIVATE
        KF6::TextTranslator
        KF6::I18n
        KF6::ConfigCore
        KF6::TextAddonsWidgets
        KF6::WidgetsAddons
)

install(TARGETS translator_lingva DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/translator/)
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
