# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextAutoGenerateTextMcpProtocolCore")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOGENERATETEXTMCPPROTOCOLCORE
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextmcpprotocolcore_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextMcpProtocolCoreConfigVersion.cmake"
    SOVERSION 1
)

add_library(KF6TextAutoGenerateTextMcpProtocolCore)

add_library(KF6::TextAutoGenerateTextMcpProtocolCore ALIAS KF6TextAutoGenerateTextMcpProtocolCore)

ecm_qt_declare_logging_category(KF6TextAutoGenerateTextMcpProtocolCore HEADER textautogeneratetextmcpprotocol_core_debug.h
    IDENTIFIER TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetextmcpprotocolcore
    DESCRIPTION "KF6 (TextAutoGenerateText core MCP protocols)"
    EXPORT KTEXTADDONS
)

target_include_directories(
    KF6TextAutoGenerateTextMcpProtocolCore
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextMcpProtocolCore;>"
)

target_sources(
    KF6TextAutoGenerateTextMcpProtocolCore
    PRIVATE
        impl/mcpprotocolimagecontent.h
        impl/mcpprotocolimagecontent.cpp
        impl/mcpprotocoltextcontent.cpp
        impl/mcpprotocoltask.cpp
        impl/mcpprotocolroot.cpp
        impl/mcpprotocolimplementation.cpp
        impl/mcpprotocolresourcetemplatereference.cpp
        impl/mcpprotocolpromptargument.cpp
        impl/mcpprotocolbasemetadata.cpp
        impl/mcpprotocolbooleanschema.cpp
        impl/mcpprotocolelicitationcompletenotification.cpp
        impl/mcpprotocolresourcelink.cpp
        impl/mcpprotocolinitializednotification.cpp
        impl/mcpprotocollistpromptsresult.cpp
        impl/mcpprotocoltaskstatusnotificationparams.cpp
        impl/mcpprotocolcanceltaskrequest.cpp
        impl/mcpprotocolcalltoolrequest.cpp
        impl/mcpprotocolcalltoolrequestparams.cpp
        impl/mcpprotocolgetpromptrequestparams.cpp
        impl/mcpprotocolgettaskpayloadrequest.cpp
        impl/mcpprotocolgettaskrequest.cpp
        impl/mcpprotocolunsubscriberequestparams.cpp
        impl/mcpprotocolresourcetemplate.cpp
        impl/mcpprotocoltoollistchangednotification.cpp
        impl/mcpprotocolresourcelistchangednotification.cpp
        impl/mcpprotocolresourceupdatednotification.cpp
        impl/mcpprotocoljsonrpcerrorresponse.cpp
        impl/mcpprotocolpaginatedrequestparams.cpp
        impl/mcpprotocolrequestparams.cpp
        impl/mcpprotocolinitializerequestparams.cpp
        impl/mcpprotocolsetlevelrequestparams.cpp
        impl/mcpprotocolcompleterequestparams.cpp
        impl/mcpprotocolreadresourcerequestparams.cpp
        impl/mcpprotocolsubscriberequestparams.cpp
        impl/mcpprotocolpromptreference.cpp
        impl/mcpprotocolprogressnotificationparams.cpp
        impl/mcpprotocolembeddedresource.cpp
        impl/mcpprotocoltextresourcecontents.cpp
        impl/mcpprotocollegacytitledenumschema.cpp
        impl/mcpprotocolcreatetaskresult.cpp
        impl/mcpprotocolblobresourcecontents.cpp
        impl/mcpprotocolgetpromptresult.cpp
        impl/mcpprotocolresourceupdatednotificationparams.cpp
        impl/mcpprotocolpromptlistchangednotification.cpp
        impl/mcpprotocolpaginatedresult.cpp
        impl/mcpprotocolgetpromptrequest.cpp
        impl/mcpprotocolreadresourcerequest.cpp
        impl/mcpprotocolpingrequest.cpp
        impl/mcpprotocollisttoolsrequest.cpp
        impl/mcpprotocollistresourcetemplatesrequest.cpp
        impl/mcpprotocolinitializerequest.cpp
        impl/mcpprotocollisttasksrequest.cpp
        impl/mcpprotocollistpromptsrequest.cpp
        impl/mcpprotocolsetlevelrequest.cpp
        impl/mcpprotocolsubscriberequest.cpp
        impl/mcpprotocolunsubscriberequest.cpp
        impl/mcpprotocolcompleterequest.cpp
        impl/mcpprotocollistresourcesrequest.cpp
        impl/mcpprotocoltaskstatusnotification.cpp
        impl/mcpprotocolprogressnotification.cpp
        impl/mcpprotocolresult.cpp
        impl/mcpprotocollistresourcetemplatesresult.cpp
        impl/mcpprotocollistresourcesresult.cpp
        impl/mcpprotocolprompt.cpp
        impl/mcpprotocolresource.cpp
        impl/mcpprotocolrootslistchangednotification.cpp
        impl/mcpprotocolnotificationparams.cpp
        impl/mcpprotocolcancellednotification.cpp
        impl/mcpprotocolcancellednotificationparams.cpp
        impl/mcpprotocolloggingmessagenotification.cpp
        impl/mcpprotocolmeta.cpp
        impl/mcpprotocoluntitledsingleselectenumschema.cpp
        impl/mcpprotocoltaskmetadata.cpp
        impl/mcpprotocolstringschema.cpp
        impl/mcpprotocolnumberschema.cpp
        impl/mcpprotocolrelatedtaskmetadata.cpp
        impl/mcpprotocolmodelpreferences.cpp
        impl/mcpprotocoltoolchoice.cpp
        impl/mcpprotocolerror.cpp
        impl/mcpprotocoltoolchoice.h
        impl/mcpprotocolerror.h
        impl/mcpprotocolloggingmessagenotificationparams.cpp
        impl/mcpprotocolloggingmessagenotificationparams.h
        impl/mcpprotocoltoolexecution.cpp
        impl/mcpprotocoltoolexecution.h
        impl/mcpprotocoltoolusecontent.cpp
        impl/mcpprotocoltoolresultcontent.cpp
        impl/mcpprotocoltextcontent.h
        impl/mcpprotocoltask.h
        impl/mcpprotocolroot.h
        impl/mcpprotocolimplementation.h
        impl/mcpprotocolresourcetemplatereference.h
        impl/mcpprotocolpromptargument.h
        impl/mcpprotocolbasemetadata.h
        impl/mcpprotocolbooleanschema.h
        impl/mcpprotocolelicitationcompletenotification.h
        impl/mcpprotocolresourcelink.h
        impl/mcpprotocolinitializednotification.h
        impl/mcpprotocollistpromptsresult.h
        impl/mcpprotocoltaskstatusnotificationparams.h
        impl/mcpprotocolcanceltaskrequest.h
        impl/mcpprotocolcalltoolrequest.h
        impl/mcpprotocolcalltoolrequestparams.h
        impl/mcpprotocolgetpromptrequestparams.h
        impl/mcpprotocolgettaskpayloadrequest.h
        impl/mcpprotocolgettaskrequest.h
        impl/mcpprotocolunsubscriberequestparams.h
        impl/mcpprotocolresourcetemplate.h
        impl/mcpprotocoltoollistchangednotification.h
        impl/mcpprotocolresourcelistchangednotification.h
        impl/mcpprotocolresourceupdatednotification.h
        impl/mcpprotocoljsonrpcerrorresponse.h
        impl/mcpprotocolpaginatedrequestparams.h
        impl/mcpprotocolrequestparams.h
        impl/mcpprotocolinitializerequestparams.h
        impl/mcpprotocolsetlevelrequestparams.h
        impl/mcpprotocolcompleterequestparams.h
        impl/mcpprotocolreadresourcerequestparams.h
        impl/mcpprotocolsubscriberequestparams.h
        impl/mcpprotocolpromptreference.h
        impl/mcpprotocolprogressnotificationparams.h
        impl/mcpprotocolembeddedresource.h
        impl/mcpprotocoltextresourcecontents.h
        impl/mcpprotocollegacytitledenumschema.h
        impl/mcpprotocolcreatetaskresult.h
        impl/mcpprotocolblobresourcecontents.h
        impl/mcpprotocolgetpromptresult.h
        impl/mcpprotocolresourceupdatednotificationparams.h
        impl/mcpprotocolpromptlistchangednotification.h
        impl/mcpprotocolpaginatedresult.h
        impl/mcpprotocolgetpromptrequest.h
        impl/mcpprotocolreadresourcerequest.h
        impl/mcpprotocolpingrequest.h
        impl/mcpprotocollisttoolsrequest.h
        impl/mcpprotocollistresourcetemplatesrequest.h
        impl/mcpprotocolinitializerequest.h
        impl/mcpprotocollisttasksrequest.h
        impl/mcpprotocollistpromptsrequest.h
        impl/mcpprotocolsetlevelrequest.h
        impl/mcpprotocolsubscriberequest.h
        impl/mcpprotocolunsubscriberequest.h
        impl/mcpprotocolcompleterequest.h
        impl/mcpprotocollistresourcesrequest.h
        impl/mcpprotocoltaskstatusnotification.h
        impl/mcpprotocolprogressnotification.h
        impl/mcpprotocolresult.h
        impl/mcpprotocollistresourcetemplatesresult.h
        impl/mcpprotocollistresourcesresult.h
        impl/mcpprotocolprompt.h
        impl/mcpprotocolresource.h
        impl/mcpprotocolrootslistchangednotification.h
        impl/mcpprotocolnotificationparams.h
        impl/mcpprotocolcancellednotification.h
        impl/mcpprotocolcancellednotificationparams.h
        impl/mcpprotocolloggingmessagenotification.h
        impl/mcpprotocolmeta.h
        impl/mcpprotocoluntitledsingleselectenumschema.h
        impl/mcpprotocoltaskmetadata.h
        impl/mcpprotocolstringschema.h
        impl/mcpprotocolnumberschema.h
        impl/mcpprotocolrelatedtaskmetadata.h
        impl/mcpprotocolmodelpreferences.h
        impl/mcpprotocoltoolannotations.cpp
        impl/mcpprotocoltoolannotations.h
        impl/mcpprotocoltoolusecontent.h
        impl/mcpprotocoltoolresultcontent.h
        impl/mcpprotocolaudiocontent.cpp
        impl/mcpprotocolicon.cpp
        impl/mcpprotocolicon.h
        impl/mcpprotocolaudiocontent.h
        impl/mcpprotocolannotations.cpp
        impl/mcpprotocolannotations.h
        impl/mcpprotocolutils.h
        impl/mcpprotocolutils.cpp
        impl/mcpprotocolmodelhint.cpp
        impl/mcpprotocolclientcapabilities.cpp
        impl/mcpprotocolpromptmessage.cpp
        impl/mcpprotocolmodelhint.h
        impl/mcpprotocolclientcapabilities.h
        impl/mcpprotocolpromptmessage.h
        server/mcpprotocolserver.h
        server/mcpprotocolserver.cpp
        server/mcpserver.cpp
        server/mcpserver.h
        server/mcpservermanager.cpp
        server/mcpservermanager.h
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
        common/mcpprotocolutils.h
        common/mcpprotocolutils.cpp
        models/mcpservermodel.cpp
        models/mcpservermodel.h
        models/mcpserversortfilterproxymodel.cpp
        models/mcpserversortfilterproxymodel.h
)
generate_export_header(KF6TextAutoGenerateTextMcpProtocolCore BASE_NAME textautogeneratetextmcpprotocolcore)

