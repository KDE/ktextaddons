# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
if(0)
    add_executable(
        mcpserver_gui
        main.cpp
        mainwidget.h
        mainwidget.cpp
    )

    target_link_libraries(
        mcpserver_gui
        KF6::TextAutoGenerateTextMcpProtocol
        Qt::Widgets
    )
endif()
