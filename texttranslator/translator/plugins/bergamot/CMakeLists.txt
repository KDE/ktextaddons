# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none
include_directories(${CMAKE_CURRENT_BINARY_DIR}/)

add_library(libbergamot
    translatormodel.h translatormodel.cpp)

target_sources(libbergamot PRIVATE

    begamotenginedialog.h
    begamotenginedialog.cpp
    bergamotenginewidget.h
    bergamotenginewidget.cpp

    managermodeltranslator.h
    managermodeltranslator.cpp
    translator.h
    translator.cpp

    bergamotutils.h
    bergamotutils.cpp

    libbergamot_private_export.h
)

generate_export_header(libbergamot BASE_NAME libbergamot)

ecm_qt_declare_logging_category(libbergamot HEADER libbergamot_debug.h IDENTIFIER TRANSLATOR_LIBBERGAMOT_LOG
    CATEGORY_NAME org.kde.ruqola DESCRIPTION "lib bergamot translator" EXPORT KTEXTADDONS)

target_link_libraries(libbergamot  Qt::Widgets KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::TextTranslator)

set_target_properties(libbergamot
    PROPERTIES OUTPUT_NAME ruqolacore VERSION ${TEXTTRANSLATE_VERSION} SOVERSION ${TEXTTRANSLATE_SOVERSION}
)

install(TARGETS libbergamot ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)


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

)

target_link_libraries(translator_bergamot PRIVATE KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n libbergamot)

install(TARGETS translator_bergamot  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/translator/)

if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()
