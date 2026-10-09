# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

add_executable(
    mcpserver_gui
    main.cpp
    servermainwidget.h
    servermainwidget.cpp
    mcptestserver.h
    mcptestserver.cpp
)

target_link_libraries(
    mcpserver_gui
    KF6::TextAutoGenerateTextMcpProtocolCore
    Qt::Widgets
)
