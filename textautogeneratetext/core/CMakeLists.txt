# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextAutoGenerateTextCore")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOGENERATETEXTCORE
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextcore_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextCoreConfigVersion.cmake"
    SOVERSION 1
)

add_library(KF6TextAutoGenerateTextCore)
add_library(KF6::TextAutoGenerateTextCore ALIAS KF6TextAutoGenerateTextCore)

# precompiled headers support
if(ENABLE_PCH)
    target_precompile_headers(
        KF6TextAutoGenerateTextCore
        PRIVATE
            <QObject>
            <QDebug>
            <QJsonObject>
            <QStringList>
            <QString>
    )
endif()

ecm_qt_declare_logging_category(KF6TextAutoGenerateTextCore HEADER textautogeneratetextcore_database_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext.database
    DESCRIPTION "KF6 (TextAutoGenerateText core database)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextAutoGenerateTextCore HEADER textautogeneratetextcore_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_CORE_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext
    DESCRIPTION "KF6 (TextAutoGenerateText core)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextAutoGenerateTextCore HEADER textautogeneratetextcore_memory_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext.memory
    DESCRIPTION "KF6 (TextAutoGenerateText core memory)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextAutoGenerateTextCore HEADER textautogeneratetextcore_cmark_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_CORE_CMARK_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext.core.cmark
    DESCRIPTION "KF6 (TextAutoGenerateText core cmark)"
    EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextAutoGenerateTextCore HEADER textautogeneratetextcore_toolplugin_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_CORE_TOOL_PLUGIN_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext.core.tool.plugin
    DESCRIPTION "KF6 (TextAutoGenerateText core tool plugin)"
    EXPORT KTEXTADDONS
)

set(textautogeneratetext_dbs_adaptor_SRCS)
if(NOT WIN32 AND NOT APPLE)
    qt_add_dbus_adaptor(textautogeneratetext_dbs_adaptor_SRCS org.kde.textautogeneratetext.TextAutoGenerateManager.xml textautogeneratemanager.h TextAutoGenerateText::TextAutoGenerateManager)
endif()

kconfig_add_kcfg_files(KF6TextAutoGenerateTextCore
    settings/textautogeneratetextglobalconfig.kcfgc
)
install(
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/settings/textautogeneratetextglobalconfig.kcfg
    DESTINATION ${KDE_INSTALL_KCFGDIR}
)

