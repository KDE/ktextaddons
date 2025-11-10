# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
add_definitions(-DTRANSLATION_DOMAIN=\"libtextautogeneratetext\")
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextAutoGenerateText")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOGENERATETEXT
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetext_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextConfigVersion.cmake"
    SOVERSION 1
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KF6TextAutoGenerateTextTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextAutoGenerateTextTargets.cmake
    NAMESPACE KF6::
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetext_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateText/
    COMPONENT Devel
)

if(NOT WIN32 AND NOT APPLE)
    set(HAVE_KTEXTADDONS_TEXTAUTOGENERATE_DBUS_SUPPORT TRUE)
endif()

if(TARGET Qt6::TextToSpeech)
    set(HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT TRUE)
endif()

configure_file(config-textautogeneratetext.h.in ${CMAKE_CURRENT_BINARY_DIR}/config-textautogeneratetext.h)

add_library(KF6TextAutoGenerateText)

add_library(KF6::TextAutoGenerateText ALIAS KF6TextAutoGenerateText)
ecm_qt_declare_logging_category(KF6TextAutoGenerateText HEADER textautogeneratetextcore_database_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext.database
    DESCRIPTION "KF6 (TextAutoGenerateText core database)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextAutoGenerateText HEADER textautogeneratetextcore_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_CORE_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext
    DESCRIPTION "KF6 (TextAutoGenerateText core)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextAutoGenerateText HEADER textautogeneratetextcore_memory_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext.memory
    DESCRIPTION "KF6 (TextAutoGenerateText core memory)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextAutoGenerateText HEADER textautogeneratetextcore_cmark_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_CORE_CMARK_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext.core.cmark
    DESCRIPTION "KF6 (TextAutoGenerateText core cmark)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextAutoGenerateText HEADER textautogeneratetextwidget_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_WIDGET_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext.widget
    DESCRIPTION "KF6 (TextAutoGenerateText widget)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextAutoGenerateText HEADER textautogeneratetextwidget_animation_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext.widget_animation
    DESCRIPTION "KF6 (TextAutoGenerateText widget animation)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextAutoGenerateText HEADER textautogeneratetextwidget_menu_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_WIDGET_MENU_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext.widget_menu
    DESCRIPTION "KF6 (TextAutoGenerateText widget menu)"
    EXPORT KTEXTADDONS
)

if(NOT WIN32 AND NOT APPLE)
    qt_add_dbus_adaptor(textautogeneratetext_dbs_adaptor_SRCS core/org.kde.textautogeneratetext.TextAutoGenerateManager.xml core/textautogeneratemanager.h TextAutoGenerateText::TextAutoGenerateManager)
endif()

kconfig_add_kcfg_files(KF6TextAutoGenerateText
    core/settings/textautogeneratetextglobalconfig.kcfgc
)

