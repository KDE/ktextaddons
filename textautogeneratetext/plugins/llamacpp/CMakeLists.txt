# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

add_library(textautogeneratellamacpp)
ecm_qt_declare_logging_category(textautogeneratellamacpp
    HEADER autogeneratetext_llamacpp_debug.h
    IDENTIFIER AUTOGENERATETEXT_LLAMACPP_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.llamacpp
    DESCRIPTION "autogenerate text llamacpp (lib)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(textautogeneratellamacpp
    HEADER autogeneratetext_llamacpp_generate_json_debug.h
    IDENTIFIER AUTOGENERATETEXT_LMSTUDIO_GENERATE_JSON_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.llamacpp_json
    DESCRIPTION "autogenerate text llamacpp (json info)"
    EXPORT KTEXTADDONS
)

target_sources(
    textautogeneratellamacpp
    PRIVATE
        # This empty dummy is required to let MSVC create the import library (.lib),
        # given that there is only a header, but no other cpp source files yet
        empty_dummy.cpp
        textautogeneratellamacpp_private_export.h
)

# precompiled headers support
if(ENABLE_PCH)
    target_precompile_headers(
        textautogeneratellamacpp
        PRIVATE
            <QObject>
            <QDebug>
            <QJsonObject>
            <QString>
    )
endif()

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        textautogeneratellamacpp
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(textautogeneratellamacpp BASE_NAME textautogeneratellamacpp)

target_link_libraries(
    textautogeneratellamacpp
    PUBLIC
        KF6::TextAutoGenerateText
        textautogenerateplugincommon
    PRIVATE
        KF6::I18n
        KF6::ConfigGui
        KF6::CoreAddons
        KF6::WidgetsAddons
        KF6::TextAddonsWidgets
        KF6::KIOWidgets
)
set_target_properties(
    textautogeneratellamacpp
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
        textautogeneratellamacpp
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

#####

add_library(autogeneratetext_llamacpp MODULE)

ecm_qt_declare_logging_category(autogeneratetext_llamacpp
    HEADER autogeneratetext_llamacpp_plugin_debug.h
    IDENTIFIER AUTOGENERATETEXT_LLAMACPP_PLUGIN_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.llamacpp_plugin
    DESCRIPTION "autogenerate text llamacpp (plugin)"
    EXPORT KTEXTADDONS
)

target_sources(
    autogeneratetext_llamacpp
    PRIVATE
        llamacppclient.h
        llamacppclient.cpp
        llamacppplugin.h
        llamacppplugin.cpp
)

target_link_libraries(
    autogeneratetext_llamacpp
    PRIVATE
        textautogeneratellamacpp
        KF6::ConfigGui
        KF6::CoreAddons
        KF6::I18n
        KF6::WidgetsAddons
        qt6keychain
)
install(TARGETS autogeneratetext_llamacpp DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/textautogeneratetext/)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