target_sources(
    KF6TextAutoGenerateTextCore
    PRIVATE
        ${textautogeneratetext_dbs_adaptor_SRCS}
        textautogeneratetextutils.h
        textautogeneratetextutils.cpp
        textautogenerateengineloader.cpp
        textautogenerateengineloader.h
        textautogeneratetextclient.h
        textautogeneratetextclient.cpp
        textautogeneratetextplugin.h
        textautogeneratetextplugin.cpp
        textautogeneratemanager.h
        textautogeneratemanager.cpp
        textautogenerateengineaccessmanager.cpp
        textautogenerateengineaccessmanager.h
        textautogeneratechatsettings.h
        textautogeneratechatsettings.cpp
        textautogeneratetextreplyinfo.h
        textautogeneratetextreplyinfo.cpp
        textautogeneratesearchmessage.h
        textautogeneratesearchmessage.cpp
        textautogeneratemessage.h
        textautogeneratemessage.cpp
        textautogenerateanswerinfo.h
        textautogenerateanswerinfo.cpp
        textautogenerateattachment.h
        textautogenerateattachment.cpp
        textautogenerateattachments.h
        textautogenerateattachments.cpp
        textautogeneratemessageutils.h
        textautogeneratemessageutils.cpp
        textautogeneratechat.h
        textautogeneratechat.cpp
        textautogeneratesettings.h
        textautogeneratesettings.cpp
        textautogenerateattachmentutils.h
        textautogenerateattachmentutils.cpp
        textautogenerateblockcmarksupport.h
        textautogenerateblockcmarksupport.cpp
        textautogenerateagentprompskillmanager.h
        textautogenerateagentprompskillmanager.cpp
        models/textautogeneratemessagesmodel.h
        models/textautogeneratemessagesmodel.cpp
        models/textautogeneratesearchmessagesmodel.h
        models/textautogeneratesearchmessagesmodel.cpp
        models/textautogeneratehistorysortfilterproxymodel.h
        models/textautogeneratehistorysortfilterproxymodel.cpp
        models/textautogeneratehistorylistheadingsproxymodel.cpp
        models/textautogeneratehistorylistheadingsproxymodel.h
        models/textautogeneratechatsmodel.h
        models/textautogeneratechatsmodel.cpp
        models/textautogeneratetextinstancemodel.h
        models/textautogeneratetextinstancemodel.cpp
        models/textautogeneratetextinstancesortfilterproxymodel.h
        models/textautogeneratetextinstancesortfilterproxymodel.cpp
        models/textautogeneratetextpromptmodel.cpp
        models/textautogeneratetextpromptmodel.h
        models/textautogeneratetextskillmodel.cpp
        models/textautogeneratetextskillmodel.h
        models/textautogeneratetextagentmodel.cpp
        models/textautogeneratetextagentmodel.h
        models/textautogeneratetextpromptsortfilterproxymodel.cpp
        models/textautogeneratetextpromptsortfilterproxymodel.h
        models/textautogeneratetagsmodel.cpp
        models/textautogeneratetagsmodel.h
        models/textautogenerateprojectsmodel.cpp
        models/textautogenerateprojectsmodel.h
        localdatabase/textautogeneratelocaldatabaseutils.h
        localdatabase/textautogeneratelocaldatabaseutils.cpp
        localdatabase/textautogeneratelocaldatabaseabstract.h
        localdatabase/textautogeneratelocaldatabaseabstract.cpp
        localdatabase/textautogeneratelocalchatsdatabase.h
        localdatabase/textautogeneratelocalchatsdatabase.cpp
        localdatabase/textautogeneratelocalmessagesdatabase.cpp
        localdatabase/textautogeneratelocalmessagesdatabase.h
        localdatabase/textautogeneratelocaldatabasemanager.h
        localdatabase/textautogeneratelocaldatabasemanager.cpp
        localdatabase/textautogeneratelocalchatpendingtypedinfodatabase.cpp
        localdatabase/textautogeneratelocalchatpendingtypedinfodatabase.h
        localdatabase/textautogeneratelocaltagsdatabase.cpp
        localdatabase/textautogeneratelocaltagsdatabase.h
        localdatabase/textautogeneratelocalprojectsdatabase.cpp
        localdatabase/textautogeneratelocalprojectsdatabase.h
        textautogeneratesearchmessageutils.h
        textautogeneratesearchmessageutils.cpp
        textautogeneratereply.h
        textautogeneratereply.cpp
        textautogeneratetextrequest.cpp
        textautogeneratetextrequest.h
        textautogeneratemanagerbase.h
        textautogeneratemanagerbase.cpp
        textautogeneratetextinstance.h
        textautogeneratetextinstance.cpp
        textautogeneratetextinstancesmanager.h
        textautogeneratetextinstancesmanager.cpp
        jobs/textautogenerateexportchatbasejob.cpp
        jobs/textautogenerateexportchatbasejob.h
        jobs/textautogenerateexportchatasjsonjob.cpp
        jobs/textautogenerateexportchatasjsonjob.h
        jobs/textautogeneratesearchjob.h
        jobs/textautogeneratesearchjob.cpp
        jobs/textautogenerateaskjob.h
        jobs/textautogenerateaskjob.cpp
        jobs/textautogenerateimportchatbasejob.cpp
        jobs/textautogenerateimportchatbasejob.h
        jobs/textautogenerateimportchatasjsonjob.h
        jobs/textautogenerateimportchatasjsonjob.cpp
        jobs/textautogeneratepurgeexpiredchatsjob.h
        jobs/textautogeneratepurgeexpiredchatsjob.cpp
        mcp/textautogeneratemcpsamplingjob.h
        mcp/textautogeneratemcpsamplingjob.cpp
        mcp/textautogeneratemcptoolcalljob.h
        mcp/textautogeneratemcptoolcalljob.cpp
        mcp/textautogeneratemcptoolsmanager.h
        mcp/textautogeneratemcptoolsmanager.cpp
        mcp/textautogeneratemcptoolsutils.h
        mcp/textautogeneratemcptoolsutils.cpp
        tools/textautogeneratetexttoolplugin.h
        tools/textautogeneratetexttoolplugin.cpp
        tools/textautogeneratetexttoolpluginmanager.cpp
        tools/textautogeneratetexttoolpluginmanager.h
        tools/textautogeneratetexttoolpluginproperty.h
        tools/textautogeneratetexttoolpluginproperty.cpp
        tools/textautogeneratetexttoolpluginjob.h
        tools/textautogeneratetexttoolpluginjob.cpp
        tools/textautogeneratetexttoolsloadingjob.h
        tools/textautogeneratetexttoolsloadingjob.cpp
        tools/textautogeneratetexttoolinternalproperty.h
        tools/textautogeneratetexttoolinternalproperty.cpp
        tools/textautogeneratetexttoolinternalinterface.h
        tools/textautogeneratetexttoolinternalinterface.cpp
        tools/textautogeneratetexttoolinternal.h
        tools/textautogeneratetexttoolinternal.cpp
        tools/textautogeneratetexttoolbasejob.h
        tools/textautogeneratetexttoolbasejob.cpp
        tools/textautogeneratetexttoolinternaljob.h
        tools/textautogeneratetexttoolinternaljob.cpp
        tools/textautogeneratetoolcalljob.h
        tools/textautogeneratetoolcalljob.cpp
        textautogeneratesearchmessagesettings.h
        textautogeneratesearchmessagesettings.cpp
        textautogeneratefilecache.h
        textautogeneratefilecache.cpp
        icons/icons.qrc
        prompts/textautogenerateskill.h
        prompts/textautogenerateskill.cpp
        prompts/textautogenerateprompt.h
        prompts/textautogenerateprompt.cpp
        prompts/textautogenerateagent.cpp
        prompts/textautogenerateagent.h
        tags/textautogeneratetag.h
        tags/textautogeneratetag.cpp
        projects/textautogenerateproject.h
        projects/textautogenerateproject.cpp
        textautogeneratetagsmanager.h
        textautogeneratetagsmanager.cpp
        textautogenerateprojectsmanager.h
        textautogenerateprojectsmanager.cpp
)