target_sources(
    KF6TextAutoGenerateText
    PRIVATE
        ${textautogeneratetext_dbs_adaptor_SRCS}
        core/textautogeneratetextutils.h
        core/textautogeneratetextutils.cpp
        core/textautogenerateengineloader.cpp
        core/textautogenerateengineloader.h
        core/textautogeneratetextclient.h
        core/textautogeneratetextclient.cpp
        core/textautogeneratetextplugin.h
        core/textautogeneratetextplugin.cpp
        core/textautogeneratemanager.h
        core/textautogeneratemanager.cpp
        core/textautogenerateengineaccessmanager.cpp
        core/textautogenerateengineaccessmanager.h
        core/textautogeneratechatsettings.h
        core/textautogeneratechatsettings.cpp
        core/textautogeneratetextreplyinfo.h
        core/textautogeneratetextreplyinfo.cpp
        core/textautogeneratesearchmessage.h
        core/textautogeneratesearchmessage.cpp
        core/textautogeneratemessage.h
        core/textautogeneratemessage.cpp
        core/textautogenerateanswerinfo.h
        core/textautogenerateanswerinfo.cpp
        core/textautogenerateattachment.h
        core/textautogenerateattachment.cpp
        core/textautogenerateattachments.h
        core/textautogenerateattachments.cpp
        core/textautogeneratemessageutils.h
        core/textautogeneratemessageutils.cpp
        core/textautogeneratetoolcalljob.h
        core/textautogeneratetoolcalljob.cpp
        core/textautogeneratechat.h
        core/textautogeneratechat.cpp
        core/textautogeneratesettings.h
        core/textautogeneratesettings.cpp
        core/textautogenerateattachmentutils.h
        core/textautogenerateattachmentutils.cpp
        core/textautogeneratepluginutils.h
        core/textautogeneratepluginutils.cpp
        core/textautogenerateblockcmarksupport.h
        core/textautogenerateblockcmarksupport.cpp
        core/models/textautogeneratemessagesmodel.h
        core/models/textautogeneratemessagesmodel.cpp
        core/models/textautogeneratesearchmessagesmodel.h
        core/models/textautogeneratesearchmessagesmodel.cpp
        core/models/textautogeneratehistorysortfilterproxymodel.h
        core/models/textautogeneratehistorysortfilterproxymodel.cpp
        core/models/textautogeneratehistorylistheadingsproxymodel.cpp
        core/models/textautogeneratehistorylistheadingsproxymodel.h
        core/models/textautogeneratechatsmodel.h
        core/models/textautogeneratechatsmodel.cpp
        core/models/textautogeneratetextinstancemodel.h
        core/models/textautogeneratetextinstancemodel.cpp
        core/models/textautogeneratetextinstancesortfilterproxymodel.h
        core/models/textautogeneratetextinstancesortfilterproxymodel.cpp
        core/localdatabase/textautogeneratelocaldatabaseutils.h
        core/localdatabase/textautogeneratelocaldatabaseutils.cpp
        core/localdatabase/textautogeneratelocaldatabaseabstract.h
        core/localdatabase/textautogeneratelocaldatabaseabstract.cpp
        core/localdatabase/textautogeneratelocalchatsdatabase.h
        core/localdatabase/textautogeneratelocalchatsdatabase.cpp
        core/localdatabase/textautogeneratelocalmessagesdatabase.cpp
        core/localdatabase/textautogeneratelocalmessagesdatabase.h
        core/localdatabase/textautogeneratelocaldatabasemanager.h
        core/localdatabase/textautogeneratelocaldatabasemanager.cpp
        core/textautogeneratesearchmessageutils.h
        core/textautogeneratesearchmessageutils.cpp
        core/textautogeneratereply.h
        core/textautogeneratereply.cpp
        core/textautogeneratetextrequest.cpp
        core/textautogeneratetextrequest.h
        core/textautogeneratemanagerbase.h
        core/textautogeneratemanagerbase.cpp
        core/textautogeneratetextinstance.h
        core/textautogeneratetextinstance.cpp
        core/textautogeneratetextinstancesmanager.h
        core/textautogeneratetextinstancesmanager.cpp
        core/jobs/textautogenerateexportchatbasejob.cpp
        core/jobs/textautogenerateexportchatbasejob.h
        core/jobs/textautogenerateexportchatasjsonjob.cpp
        core/jobs/textautogenerateexportchatasjsonjob.h
        core/jobs/textautogeneratesearchjob.h
        core/jobs/textautogeneratesearchjob.cpp
        core/jobs/textautogenerateaskjob.h
        core/jobs/textautogenerateaskjob.cpp
        core/jobs/textautogenerateimportchatbasejob.cpp
        core/jobs/textautogenerateimportchatbasejob.h
        core/tools/textautogeneratetexttoolplugin.h
        core/tools/textautogeneratetexttoolplugin.cpp
        core/tools/textautogeneratetexttoolpluginmanager.cpp
        core/tools/textautogeneratetexttoolpluginmanager.h
        core/tools/textautogeneratetexttoolpluginproperty.h
        core/tools/textautogeneratetexttoolpluginproperty.cpp
        core/tools/textautogeneratetexttoolpluginjob.h
        core/tools/textautogeneratetexttoolpluginjob.cpp
        core/textautogeneratesearchmessagesettings.h
        core/textautogeneratesearchmessagesettings.cpp
)

if(HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT)
    target_sources(
        KF6TextAutoGenerateText
        PRIVATE
            core/texttospeech/textautogeneratetexttospeechenqueueinfo.h
            core/texttospeech/textautogeneratetexttospeechenqueueinfo.cpp
            core/texttospeech/textautogeneratetexttospeechenqueuemanager.h
            core/texttospeech/textautogeneratetexttospeechenqueuemanager.cpp
    )
endif()

