# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

add_library(KF6TextAutoGenerateTextMcpProtocol)

add_library(KF6::TextAutoGenerateTextMcpProtocol ALIAS KF6TextAutoGenerateTextMcpProtocol)

ecm_qt_declare_logging_category(KF6TextAutoGenerateTextMcpProtocol HEADER textautogeneratetextmcpprotocol_debug.h
    IDENTIFIER TEXTAUTOGENERATEMCPPROTOCOL_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetextmcpprotocol
    DESCRIPTION "KF6 (TextAutoGenerateText MCP protocols)"
    EXPORT KTEXTADDONS
)

target_sources(
    KF6TextAutoGenerateTextMcpProtocol
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
        mcpprotocoltextresourcecontents.cpp
        mcpprotocollegacytitledenumschema.cpp
        mcpprotocolcreatetaskresult.cpp
        mcpprotocolblobresourcecontents.cpp
        mcpprotocolgetpromptresult.cpp
        mcpprotocolresourceupdatednotificationparams.cpp
        mcpprotocolpromptlistchangednotification.cpp
        mcpprotocolpaginatedresult.cpp
        mcpprotocollistresourcesresult.cpp
        mcpprotocolprompt.cpp
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
        mcpprotocoltextresourcecontents.h
        mcpprotocollegacytitledenumschema.h
        mcpprotocolcreatetaskresult.h
        mcpprotocolblobresourcecontents.h
        mcpprotocolgetpromptresult.h
        mcpprotocolresourceupdatednotificationparams.h
        mcpprotocolpromptlistchangednotification.h
        mcpprotocolpaginatedresult.h
        mcpprotocollistresourcesresult.h
        mcpprotocolprompt.h
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
        mcpprotocolaudiocontent.cpp
        mcpprotocolicon.cpp
        mcpprotocolicon.h
        mcpprotocolaudiocontent.h
        mcpprotocolannotations.cpp
        mcpprotocolannotations.h
        mcpprotocolutils.h
        mcpprotocolutils.cpp
        mcpprotocolmodelhint.cpp
        mcpprotocolmodelhint.h
)

generate_export_header(KF6TextAutoGenerateTextMcpProtocol BASE_NAME textautogeneratetextmcpprotocol)

target_link_libraries(KF6TextAutoGenerateTextMcpProtocol Qt::Core)

install(
    TARGETS
        KF6TextAutoGenerateTextMcpProtocol
    EXPORT KF6TextAutoGenerateTextMcpProtocolTargets
    ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
