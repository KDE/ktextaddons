# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

add_library(textautogenerategenericnetwork)

ecm_qt_declare_logging_category(textautogenerategenericnetwork
    HEADER autogeneratetext_genericnetwork_debug.h
    IDENTIFIER AUTOGENERATETEXT_GENERICNETWORK_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.genericnetwork
    DESCRIPTION "autogenerate text genericnetwork (lib)"
    EXPORT KTEXTADDONS
)

target_sources(
    textautogenerategenericnetwork
    PRIVATE
        genericnetworkmanager.h
        genericnetworkmanager.cpp
        genericnetworkserverinfo.h
        genericnetworkserverinfo.cpp
        genericnetworkconfiguredialog.h
        genericnetworkconfiguredialog.cpp
        genericnetworkavailablemodelwidget.h
        genericnetworkavailablemodelwidget.cpp
        genericnetworkreply.h
        genericnetworkreply.cpp
        genericnetworknetworkpluginconfigurewidget.h
        genericnetworknetworkpluginconfigurewidget.cpp
        textautogenerategeneric_private_export.h
        genericnetworksettings.h
        genericnetworksettings.cpp
        modelsmanager/genericnetworkmodelavailableinfo.h
        modelsmanager/genericnetworkmodelavailableinfo.cpp
        modelsmanager/genericnetworkavailableinfosmodel.cpp
        modelsmanager/genericnetworkavailableinfosmodel.h
        modelsmanager/genericnetworkmodelavailableinfos.h
        modelsmanager/genericnetworkmodelavailableinfos.cpp
        modelsmanager/genericnetworkmodelavailablelistview.cpp
        modelsmanager/genericnetworkmodelavailablelistview.h
        modelsmanager/genericnetworkmodelavailableinfosdelegate.h
        modelsmanager/genericnetworkmodelavailableinfosdelegate.cpp
        modelsmanager/genericnetworkmodelinfosdelegateutils.h
        modelsmanager/genericnetworkmodelinfosdelegateutils.cpp
        modelsmanager/genericnetworkmodelavailablewidget.h
        modelsmanager/genericnetworkmodelavailablewidget.cpp
        modelsmanager/genericnetworkmodelavailableinfossortproxymodel.h
        modelsmanager/genericnetworkmodelavailableinfossortproxymodel.cpp
        modelsmanager/genericnetworkmodelavailableinfowidget.h
        modelsmanager/genericnetworkmodelavailableinfowidget.cpp
        modelsmanager/genericnetworkavailableinfosmanager.h
        modelsmanager/genericnetworkavailableinfosmanager.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        textautogenerategenericnetwork
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(textautogenerategenericnetwork BASE_NAME textautogenerategenericnetwork)

target_link_libraries(
    textautogenerategenericnetwork
    PUBLIC
        KF6::TextAutoGenerateText
    PRIVATE
        KF6::I18n
        KF6::ConfigGui
        KF6::CoreAddons
        KF6::WidgetsAddons
)
set_target_properties(
    textautogenerategenericnetwork
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
        textautogenerategenericnetwork
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

######
add_library(autogeneratetext_genericnetwork MODULE)

ecm_qt_declare_logging_category(autogeneratetext_genericnetwork
    HEADER autogeneratetext_genericnetwork_plugin_debug.h
    IDENTIFIER AUTOGENERATETEXT_GENERICNETWORK_PLUGIN_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.genericnetwork
    DESCRIPTION "autogenerate text genericnetwork plugin"
    EXPORT KTEXTADDONS
)
target_sources(
    autogeneratetext_genericnetwork
    PRIVATE
        genericnetworkclient.h
        genericnetworkclient.cpp
        genericnetworkplugin.h
        genericnetworkplugin.cpp
)

target_link_libraries(
    autogeneratetext_genericnetwork
    PRIVATE
        KF6::TextAutoGenerateText
        KF6::I18n
        KF6::ConfigGui
        KF6::WidgetsAddons
        KF6::CoreAddons
        textautogenerategenericnetwork
        qt6keychain
)
install(TARGETS autogeneratetext_genericnetwork DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/textautogeneratetext/)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
