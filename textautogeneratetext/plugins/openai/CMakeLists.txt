# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

add_library(textautogenerateopenai)

ecm_qt_declare_logging_category(textautogenerateopenai
    HEADER autogeneratetext_openai_debug.h
    IDENTIFIER AUTOGENERATETEXT_OPENAI_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.openai
    DESCRIPTION "autogenerate text openai (lib)"
    EXPORT KTEXTADDONS
)

target_sources(textautogenerateopenai PRIVATE
    openaiconfiguredialog.h
    openaiconfiguredialog.cpp
    openaiconfigurewidget.h
    openaiconfigurewidget.cpp
    openaimanager.cpp
    openaimanager.h
    openaireply.cpp
    openaireply.h
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(textautogenerateopenai PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(textautogenerateopenai BASE_NAME textautogenerateopenai)

target_link_libraries(textautogenerateopenai
    PUBLIC
    KF6::TextAutoGenerateText
    PRIVATE
    KF6::I18n
    KF6::ConfigGui
    KF6::CoreAddons
    KF6::WidgetsAddons
)
set_target_properties(textautogenerateopenai PROPERTIES
    VERSION ${TEXTAUTOGENERATETEXT_VERSION}
    SOVERSION ${TEXTAUTOGENERATETEXT_SOVERSION}
    EXPORT_NAME TextAutoGenerateText
)

install(TARGETS textautogenerateopenai ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

#######

add_library(autogeneratetext_openai MODULE)

target_sources(autogeneratetext_openai PRIVATE
    openaiclient.h
    openaiclient.cpp
    openaiplugin.h
    openaiplugin.cpp

)

target_link_libraries(autogeneratetext_openai
    PRIVATE
    KF6::TextAutoGenerateText
    KF6::I18n
    KF6::ConfigGui
    KF6::WidgetsAddons
    KF6::CoreAddons
    qt6keychain
    textautogenerateopenai
)

install(TARGETS autogeneratetext_openai  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/textautogeneratetext/)