if(HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT)
    target_sources(
        KF6TextAutoGenerateTextCore
        PRIVATE
            texttospeech/textautogeneratetexttospeechenqueueinfo.h
            texttospeech/textautogeneratetexttospeechenqueueinfo.cpp
            texttospeech/textautogeneratetexttospeechenqueuemanager.h
            texttospeech/textautogeneratetexttospeechenqueuemanager.cpp
    )
endif()

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KF6TextAutoGenerateTextCore
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()

ecm_generate_export_header(KF6TextAutoGenerateTextCore
    BASE_NAME textautogeneratetextcore
    VERSION ${TEXTAUTOGENERATETEXTCORE_VERSION}
    USE_VERSION_HEADER
)

target_link_libraries(
    KF6TextAutoGenerateTextCore
    PUBLIC
        Qt::Gui
        Qt::Network
        Qt::Sql
        KF6::ConfigGui
        KF6::CoreAddons
        KF6::I18n
        KF6::TextAddonsCore
        KF6::TextAutoGenerateTextMcpProtocolCore
    PRIVATE
        KF6::ColorScheme
        KF6::SyntaxHighlighting
        KF6::TextUtils
)

if(TARGET Qt6::TextToSpeech)
    target_link_libraries(KF6TextAutoGenerateTextCore PRIVATE KF6::TextEditTextToSpeech)
endif()

if(NOT WIN32 AND NOT APPLE)
    target_link_libraries(KF6TextAutoGenerateTextCore PRIVATE Qt::DBus)
endif()

target_include_directories(
    KF6TextAutoGenerateTextCore
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/..>"
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextCore/>"
)

set_target_properties(
    KF6TextAutoGenerateTextCore
    PROPERTIES
        VERSION
            ${TEXTAUTOGENERATETEXTCORE_VERSION}
        SOVERSION
            ${TEXTAUTOGENERATETEXTCORE_SOVERSION}
        EXPORT_NAME
            TextAutoGenerateTextCore
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
    TextAutoGenerateSettings
    TextAutoGenerateAttachmentUtils
    TextAutoGenerateSearchMessageSettings
    TextAutoGenerateAgentPrompSkillManager
    TextAutoGenerateProjectsManager
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextcore_HEADERS
    PREFIX TextAutoGenerateText
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetexttoolscore_HEADERS
    HEADER_NAMES
    TextAutoGenerateTextToolPlugin
    TextAutoGenerateTextToolPluginProperty
    TextAutoGenerateTextToolPluginManager
    TextAutoGenerateTextToolPluginJob
    TextAutoGenerateTextToolsLoadingJob
    TextAutoGenerateTextToolInternalProperty
    TextAutoGenerateTextToolInternalInterface
    TextAutoGenerateTextToolInternal
    TextAutoGenerateTextToolBaseJob
    TextAutoGenerateTextToolInternalJob
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetexttoolscore_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE tools
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextcoremcp_HEADERS
    HEADER_NAMES
    TextAutoGenerateMcpToolsManager
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextcoremcp_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE mcp
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextcoremodels_HEADERS
    HEADER_NAMES
    TextAutoGenerateHistorySortFilterProxyModel
    TextAutoGenerateMessagesModel
    TextAutoGenerateSearchMessagesModel
    TextAutoGenerateChatsModel
    TextAutoGenerateTextPromptModel
    TextAutoGenerateTextSkillModel
    TextAutoGenerateTextAgentModel
    TextAutoGenerateTextPromptSortFilterProxyModel
    TextAutoGenerateTagsModel
    TextAutoGenerateProjectsModel
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextcoremodels_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE models
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextcorelocaldatabase_HEADERS
    HEADER_NAMES
    TextAutoGenerateLocalChatPendingTypedInfoDatabase
    TextAutoGenerateLocalChatsDatabase
    TextAutoGenerateLocalTagsDatabase
    TextAutoGenerateLocalProjectsDatabase
    TextAutoGenerateLocalMessagesDatabase
    TextAutoGenerateLocalDatabaseManager
    TextAutoGenerateLocalDatabaseAbstract
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextcorelocaldatabase_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE localdatabase
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextcoreprompts_HEADERS
    HEADER_NAMES
    TextAutoGenerateSkill
    TextAutoGeneratePrompt
    TextAutoGenerateAgent
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextcoreprompts_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE prompts
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextcoretags_HEADERS
    HEADER_NAMES
    TextAutoGenerateTag
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextcoretags_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE tags
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextcoreprojects_HEADERS
    HEADER_NAMES
    TextAutoGenerateProject
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextcoreprojects_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE projects
)

