# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
include_directories(${CMAKE_CURRENT_BINARY_DIR}/)
add_library(translator_bing MODULE)
ecm_qt_declare_logging_category(translator_debug_bing_SRCS
    HEADER bingtranslator_debug.h
    IDENTIFIER TRANSLATOR_BING_LOG
    CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.texttranslator.bing
    DESCRIPTION "bing translator"
    EXPORT KTEXTADDONS
)
target_sources(translator_bing PRIVATE
    ${translator_debug_bing_SRCS}
    bingengineclient.cpp
    bingengineclient.h
    bingengineplugin.cpp
    bingengineplugin.h
)

target_link_libraries(translator_bing PRIVATE KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n)

install(TARGETS translator_bing  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/translator/)
if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()

