# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

add_library(textautogenerateollamaonline)
ecm_qt_declare_logging_category(textautogenerateollamaonline
    HEADER autogeneratetext_ollamaonline_debug.h
    IDENTIFIER AUTOGENERATETEXT_OLLAMAONLINE_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.ollamaonline
    DESCRIPTION "autogenerate text ollamaonline (lib)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(textautogenerateollamaonline
    HEADER autogeneratetext_ollamaonline_generate_json_debug.h
    IDENTIFIER AUTOGENERATETEXT_OLLAMAONLINE_GENERATE_JSON_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.ollamaonline_json
    DESCRIPTION "autogenerate text ollamaonline (json info)"
    EXPORT KTEXTADDONS
)

target_sources(
    textautogenerateollamaonline
    PRIVATE
        ollamaonlineconfiguredialog.h
        ollamaonlineconfiguredialog.cpp
        ollamaonlineconfigurewidget.h
        ollamaonlineconfigurewidget.cpp
        ollamaonlinesettings.cpp
        ollamaonlinesettings.h
)

# precompiled headers support
if(ENABLE_PCH)
    target_precompile_headers(
        textautogenerateollamaonline
        PRIVATE
            <QObject>
            <QDebug>
            <QJsonObject>
            <QString>
    )
endif()

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        textautogenerateollamaonline
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(textautogenerateollamaonline BASE_NAME textautogenerateollamaonline)

target_link_libraries(
    textautogenerateollamaonline
    PUBLIC
        KF6::TextAutoGenerateText
    PRIVATE
        KF6::I18n
        KF6::ConfigGui
        KF6::CoreAddons
        KF6::WidgetsAddons
)
set_target_properties(
    textautogenerateollamaonline
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
        textautogenerateollamaonline
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

####
add_library(autogeneratetext_ollamaonline MODULE)

ecm_qt_declare_logging_category(autogeneratetext_ollamaonline
    HEADER autogeneratetext_ollamaonline_plugin_debug.h
    IDENTIFIER autogeneratetext_ollamaonline_PLUGIN_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.ollama_plugin
    DESCRIPTION "autogenerate text ollama online (plugin)"
    EXPORT KTEXTADDONS
)

target_sources(
    autogeneratetext_ollamaonline
    PRIVATE
        ollamaonlineclient.h
        ollamaonlineclient.cpp
        ollamaonlineplugin.h
        ollamaonlineplugin.cpp
)

target_link_libraries(
    autogeneratetext_ollamaonline
    PUBLIC
        KF6::TextAutoGenerateText
    PRIVATE
        textautogenerateollamaonline
        KF6::ConfigGui
        KF6::CoreAddons
        KF6::I18n
        KF6::WidgetsAddons
)
install(TARGETS autogeneratetext_ollamaonline DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/textautogeneratetext/)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
