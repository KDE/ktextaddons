# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

add_executable(
    mcpclient_gui
    main.cpp
    mainwidget.h
    mainwidget.cpp
)

target_link_libraries(
    mcpclient_gui
    KF6::TextAutoGenerateTextMcpProtocolCore
    Qt::Widgets
)