ecm_generate_headers(TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolcommon_HEADERS
    HEADER_NAMES
    McpProtocolPlugin
    McpProtocolPluginInterface
    McpProtocolSettings
    REQUIRED_HEADERS TextAutoGenerateTextMcpProtocol_mcpprotocolcommon_HEADERS
    PREFIX TextAutoGenerateTextMcpProtocolCore
    RELATIVE common
)

ecm_generate_headers(TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolclient_HEADERS
    HEADER_NAMES
    McpProtocolClient
    REQUIRED_HEADERS TextAutoGenerateTextMcpProtocol_mcpprotocolclient_HEADERS
    PREFIX TextAutoGenerateTextMcpProtocolCore
    RELATIVE client
)

ecm_generate_headers(TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolserver_HEADERS
    HEADER_NAMES
    McpProtocolServer
    McpServer
    McpServerManager
    REQUIRED_HEADERS TextAutoGenerateTextMcpProtocol_mcpprotocolserver_HEADERS
    PREFIX TextAutoGenerateTextMcpProtocolCore
    RELATIVE server
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextmcpprotocolcore_export.h
        ${TextAutoGenerateTextMcpProtocol_mcpprotocolcommon_HEADERS}
        ${TextAutoGenerateTextMcpProtocol_mcpprotocolclient_HEADERS}
        ${TextAutoGenerateTextMcpProtocol_mcpprotocolserver_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextMcpProtocolCore/textautogeneratetextmcpprotocolcore
    COMPONENT Devel
)

install(
    FILES
        ${TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolcommon_HEADERS}
        ${TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolclient_HEADERS}
        ${TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolserver_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextMcpProtocolCore/TextAutoGenerateTextMcpProtocolCore
    COMPONENT Devel
)

target_link_libraries(
    KF6TextAutoGenerateTextMcpProtocolCore
    Qt::Core
    KF6::CoreAddons
    KF6::ConfigCore
)

set_target_properties(
    KF6TextAutoGenerateTextMcpProtocolCore
    PROPERTIES
        VERSION
            ${TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_VERSION}
        SOVERSION
            ${TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_SOVERSION}
        EXPORT_NAME
            TextAutoGenerateTextMcpProtocolCore
)

install(
    TARGETS
        KF6TextAutoGenerateTextMcpProtocolCore
    EXPORT KF6TextAutoGenerateTextMcpProtocolCoreTargets
    ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

install(
    EXPORT KF6TextAutoGenerateTextMcpProtocolCoreTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextAutoGenerateTextMcpProtocolCoreTargets.cmake
    NAMESPACE KF6::
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextMcpProtocolCoreConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextMcpProtocolCoreConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextAutoGenerateTextMcpProtocolCoreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextMcpProtocolCoreConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
