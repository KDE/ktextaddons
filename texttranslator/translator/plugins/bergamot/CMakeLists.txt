# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>
# slimt reports i/o failures (missing or unreadable model files) by throwing.
kde_enable_exceptions()

add_library(libbergamot)

target_sources(
    libbergamot
    PRIVATE
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
        translation.cpp
        translation.h
)

generate_export_header(libbergamot BASE_NAME libbergamot)

ecm_qt_declare_logging_category(libbergamot HEADER libbergamot_debug.h IDENTIFIER TRANSLATOR_LIBBERGAMOT_LOG
    CATEGORY_NAME org.kde.libbergamottranslator DESCRIPTION "lib bergamot translator" EXPORT KTEXTADDONS
)

target_link_libraries(
    libbergamot
    Qt::Widgets
    KF6::I18n
    KF6::ConfigCore
    KF6::ConfigGui
    KF6::TextTranslator
    KF6::TextAddonsWidgets
    KF6::WidgetsAddons
    KF6::Archive
    slimt::slimt-shared
)

set_target_properties(
    libbergamot
    PROPERTIES
        OUTPUT_NAME
            libbergamot
        VERSION
            ${TEXTTRANSLATE_VERSION}
        SOVERSION
            ${TEXTTRANSLATE_SOVERSION}
)

install(
    TARGETS
        libbergamot
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

add_library(translator_bergamot MODULE)
ecm_qt_declare_logging_category(translator_debug_bergamot_SRCS
    HEADER bergamottranslator_debug.h
    IDENTIFIER TRANSLATOR_BERGAMOT_LOG
    CATEGORY_NAME org.kde.kf.texttranslator.bergamot
    DESCRIPTION "bergamot translator"
    EXPORT KTEXTADDONS
)

target_sources(
    translator_bergamot
    PRIVATE
        ${translator_debug_bergamot_SRCS}
        bergamotengineplugin.cpp
        bergamotengineplugin.h
        bergamotengineclient.cpp
        bergamotengineclient.h
)

target_link_libraries(
    translator_bergamot
    PRIVATE
        KF6::TextTranslator
        KF6::I18n
        libbergamot
)

install(TARGETS translator_bergamot DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/translator/)

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
