# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

add_library(KF6TextAutoGenerateTextMcpProtocolCore)

add_library(KF6::TextAutoGenerateTextMcpProtocolCore ALIAS KF6TextAutoGenerateTextMcpProtocolCore)

ecm_qt_declare_logging_category(KF6TextAutoGenerateTextMcpProtocolCore HEADER textautogeneratetextmcpprotocol_core_debug.h
    IDENTIFIER TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetextmcpprotocolcore
    DESCRIPTION "KF6 (TextAutoGenerateText core MCP protocols)"
    EXPORT KTEXTADDONS
)

target_sources(
    KF6TextAutoGenerateTextMcpProtocolCore
    PRIVATE
        mcpprotocolimagecontent.h
        mcpprotocolimagecontent.cpp
        mcpprotocoltextcontent.cpp
        mcpprotocoltask.cpp
        mcpprotocolroot.cpp
        mcpprotocolimplementation.cpp
        mcpprotocolresourcetemplatereference.cpp
        mcpprotocolpromptargument.cpp
        mcpprotocolbasemetadata.cpp
        mcpprotocolbooleanschema.cpp
        mcpprotocolelicitationcompletenotification.cpp
        mcpprotocolresourcelink.cpp
        mcpprotocolinitializednotification.cpp
        mcpprotocollistpromptsresult.cpp
        mcpprotocoltaskstatusnotificationparams.cpp
        mcpprotocolcanceltaskrequest.cpp
        mcpprotocolcalltoolrequest.cpp
        mcpprotocolcalltoolrequestparams.cpp
        mcpprotocolgetpromptrequestparams.cpp
        mcpprotocolgettaskpayloadrequest.cpp
        mcpprotocolgettaskrequest.cpp
        mcpprotocolunsubscriberequestparams.cpp
        mcpprotocolresourcetemplate.cpp
        mcpprotocoltoollistchangednotification.cpp
        mcpprotocolresourcelistchangednotification.cpp
        mcpprotocolresourceupdatednotification.cpp
        mcpprotocoljsonrpcerrorresponse.cpp
        mcpprotocolpaginatedrequestparams.cpp
        mcpprotocolrequestparams.cpp
        mcpprotocolinitializerequestparams.cpp
        mcpprotocolsetlevelrequestparams.cpp
        mcpprotocolcompleterequestparams.cpp
        mcpprotocolreadresourcerequestparams.cpp
        mcpprotocolsubscriberequestparams.cpp
        mcpprotocolpromptreference.cpp
        mcpprotocolprogressnotificationparams.cpp
        mcpprotocolembeddedresource.cpp
        mcpprotocoltextresourcecontents.cpp
        mcpprotocollegacytitledenumschema.cpp
        mcpprotocolcreatetaskresult.cpp
        mcpprotocolblobresourcecontents.cpp
        mcpprotocolgetpromptresult.cpp
        mcpprotocolresourceupdatednotificationparams.cpp
        mcpprotocolpromptlistchangednotification.cpp
        mcpprotocolpaginatedresult.cpp
        mcpprotocolgetpromptrequest.cpp
        mcpprotocolreadresourcerequest.cpp
        mcpprotocolpingrequest.cpp
        mcpprotocollisttoolsrequest.cpp
        mcpprotocollistresourcetemplatesrequest.cpp
        mcpprotocolinitializerequest.cpp
        mcpprotocollisttasksrequest.cpp
        mcpprotocollistpromptsrequest.cpp
        mcpprotocolsetlevelrequest.cpp
        mcpprotocolsubscriberequest.cpp
        mcpprotocolunsubscriberequest.cpp
        mcpprotocolcompleterequest.cpp
        mcpprotocollistresourcesrequest.cpp
        mcpprotocoltaskstatusnotification.cpp
        mcpprotocolprogressnotification.cpp
        mcpprotocolresult.cpp
        mcpprotocollistresourcetemplatesresult.cpp
        mcpprotocollistresourcesresult.cpp
        mcpprotocolprompt.cpp
        mcpprotocolresource.cpp
        mcpprotocolrootslistchangednotification.cpp
        mcpprotocolnotificationparams.cpp
        mcpprotocolcancellednotification.cpp
        mcpprotocolcancellednotificationparams.cpp
        mcpprotocolloggingmessagenotification.cpp
        mcpprotocolmeta.cpp
        mcpprotocoluntitledsingleselectenumschema.cpp
        mcpprotocoltaskmetadata.cpp
        mcpprotocolstringschema.cpp
        mcpprotocolnumberschema.cpp
        mcpprotocolrelatedtaskmetadata.cpp
        mcpprotocolmodelpreferences.cpp
        mcpprotocoltoolchoice.cpp
        mcpprotocolerror.cpp
        mcpprotocoltoolchoice.h
        mcpprotocolerror.h
        mcpprotocolloggingmessagenotificationparams.cpp
        mcpprotocolloggingmessagenotificationparams.h
        mcpprotocoltoolexecution.cpp
        mcpprotocoltoolexecution.h
        mcpprotocoltoolusecontent.cpp
        mcpprotocoltoolresultcontent.cpp
        mcpprotocoltextcontent.h
        mcpprotocoltask.h
        mcpprotocolroot.h
        mcpprotocolimplementation.h
        mcpprotocolresourcetemplatereference.h
        mcpprotocolpromptargument.h
        mcpprotocolbasemetadata.h
        mcpprotocolbooleanschema.h
        mcpprotocolelicitationcompletenotification.h
        mcpprotocolresourcelink.h
        mcpprotocolinitializednotification.h
        mcpprotocollistpromptsresult.h
        mcpprotocoltaskstatusnotificationparams.h
        mcpprotocolcanceltaskrequest.h
        mcpprotocolcalltoolrequest.h
        mcpprotocolcalltoolrequestparams.h
        mcpprotocolgetpromptrequestparams.h
        mcpprotocolgettaskpayloadrequest.h
        mcpprotocolgettaskrequest.h
        mcpprotocolunsubscriberequestparams.h
        mcpprotocolresourcetemplate.h
        mcpprotocoltoollistchangednotification.h
        mcpprotocolresourcelistchangednotification.h
        mcpprotocolresourceupdatednotification.h
        mcpprotocoljsonrpcerrorresponse.h
        mcpprotocolpaginatedrequestparams.h
        mcpprotocolrequestparams.h
        mcpprotocolinitializerequestparams.h
        mcpprotocolsetlevelrequestparams.h
        mcpprotocolcompleterequestparams.h
        mcpprotocolreadresourcerequestparams.h
        mcpprotocolsubscriberequestparams.h
        mcpprotocolpromptreference.h
        mcpprotocolprogressnotificationparams.h
        mcpprotocolembeddedresource.h
        mcpprotocoltextresourcecontents.h
        mcpprotocollegacytitledenumschema.h
        mcpprotocolcreatetaskresult.h
        mcpprotocolblobresourcecontents.h
        mcpprotocolgetpromptresult.h
        mcpprotocolresourceupdatednotificationparams.h
        mcpprotocolpromptlistchangednotification.h
        mcpprotocolpaginatedresult.h
        mcpprotocolgetpromptrequest.h
        mcpprotocolreadresourcerequest.h
        mcpprotocolpingrequest.h
        mcpprotocollisttoolsrequest.h
        mcpprotocollistresourcetemplatesrequest.h
        mcpprotocolinitializerequest.h
        mcpprotocollisttasksrequest.h
        mcpprotocollistpromptsrequest.h
        mcpprotocolsetlevelrequest.h
        mcpprotocolsubscriberequest.h
        mcpprotocolunsubscriberequest.h
        mcpprotocolcompleterequest.h
        mcpprotocollistresourcesrequest.h
        mcpprotocoltaskstatusnotification.h
        mcpprotocolprogressnotification.h
        mcpprotocolresult.h
        mcpprotocollistresourcetemplatesresult.h
        mcpprotocollistresourcesresult.h
        mcpprotocolprompt.h
        mcpprotocolresource.h
        mcpprotocolrootslistchangednotification.h
        mcpprotocolnotificationparams.h
        mcpprotocolcancellednotification.h
        mcpprotocolcancellednotificationparams.h
        mcpprotocolloggingmessagenotification.h
        mcpprotocolmeta.h
        mcpprotocoluntitledsingleselectenumschema.h
        mcpprotocoltaskmetadata.h
        mcpprotocolstringschema.h
        mcpprotocolnumberschema.h
        mcpprotocolrelatedtaskmetadata.h
        mcpprotocolmodelpreferences.h
        mcpprotocoltoolannotations.cpp
        mcpprotocoltoolannotations.h
        mcpprotocoltoolusecontent.h
        mcpprotocoltoolresultcontent.h
        mcpprotocolaudiocontent.cpp
        mcpprotocolicon.cpp
        mcpprotocolicon.h
        mcpprotocolaudiocontent.h
        mcpprotocolannotations.cpp
        mcpprotocolannotations.h
        mcpprotocolutils.h
        mcpprotocolutils.cpp
        mcpprotocolmodelhint.cpp
        mcpprotocolclientcapabilities.cpp
        mcpprotocolpromptmessage.cpp
        mcpprotocolmodelhint.h
        mcpprotocolclientcapabilities.h
        mcpprotocolpromptmessage.h
        server/mcpprotocolserver.h
        server/mcpprotocolserver.cpp
        client/mcpprotocolclient.h
        client/mcpprotocolclient.cpp
        common/mcpprotocolplugin.h
        common/mcpprotocolplugin.cpp
        common/mcpprotocolplugininterface.h
        common/mcpprotocolplugininterface.cpp
        common/mcpprotocolsettings.h
        common/mcpprotocolsettings.cpp
        common/mcpbase.h
        common/mcpbase.cpp
)

