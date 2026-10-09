/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
// Stdio MCP server launched by mcpserverstdiotest: exits when stdin is closed.
#include <QCoreApplication>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerProtocolManager>
using namespace Qt::Literals::StringLiterals;

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolServerProtocolManager manager(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolImplementation serverInfo;
    serverInfo.setName(u"mcpserverstdiohelper"_s);
    serverInfo.setVersion(u"1.0"_s);
    manager.setServerInfo(serverInfo);
    QObject::connect(&manager, &TextAutoGenerateTextMcpProtocolCore::McpProtocolServerProtocolManager::runningChanged, &app, [](bool running) {
        if (!running) {
            QCoreApplication::quit();
        }
    });
    manager.start();
    if (!manager.isRunning()) {
        return 1;
    }
    return app.exec();
}
