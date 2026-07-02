# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
# SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

add_library(textautogenerateplugincommon)
ecm_qt_declare_logging_category(textautogenerateplugincommon
    HEADER autogeneratetext_plugincommon_debug.h
    IDENTIFIER AUTOGENERATETEXT_PLUGINCOMMON_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.plugincommon
    DESCRIPTION "autogenerate text plugincommon (lib)"
    EXPORT KTEXTADDONS
)

target_sources(
    textautogenerateplugincommon
    PRIVATE
        plugincommonmodelinfosdelegateutils.cpp
        plugincommonmodelinfosdelegateutils.h
        plugincommonmodelinstalledinfo.cpp
        plugincommonmodelinstalledinfo.h
        plugincommonmodelinstalledinfosdelegate.cpp
        plugincommonmodelinstalledinfosdelegate.h
        plugincommonmodelinstalledinfosmodel.cpp
        plugincommonmodelinstalledinfosmodel.h
        plugincommonmodelinstalledinfossortproxymodel.cpp
        plugincommonmodelinstalledinfossortproxymodel.h
        plugincommonsettings.h
        plugincommonsettings.cpp
        plugincommonsaveloadpassword.h
        plugincommonsaveloadpassword.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        textautogenerateplugincommon
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(textautogenerateplugincommon BASE_NAME textautogenerateplugincommon)

target_link_libraries(textautogenerateplugincommon PUBLIC KF6::TextAutoGenerateText PRIVATE qt6keychain)

set_target_properties(
    textautogenerateplugincommon
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
        textautogenerateplugincommon
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
