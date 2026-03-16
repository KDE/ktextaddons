# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

add_library(KF6TextAutoGenerateTextMcpProtocol)

add_library(KF6::TextAutoGenerateTextMcpProtocol ALIAS KF6TextAutoGenerateTextMcpProtocol)

target_sources(
    KF6TextAutoGenerateTextMcpProtocol
    PRIVATE
        mcpprotocolimagecontent.h
        mcpprotocolimagecontent.cpp
)

ecm_generate_export_header(KF6TextAutoGenerateTextMcpProtocol
    BASE_NAME textautogeneratetextmcpprotocol
    VERSION ${TEXTAUTOGENERATETEXT_VERSION}
    USE_VERSION_HEADER
)

target_link_libraries(KF6TextAutoGenerateTextMcpProtocol Qt::Core)

install(
    TARGETS
        KF6TextAutoGenerateTextMcpProtocol
    EXPORT KF6TextAutoGenerateTextMcpProtocolTargets
    ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)
