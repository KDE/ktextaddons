# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

add_library(textautogeneratelmstudio)
ecm_qt_declare_logging_category(textautogeneratelmstudio
    HEADER autogeneratetext_lmstudio_debug.h
    IDENTIFIER AUTOGENERATETEXT_LMSTUDIO_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.lmstudio
    DESCRIPTION "autogenerate text lmstudio (lib)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(textautogeneratelmstudio
    HEADER autogeneratetext_lmstudio_generate_json_debug.h
    IDENTIFIER AUTOGENERATETEXT_LMSTUDIO_GENERATE_JSON_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.lmstudio_json
    DESCRIPTION "autogenerate text lmstudio (json info)"
    EXPORT KTEXTADDONS
)

target_sources(
    textautogeneratelmstudio
    PRIVATE
        lmstudioconfiguredialog.cpp
        lmstudioconfiguredialog.h
        lmstudioconfigurewidget.cpp
        lmstudioconfigurewidget.h
        lmstudioinstalledmodelwidget.cpp
        lmstudioinstalledmodelwidget.h
        lmstudiomanager.h
        lmstudiomanager.cpp
        lmstudioreply.h
        lmstudioreply.cpp
        lmstudiosettings.h
        lmstudiosettings.cpp
        modelsmanager/lmstudiomodelinfosdelegateutils.cpp
        modelsmanager/lmstudiomodelinfosdelegateutils.h
        modelsmanager/lmstudiomodelinstalledinfosdelegate.cpp
        modelsmanager/lmstudiomodelinstalledinfosdelegate.h
        modelsmanager/lmstudiomodelinstalledinfo.h
        modelsmanager/lmstudiomodelinstalledinfo.cpp
        modelsmanager/lmstudiomodelinstalledinfosmodel.h
        modelsmanager/lmstudiomodelinstalledinfosmodel.cpp
        modelsmanager/lmstudiomodelinstalledinfossortproxymodel.cpp
        modelsmanager/lmstudiomodelinstalledinfossortproxymodel.h
        modelsmanager/lmstudiomodelinstalledinfowidget.cpp
        modelsmanager/lmstudiomodelinstalledinfowidget.h
        modelsmanager/lmstudiomodelinstalledwidget.cpp
        modelsmanager/lmstudiomodelinstalledwidget.h
        textautogeneratelmstudio_private_export.h
)

# precompiled headers support
if(ENABLE_PCH)
  target_precompile_headers(
        textautogeneratelmstudio
        PRIVATE
            <QObject>
            <QDebug>
            <QJsonObject>
            <QString>
    )
endif()

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
  set_target_properties(
        textautogeneratelmstudio
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(textautogeneratelmstudio BASE_NAME textautogeneratelmstudio)

target_link_libraries(
    textautogeneratelmstudio
    PUBLIC
        KF6::TextAutoGenerateText
    PRIVATE
        KF6::I18n
        KF6::ConfigGui
        KF6::CoreAddons
        KF6::WidgetsAddons
        KF6::TextAddonsWidgets
        KF6::KIOWidgets
)
set_target_properties(
    textautogeneratelmstudio
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
        textautogeneratelmstudio
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

#####

add_library(autogeneratetext_lmstudio MODULE)

ecm_qt_declare_logging_category(autogeneratetext_lmstudio
    HEADER autogeneratetext_lmstudio_plugin_debug.h
    IDENTIFIER AUTOGENERATETEXT_LMSTUDIO_PLUGIN_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.lmstudio_plugin
    DESCRIPTION "autogenerate text lmstudio (plugin)"
    EXPORT KTEXTADDONS
)

target_sources(
    autogeneratetext_lmstudio
    PRIVATE
        lmstudioclient.h
        lmstudioclient.cpp
        lmstudioplugin.h
        lmstudioplugin.cpp
)

target_link_libraries(
    autogeneratetext_lmstudio
    PRIVATE
        textautogeneratelmstudio
        KF6::ConfigGui
        KF6::CoreAddons
        KF6::I18n
        KF6::WidgetsAddons
        qt6keychain
)
install(TARGETS autogeneratetext_lmstudio DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/textautogeneratetext/)

if(BUILD_TESTING)
  # add_subdirectory(autotests)
  # add_subdirectory(tests)
endif()
