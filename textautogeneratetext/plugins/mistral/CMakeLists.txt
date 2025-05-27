# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

add_library(textautogeneratemistral)
kconfig_add_kcfg_files(textautogeneratemistral GENERATE_MOC mistralsettings.kcfgc)

ecm_qt_declare_logging_category(textautogeneratemistral
    HEADER autogeneratetext_mistral_debug.h
    IDENTIFIER AUTOGENERATETEXT_MISTRAL_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.mistral
    DESCRIPTION "autogenerate text mistral (lib)"
    EXPORT KTEXTADDONS
)

target_sources(textautogeneratemistral PRIVATE
    mistralconfiguredialog.h
    mistralconfiguredialog.cpp
    mistralconfigurewidget.h
    mistralconfigurewidget.cpp

    mistralmanager.h
    mistralmanager.cpp

    mistralreply.h
    mistralreply.cpp

    mistralutils.h
    mistralutils.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(textautogeneratemistral PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(textautogeneratemistral BASE_NAME textautogeneratemistral)

target_link_libraries(textautogeneratemistral
    PUBLIC
    KF6::TextAutoGenerateText
    PRIVATE
    KF6::I18n
    KF6::ConfigGui
    KF6::CoreAddons
    KF6::WidgetsAddons
)
set_target_properties(textautogeneratemistral PROPERTIES
    VERSION ${TEXTAUTOGENERATETEXT_VERSION}
    SOVERSION ${TEXTAUTOGENERATETEXT_SOVERSION}
    EXPORT_NAME TextAutoGenerateText
)

install(TARGETS textautogeneratemistral ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

######
add_library(autogeneratetext_mistral MODULE)


ecm_qt_declare_logging_category(autogeneratetext_mistral
    HEADER autogeneratetext_mistral_debug.h
    IDENTIFIER AUTOGENERATETEXT_MISTRAL_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.mistral
    DESCRIPTION "autogenerate text mistral"
    EXPORT KTEXTADDONS
)
target_sources(autogeneratetext_mistral PRIVATE
    mistralclient.h
    mistralclient.cpp
    mistralplugin.h
    mistralplugin.cpp
)

target_link_libraries(autogeneratetext_mistral
    PRIVATE
    KF6::TextAutoGenerateText
    KF6::I18n
    KF6::ConfigGui
    KF6::WidgetsAddons
    KF6::CoreAddons
    textautogeneratemistral
    qt6keychain
)

install(TARGETS autogeneratetext_mistral  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/textautogeneratetext/)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