target_sources(
    KF6TextAutoGenerateText
    PRIVATE
        widgets/textautogeneratestackwidget.h
        widgets/textautogeneratestackwidget.cpp
        widgets/textautogeneratehistorywidget.h
        widgets/textautogeneratehistorywidget.cpp
        widgets/textautogenerateheaderwidget.h
        widgets/textautogenerateheaderwidget.cpp
        widgets/textautogeneratesearchwidget.h
        widgets/textautogeneratesearchwidget.cpp
        widgets/textautogeneratesearchdialog.h
        widgets/textautogeneratesearchdialog.cpp
        widgets/textautogeneratesearchlineedit.h
        widgets/textautogeneratesearchlineedit.cpp
        widgets/textautogeneratewidget.h
        widgets/textautogeneratewidget.cpp
        widgets/textautogeneratedialog.h
        widgets/textautogeneratedialog.cpp
        widgets/common/textautogeneratetextmodelcombobox.cpp
        widgets/configure/textautogeneratetextconfigurepromptwidget.h
        widgets/configure/textautogeneratetextconfigurepromptwidget.cpp
        widgets/configure/textautogeneratetextconfigurepluginswidget.h
        widgets/configure/textautogeneratetextconfigurepluginswidget.cpp
        widgets/configure/textautogeneratetextconfigurepluginstreewidgetdelegate.cpp
        widgets/configure/textautogeneratetextconfigurepluginstreewidgetdelegate.h
        widgets/common/textautogeneratetextmodelcombobox.h
        widgets/common/textautogeneratetextmodelcombobox.cpp
        widgets/common/textautogeneratetextlineeditwidget.h
        widgets/common/textautogeneratetextlineeditwidget.cpp
        widgets/common/textautogenerateresultwidget.h
        widgets/common/textautogenerateresultwidget.cpp
        widgets/common/textautogeneratetextlineedit.h
        widgets/common/textautogeneratetextlineedit.cpp
        widgets/common/textautogeneratenotworkingwidget.h
        widgets/common/textautogeneratenotworkingwidget.cpp
        widgets/common/textautogeneratenotworkingmessagewidget.h
        widgets/common/textautogeneratenotworkingmessagewidget.cpp
        widgets/common/textautogeneratenotinstancefoundwidget.h
        widgets/common/textautogeneratenotinstancefoundwidget.cpp
        widgets/common/textautogeneratemodelsearchlineedit.cpp
        widgets/common/textautogeneratemodelsearchlineedit.h
        widgets/common/textautogenerateflowlayout.cpp
        widgets/common/textautogenerateflowlayout.h
        widgets/common/textautogeneratetextlineeditattachmentwidget.h
        widgets/common/textautogeneratetextlineeditattachmentwidget.cpp
        widgets/common/textautogeneratetextlineeditattachmentclickablewidget.h
        widgets/common/textautogeneratetextlineeditattachmentclickablewidget.cpp
        widgets/view/textautogeneratelistview.h
        widgets/view/textautogeneratelistview.cpp
        widgets/view/textautogeneratedelegateutils.h
        widgets/view/textautogeneratedelegateutils.cpp
        widgets/view/textautogenerateselectedmessagebackgroundanimation.h
        widgets/view/textautogenerateselectedmessagebackgroundanimation.cpp
        widgets/view/textautogeneratemessagewaitingansweranimation.h
        widgets/view/textautogeneratemessagewaitingansweranimation.cpp
        widgets/view/textautogeneratemessagewaitingansweranimationbase.cpp
        widgets/view/textautogeneratemessagewaitingansweranimationbase.h
        widgets/view/textautogeneratechatwaitingansweranimation.h
        widgets/view/textautogeneratechatwaitingansweranimation.cpp
        widgets/view/textautogeneratebaselistview.h
        widgets/view/textautogeneratebaselistview.cpp
        widgets/view/textautogeneratesearchlistview.h
        widgets/view/textautogeneratesearchlistview.cpp
        widgets/view/textautogeneratehistorylistview.h
        widgets/view/textautogeneratehistorylistview.cpp
        widgets/view/textautogeneratelistviewtextselection.h
        widgets/view/textautogeneratelistviewtextselection.cpp
        widgets/view/delegate/textautogeneratehistorylistviewdelegate.h
        widgets/view/delegate/textautogeneratehistorylistviewdelegate.cpp
        widgets/view/delegate/textautogeneratelistviewdelegate.h
        widgets/view/delegate/textautogeneratelistviewdelegate.cpp
        widgets/view/delegate/textautogeneratelistviewbasedelegate.cpp
        widgets/view/delegate/textautogeneratelistviewbasedelegate.h
        widgets/view/delegate/textautogeneratesearchlistviewdelegate.h
        widgets/view/delegate/textautogeneratesearchlistviewdelegate.cpp
        widgets/view/delegate/textautogenerateattachmentdelegatehelperimage.h
        widgets/view/delegate/textautogenerateattachmentdelegatehelperimage.cpp
        widgets/view/delegate/textautogenerateattachmentdelegatehelperbase.h
        widgets/view/delegate/textautogenerateattachmentdelegatehelperbase.cpp
        widgets/view/delegate/textautogenerateattachmentdelegatehelperfile.cpp
        widgets/view/delegate/textautogenerateattachmentdelegatehelperfile.h
        widgets/view/lrucache.h
        widgets/menu/textautogeneratemenuconfiguredialog.cpp
        widgets/menu/textautogeneratemenuconfiguredialog.h
        widgets/menu/textautogeneratemenuconfigurewidget.cpp
        widgets/menu/textautogeneratemenuconfigurewidget.h
        widgets/menu/textautogeneratemenulistview.cpp
        widgets/menu/textautogeneratemenulistview.h
        widgets/menu/textautogeneratemenulistviewdelegate.cpp
        widgets/menu/textautogeneratemenulistviewdelegate.h
        widgets/menu/textautogeneratemenumodel.cpp
        widgets/menu/textautogeneratemenumodel.h
        widgets/menu/textautogeneratemenutextinfo.cpp
        widgets/menu/textautogeneratemenutextinfo.h
        widgets/menu/textautogeneratemenutextmanager.cpp
        widgets/menu/textautogeneratemenutextmanager.h
        widgets/menu/textautogeneratemenuwidget.cpp
        widgets/menu/textautogeneratemenuwidget.h
        widgets/networkpluginconfigure/textautogeneratenetworkpluginconfigurewidget.h
        widgets/networkpluginconfigure/textautogeneratenetworkpluginconfigurewidget.cpp
        widgets/quickask/textautogeneratequickaskdialog.h
        widgets/quickask/textautogeneratequickaskdialog.cpp
        widgets/quickask/textautogeneratequickaskwidget.h
        widgets/quickask/textautogeneratequickaskwidget.cpp
        widgets/quickask/textautogeneratequickaskviewwidget.h
        widgets/quickask/textautogeneratequickaskviewwidget.cpp
        widgets/quickask/textautogeneratequickaskheaderwidget.h
        widgets/quickask/textautogeneratequickaskheaderwidget.cpp
        widgets/instancesmanager/textautogeneratetextinstancesmanagerwidget.h
        widgets/instancesmanager/textautogeneratetextinstancesmanagerwidget.cpp
        widgets/instancesmanager/textautogeneratetextinstancesmanagerlistview.h
        widgets/instancesmanager/textautogeneratetextinstancesmanagerlistview.cpp
        widgets/instancesmanager/textautogenerateaddinstancedialog.h
        widgets/instancesmanager/textautogenerateaddinstancedialog.cpp
        widgets/instancesmanager/textautogenerateaddinstancewidget.h
        widgets/instancesmanager/textautogenerateaddinstancewidget.cpp
        widgets/instancesmanager/textautogeneratetextinstancecombobox.h
        widgets/instancesmanager/textautogeneratetextinstancecombobox.cpp
        widgets/instancesmanager/textautogeneratetextinstancesmanagerlistviewdelegate.h
        widgets/instancesmanager/textautogeneratetextinstancesmanagerlistviewdelegate.cpp
        widgets/instancesmanager/textautogeneratetextinstancesmanagerdialog.h
        widgets/instancesmanager/textautogeneratetextinstancesmanagerdialog.cpp
        widgets/plugintext/textautogenerateplugintext.h
        widgets/plugintext/textautogenerateplugintext.cpp
        widgets/plugintext/textautogenerateplugintextinterface.h
        widgets/plugintext/textautogenerateplugintextinterface.cpp
        widgets/plugintext/textautogenerateplugintextmanager.cpp
        widgets/plugintext/textautogenerateplugintextmanager.h
        widgets/configuretoolsplugin/textautogeneratetoolpluginconfigurewidget.h
        widgets/configuretoolsplugin/textautogeneratetoolpluginconfigurewidget.cpp
        widgets/configuretoolsplugin/textautogeneratetoolpluginshowmetadatadialog.h
        widgets/configuretoolsplugin/textautogeneratetoolpluginshowmetadatadialog.cpp
        widgets/configuretoolsplugin/textautogeneratetoolpluginshowmetadatawidget.h
        widgets/configuretoolsplugin/textautogeneratetoolpluginshowmetadatawidget.cpp
        widgets/toolswidget/textautogeneratetoolswidget.h
        widgets/toolswidget/textautogeneratetoolswidget.cpp
)

