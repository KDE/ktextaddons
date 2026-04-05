/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstdio.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include "stdio/mcpclientstdioplugininterface.h"
#include <QJsonDocument>
#include <QProcess>
#include <QVariant>

McpClientStdio::McpClientStdio(McpClientStdioPluginInterface *interface, QObject *parent)
    : QObject{parent}
    , mProcess(new QProcess(this))
    , mInterface(interface)
{
    connect(mProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << mProcess->errorString();
        Q_EMIT error(mProcess->errorString());
    });
    connect(mProcess, &QProcess::started, this, &McpClientStdio::started);
    connect(mProcess, &QProcess::finished, this, &McpClientStdio::finished);
}

McpClientStdio::~McpClientStdio() = default;

void McpClientStdio::connection()
{
    const QVariant connection = mInterface->connectionInfo();
    if (!connection.isNull()) {
        const QStringList info = connection.toStringList();
        // TODO
    }
}

void McpClientStdio::send(const QJsonObject &obj)
{
    const auto data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    mProcess->write(data + "\n");
}

#include "moc_mcpclientstdio.cpp"