generate_export_header(KF6TextAutoGenerateTextMcpProtocolCore BASE_NAME textautogeneratetextmcpprotocol)

ecm_generate_headers(TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolcommon_HEADERS
    HEADER_NAMES
    McpProtocolPlugin
    McpProtocolPluginInterface
    McpProtocolSettings
    REQUIRED_HEADERS TextAutoGenerateTextMcpProtocol_mcpprotocolcommon_HEADERS
    PREFIX TextAutoGenerateTextMcpProtocol
    RELATIVE common
)

ecm_generate_headers(TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolclient_HEADERS
    HEADER_NAMES
    McpProtocolClient
    REQUIRED_HEADERS TextAutoGenerateTextMcpProtocol_mcpprotocolclient_HEADERS
    PREFIX TextAutoGenerateTextMcpProtocol
    RELATIVE client
)

ecm_generate_headers(TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolserver_HEADERS
    HEADER_NAMES
    McpProtocolServer
    REQUIRED_HEADERS TextAutoGenerateTextMcpProtocol_mcpprotocolserver_HEADERS
    PREFIX TextAutoGenerateTextMcpProtocol
    RELATIVE server
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextmcpprotocol_export.h
        ${TextAutoGenerateTextMcpProtocol_mcpprotocolcommon_HEADERS}
        ${TextAutoGenerateTextMcpProtocol_mcpprotocolclient_HEADERS}
        ${TextAutoGenerateTextMcpProtocol_mcpprotocolserver_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextMcpProtocol/textautogeneratetextmcpprotocol
    COMPONENT Devel
)

install(
    FILES
        ${TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolcommon_HEADERS}
        ${TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolclient_HEADERS}
        ${TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolserver_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextMcpProtocol/TextAutoGenerateTextMcpProtocol
    COMPONENT Devel
)

target_link_libraries(
    KF6TextAutoGenerateTextMcpProtocolCore
    Qt::Core
    KF6::CoreAddons
)

install(
    TARGETS
        KF6TextAutoGenerateTextMcpProtocolCore
    EXPORT KF6TextAutoGenerateTextMcpProtocolCoreTargets
    ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)
if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

add_subdirectory(plugins)