if(BUILD_TESTING)
    add_subdirectory(core/autotests)
    add_subdirectory(tests)
    add_subdirectory(widgets/menu/autotests)
    add_subdirectory(widgets/autotests)
endif()

add_subdirectory(plugins)
add_subdirectory(tools)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KF6TextAutoGenerateText
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(KF6TextAutoGenerateText BASE_NAME textautogeneratetext)

target_link_libraries(
    KF6TextAutoGenerateText
    PUBLIC
        Qt::Gui
        Qt::Widgets
        Qt::Network
        KF6::ConfigGui
        KF6::CoreAddons
        KF6::I18n
    PRIVATE
        Qt::Sql
        KF6::WidgetsAddons
        KF6::TextWidgets
        KF6::ColorScheme
        KF6::SyntaxHighlighting
        KF6::ItemViews
        KF6::IconThemes
        KF6::TextUtils
        KF6::TextAddonsWidgets
)

if(TARGET Qt6::TextToSpeech)
    target_link_libraries(KF6TextAutoGenerateText PRIVATE KF6::TextEditTextToSpeech)
endif()

if(NOT WIN32 AND NOT APPLE)
    target_link_libraries(KF6TextAutoGenerateText PRIVATE Qt::DBus)
endif()

target_include_directories(
    KF6TextAutoGenerateText
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateText/>"
)

