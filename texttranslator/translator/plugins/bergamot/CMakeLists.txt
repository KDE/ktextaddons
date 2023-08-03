# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none
include_directories(${CMAKE_CURRENT_BINARY_DIR}/)
add_library(translator_bergamot MODULE)
ecm_qt_declare_logging_category(translator_debug_bergamot_SRCS
    HEADER bergamottranslator_debug.h
    IDENTIFIER TRANSLATOR_BERGAMOT_LOG
    CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.texttranslator.bergamot
    DESCRIPTION "bergamot translator"
    EXPORT KTEXTADDONS
)

target_sources(translator_bergamot PRIVATE
    ${translator_debug_bergamot_SRCS}
    bergamotengineplugin.cpp
    bergamotengineplugin.h
    bergamotengineclient.cpp
    bergamotengineclient.h

    begamotenginedialog.h
    begamotenginedialog.cpp
    bergamotenginewidget.h
    bergamotenginewidget.cpp
)

target_link_libraries(translator_bergamot PRIVATE KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n)

install(TARGETS translator_bergamot  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/translator/)

if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()
