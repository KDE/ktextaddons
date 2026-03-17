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
        mcpprotocoltoolannotations.cpp
        mcpprotocoltoolusecontent.cpp
        mcpprotocoltextcontent.h
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
