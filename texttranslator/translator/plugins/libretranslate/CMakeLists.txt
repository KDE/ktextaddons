# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none

include_directories(${CMAKE_CURRENT_BINARY_DIR}/)
add_library(translator_libretranslate MODULE)

ecm_qt_declare_logging_category(translator_libretranslate_debug_SRCS
    HEADER libretranslatetranslator_debug.h
    IDENTIFIER TRANSLATOR_LIBRETRANSLATE_LOG
    CATEGORY_NAME org.kde.kf.texttranslator.libretranslate
    OLD_CATEGORY_NAMES org.kde.kf6.texttranslator.libretranslate
    DESCRIPTION "libretranslate translator"
    EXPORT KTEXTADDONS
)

target_sources(translator_libretranslate PRIVATE
    ${translator_libretranslate_debug_SRCS}
    libretranslateengineclient.cpp
    libretranslateengineclient.h
    libretranslateengineplugin.cpp
    libretranslateengineplugin.h
    libretranslateengineconfiguredialog.h
    libretranslateengineconfiguredialog.cpp
    libretranslateengineconfigurewidget.h
    libretranslateengineconfigurewidget.cpp
    libretranslateengineutil.h
    libretranslateengineutil.cpp
)

target_link_libraries(translator_libretranslate PRIVATE KF6::TextTranslator
    KF6::I18n
    KF6::ConfigCore
    KF6::TextAddonsWidgets
    KF6::WidgetsAddons
)
target_link_libraries(translator_libretranslate PRIVATE qt6keychain)
install(TARGETS translator_libretranslate  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/translator/)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