ecm_generate_headers(TextAutoGenerateText_Camelcasestextautogeneratetextcorejobs_HEADERS
    HEADER_NAMES
    TextAutoGenerateExportChatAsJsonJob
    TextAutoGenerateAskJob
    TextAutoGenerateExportChatBaseJob
    TextAutoGenerateImportChatBaseJob
    TextAutoGenerateImportChatAsJsonJob
    REQUIRED_HEADERS TextAutoGenerateText_textautogeneratetextcorejobs_HEADERS
    PREFIX TextAutoGenerateText
    RELATIVE jobs
)

install(
    TARGETS
        KF6TextAutoGenerateTextCore
    EXPORT KF6TextAutoGenerateTextCoreTargets
    ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextcore_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextCore/
    COMPONENT Devel
)

set(TextAutoGenerateTextCoreCamelCaseIncludeFiles
    ${TextAutoGenerateText_Camelcasestextautogeneratetextcore_HEADERS}
    ${TextAutoGenerateText_Camelcasestextautogeneratetexttoolscore_HEADERS}
    ${TextAutoGenerateText_Camelcasestextautogeneratetextcoremcp_HEADERS}
    ${TextAutoGenerateText_Camelcasestextautogeneratetextcoremodels_HEADERS}
    ${TextAutoGenerateText_Camelcasestextautogeneratetextcorelocaldatabase_HEADERS}
    ${TextAutoGenerateText_Camelcasestextautogeneratetextcoreprompts_HEADERS}
    ${TextAutoGenerateText_Camelcasestextautogeneratetextcoretags_HEADERS}
    ${TextAutoGenerateText_Camelcasestextautogeneratetextcoreprojects_HEADERS}
    ${TextAutoGenerateText_Camelcasestextautogeneratetextcorejobs_HEADERS}
)

install(
    FILES
        ${TextAutoGenerateTextCoreCamelCaseIncludeFiles}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextCore/TextAutoGenerateText
    COMPONENT Devel
)

set(TextAutoGenerateTextCoreIncludeFiles
    ${TextAutoGenerateText_textautogeneratetextcore_HEADERS}
    ${TextAutoGenerateText_textautogeneratetexttoolscore_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextcoremcp_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextcoremodels_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextcorelocaldatabase_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextcoreprompts_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextcoretags_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextcoreprojects_HEADERS}
    ${TextAutoGenerateText_textautogeneratetextcorejobs_HEADERS}
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextcore_export.h
        ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextglobalconfig.h
        ${CMAKE_CURRENT_BINARY_DIR}/../config-textautogeneratetext.h
        ${TextAutoGenerateTextCoreIncludeFiles}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextCore/textautogeneratetext
    COMPONENT Devel
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextCoreConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextCoreConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KF6TextAutoGenerateTextCoreTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextAutoGenerateTextCoreTargets.cmake
    NAMESPACE KF6::
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextAutoGenerateTextCoreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextCoreConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

ecm_add_installed_library_check(KF6TextAutoGenerateTextCore
    PACKAGE_NAME "KF6TextAutoGenerateTextCore"
    PACKAGE_VERSION ${TEXTAUTOGENERATETEXTCORE_VERSION}
    PACKAGE_TARGET_NAMESPACE "KF6::"
)

ecm_installed_library_check_include_strings(KF6TextAutoGenerateTextCore
    HEADERS ${TextAutoGenerateTextCoreIncludeFiles}
    PREFIX textautogeneratetext
)

ecm_installed_library_check_include_strings(KF6TextAutoGenerateTextCore
    HEADERS
    ${TextAutoGenerateTextCoreCamelCaseIncludeFiles}
    PREFIX TextAutoGenerateText
)

ecm_generate_qdoc(KF6TextAutoGenerateTextCore textautogeneratetextcore.qdocconf)
