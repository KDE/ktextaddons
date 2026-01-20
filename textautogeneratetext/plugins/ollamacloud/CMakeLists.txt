# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

add_library(textautogenerateollamacloud)
ecm_qt_declare_logging_category(textautogenerateollamacloud
    HEADER autogeneratetext_ollamacloud_debug.h
    IDENTIFIER AUTOGENERATETEXT_OLLAMACLOUD_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.ollamacloud
    DESCRIPTION "autogenerate text ollamacloud (lib)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(textautogenerateollamacloud
    HEADER autogeneratetext_ollamacloud_generate_json_debug.h
    IDENTIFIER AUTOGENERATETEXT_OLLAMACLOUD_GENERATE_JSON_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.ollamacloud_json
    DESCRIPTION "autogenerate text ollamacloud (json info)"
    EXPORT KTEXTADDONS
)

target_sources(
    textautogenerateollamacloud
    PRIVATE
        ollamacloudconfiguredialog.h
        ollamacloudconfiguredialog.cpp
        ollamacloudconfigurewidget.h
        ollamacloudconfigurewidget.cpp
        ollamacloudsettings.cpp
        ollamacloudsettings.h
        ollamacloudmanager.h
        ollamacloudmanager.cpp
        textautogenerateollamacloud_private_export.h
)

# precompiled headers support
if(ENABLE_PCH)
    target_precompile_headers(
        textautogenerateollamacloud
        PRIVATE
            <QObject>
            <QDebug>
            <QJsonObject>
            <QString>
    )
endif()

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        textautogenerateollamacloud
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(textautogenerateollamacloud BASE_NAME textautogenerateollamacloud)

target_link_libraries(
    textautogenerateollamacloud
    PUBLIC
        KF6::TextAutoGenerateText
    PRIVATE
        KF6::I18n
        KF6::ConfigGui
        KF6::CoreAddons
        KF6::WidgetsAddons
        textautogenerateollamacommon
)
set_target_properties(
    textautogenerateollamacloud
    PROPERTIES
        VERSION
            ${TEXTAUTOGENERATETEXT_VERSION}
        SOVERSION
            ${TEXTAUTOGENERATETEXT_SOVERSION}
        EXPORT_NAME
            TextAutoGenerateText
)

install(
    TARGETS
        textautogenerateollamacloud
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

####
add_library(autogeneratetext_ollamacloud MODULE)

ecm_qt_declare_logging_category(autogeneratetext_ollamacloud
    HEADER autogeneratetext_ollamacloud_plugin_debug.h
    IDENTIFIER AUTOGENERATETEXT_OLLAMACLOUD_PLUGIN_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.ollamacloud_plugin
    DESCRIPTION "autogenerate text ollama cloud (plugin)"
    EXPORT KTEXTADDONS
)

target_sources(
    autogeneratetext_ollamacloud
    PRIVATE
        ollamacloudclient.h
        ollamacloudclient.cpp
        ollamacloudplugin.h
        ollamacloudplugin.cpp
)

target_link_libraries(
    autogeneratetext_ollamacloud
    PUBLIC
        KF6::TextAutoGenerateText
    PRIVATE
        textautogenerateollamacloud
        KF6::ConfigGui
        KF6::CoreAddons
        KF6::I18n
        KF6::WidgetsAddons
        qt6keychain
        textautogenerateollamacommon
)
install(TARGETS autogeneratetext_ollamacloud DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/textautogeneratetext/)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
