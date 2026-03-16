# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

add_library(KF6TextAutoGenerateTextMcpProtocol)

add_library(KF6::TextAutoGenerateTextMcpProtocol ALIAS KF6TextAutoGenerateTextMcpProtocol)

target_sources(
    KF6TextAutoGenerateTextMcpProtocol
    PRIVATE
        mcpprotocolimagecontent.h
        mcpprotocolimagecontent.cpp
        mcpprotocoltextcontent.cpp
        mcpprotocoltextcontent.h
        mcpprotocolannotations.cpp
        mcpprotocolannotations.h
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