set_target_properties(
    KF6TextAutoGenerateText
    PROPERTIES
        VERSION
            ${TEXTAUTOGENERATETEXT_VERSION}
        SOVERSION
            ${TEXTAUTOGENERATETEXT_SOVERSION}
        EXPORT_NAME
            TextAutoGenerateText
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextcore_HEADERS
    HEADER_NAMES
    TextAutoGenerateChatSettings
    TextAutoGenerateTextClient
    TextAutoGenerateTextPlugin
    TextAutoGenerateManager
    TextAutoGenerateMessage
    TextAutoGenerateAnswerInfo
    TextAutoGenerateAttachment
    TextAutoGenerateAttachments
    TextAutoGenerateChat
    TextAutoGenerateTextReplyInfo
    TextAutoGenerateSearchMessage
    TextAutoGenerateReply
    TextAutoGenerateTextRequest
    TextAutoGenerateManagerBase
    TextAutoGenerateTextInstance
    TextAutoGenerateTextInstancesManager
    TextAutoGenerateMessageUtils
    TextAutoGenerateTextUtils
    TextAutoGeneratePluginUtils
    TextAutoGenerateSettings
    TextAutoGenerateAttachmentUtils
    TextAutoGenerateSearchMessageSettings
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextcore_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE core
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetexttoolscore_HEADERS
    HEADER_NAMES
    TextAutoGenerateTextToolPlugin
    TextAutoGenerateTextToolPluginProperty
    TextAutoGenerateTextToolPluginManager
    TextAutoGenerateTextToolPluginJob
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetexttoolscore_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE core/tools
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextcoremodels_HEADERS
    HEADER_NAMES
    TextAutoGenerateHistorySortFilterProxyModel
    TextAutoGenerateMessagesModel
    TextAutoGenerateSearchMessagesModel
    TextAutoGenerateChatsModel
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextcoremodels_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE core/models
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextcorejobs_HEADERS
    HEADER_NAMES
    TextAutoGenerateExportChatAsJsonJob
    TextAutoGenerateAskJob
    TextAutoGenerateExportChatBaseJob
    TextAutoGenerateImportChatBaseJob
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextcorejobs_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE core/jobs
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextwidgets_HEADERS
    HEADER_NAMES
    TextAutoGenerateWidget
    TextAutoGenerateDialog
    TextAutoGenerateStackWidget
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextwidgets_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE widgets
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextconfigurewidgets_HEADERS
    HEADER_NAMES
    TextAutoGenerateTextConfigurePluginsWidget
    TextAutoGenerateTextConfigurePromptWidget
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextconfigurewidgets_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE widgets/configure
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextnetworkpluginconfigure_HEADERS
    HEADER_NAMES
    TextAutoGenerateNetworkPluginConfigureWidget
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextnetworkpluginconfigure_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE widgets/networkpluginconfigure
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextwidgetsmenu_HEADERS
    HEADER_NAMES
    TextAutoGenerateMenuWidget
    TextAutoGenerateMenuConfigureDialog
    TextAutoGenerateMenuTextInfo
    TextAutoGenerateMenuConfigureWidget
    TextAutoGenerateMenuTextManager
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextwidgetsmenu_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE widgets/menu
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextwidgetsquickask_HEADERS
    HEADER_NAMES
    TextAutoGenerateQuickAskDialog
    TextAutoGenerateQuickAskWidget
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextwidgetsquickask_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE widgets/quickask
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextwidgetsinstancesmanager_HEADERS
    HEADER_NAMES
    TextAutoGenerateTextInstancesManagerWidget
    TextAutoGenerateTextInstancesManagerDialog
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextwidgetsinstancesmanager_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE widgets/instancesmanager
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextplugintext_HEADERS
    HEADER_NAMES
    TextAutoGeneratePluginText
    TextAutoGeneratePluginTextInterface
    TextAutoGeneratePluginTextManager
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextplugintext_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE widgets/plugintext
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextconfiguretoolsplugin_HEADERS
    HEADER_NAMES
    TextAutoGenerateToolPluginConfigureWidget
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextconfiguretoolsplugin_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE widgets/configuretoolsplugin
)

