# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none
include(ExternalProject)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/)

if(0)
set(build_dir ${CMAKE_CURRENT_DIR}/3rdparty)

ExternalProject_Add(3rdparty_bergamot
#        PREFIX ${build_dir}/bergamot-translator
        GIT_REPOSITORY "https://github.com/browsermt/bergamot-translator.git"
        GIT_TAG "main"
        CMAKE_ARGS -DBLA_PREFER_PKGCONFIG:BOOL=ON
        -DBLA_PKGCONFIG_BLAS:STRING=openblas
        -Dcblas_cblas_LIBRARY:STRING=cblas
)
endif()

add_library(libbergamot)

target_sources(libbergamot PRIVATE

    begamotenginedialog.h
    begamotenginedialog.cpp
    bergamotenginewidget.h
    bergamotenginewidget.cpp

    managermodeltranslator.h
    managermodeltranslator.cpp
    translator.h
    translator.cpp

    bergamotengineutils.h
    bergamotengineutils.cpp

    translatormodel.h
    translatormodel.cpp
    bergamotenginelanguagewidget.h
    bergamotenginelanguagewidget.cpp

    bergamotenginesettingswidget.h
    bergamotenginesettingswidget.cpp

    libbergamot_private_export.h

    translatorproxymodel.h
    translatorproxymodel.cpp

    bergamotmarianinterface.h
    bergamotmarianinterface.cpp

    extractlanguagejob.h
    extractlanguagejob.cpp

    downloadlanguagejob.h
    downloadlanguagejob.cpp
)

generate_export_header(libbergamot BASE_NAME libbergamot)

ecm_qt_declare_logging_category(libbergamot HEADER libbergamot_debug.h IDENTIFIER TRANSLATOR_LIBBERGAMOT_LOG
    CATEGORY_NAME org.kde.ruqola DESCRIPTION "lib bergamot translator" EXPORT KTEXTADDONS)

target_link_libraries(libbergamot  Qt::Widgets
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::TextTranslator
    KF${KF_MAJOR_VERSION}::ConfigWidgets
    KF${KF_MAJOR_VERSION}::TextAddonsWidgets
    KF${KF_MAJOR_VERSION}::WidgetsAddons
    KF${KF_MAJOR_VERSION}::Archive
)

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
    add_subdirectory(tests)
endif()