install(TARGETS KF6TextAutoGenerateText EXPORT KF6TextAutoGenerateTextTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetext_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateText/
    COMPONENT Devel
)

install(
    FILES
        ${TextAutoGenerateText_Camelcasestextautogeneratetextcore_HEADERS}
        ${TextAutoGenerateText_Camelcasestextautogeneratetextwidgets_HEADERS}
        ${TextAutoGenerateText_Camelcasestextautogeneratetextwidgetsmenu_HEADERS}
        ${TextAutoGenerateText_Camelcasestextautogeneratetextnetworkpluginconfigure_HEADERS}
        ${TextAutoGenerateText_Camelcasestextautogeneratetextwidgetsquickask_HEADERS}
        ${TextAutoGenerateText_Camelcasestextautogeneratetextcoremodels_HEADERS}
        ${TextAutoGenerateText_Camelcasestextautogeneratetextwidgetsinstancesmanager_HEADERS}
        ${TextAutoGenerateText_Camelcasestextautogeneratetextcorejobs_HEADERS}
        ${TextAutoGenerateText_Camelcasestextautogeneratetextplugintext_HEADERS}
        ${TextAutoGenerateText_Camelcasestextautogeneratetextconfigurewidgets_HEADERS}
        ${TextAutoGenerateText_Camelcasestextautogeneratetexttoolscore_HEADERS}
        ${TextAutoGenerateText_Camelcasestextautogeneratetextconfiguretoolsplugin_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateText/TextAutoGenerateText
    COMPONENT Devel
)

set(TextAutoGenerateTextIncludeFiles
    ${TextAutoGenerateText_textautogeneratetextcore_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextwidgets_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextwidgetsmenu_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextnetworkpluginconfigure_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextwidgetsquickask_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextcoremodels_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextwidgetsinstancesmanager_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextcorejobs_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextplugintext_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextconfigurewidgets_HEADERS}
    ${TextAutoGenerateText_textautogeneratetexttoolscore_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextconfiguretoolsplugin_HEADERS}
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetext_export.h
        ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextglobalconfig.h
        ${CMAKE_CURRENT_BINARY_DIR}/config-textautogeneratetext.h
        ${TextAutoGenerateTextIncludeFiles}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateText/textautogeneratetext
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KF6TextAutoGenerateText_QCH
        NAME KF6TextAutoGenerateText
        BASE_NAME KF6TextAutoGenerateText
        VERSION ${TEXTAUTOGENERATETEXT_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextAutoGenerateTextIncludeFiles}
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTAUTOGENERATETEXT_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF6TextAutoGenerateText_QCH
        FILE KF6TextAutoGenerateTextQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF6TextAutoGenerateTextQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextAutoGenerateTextConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)
