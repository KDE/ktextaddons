/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstdio.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include "stdio/mcpclientstdioplugininterface.h"
#include <QJsonDocument>
#include <QProcess>
#include <QVariant>

McpServerStdio::McpServerStdio(McpServerStdioPluginInterface *interface, QObject *parent)
    : QObject{parent}
    , mProcess(new QProcess(this))
    , mInterface(interface)
{
    connect(mProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << mProcess->errorString();
        Q_EMIT error(mProcess->errorString());
    });
    connect(mProcess, &QProcess::started, this, &McpServerStdio::started);
    connect(mProcess, &QProcess::finished, this, &McpServerStdio::finished);
}

McpServerStdio::~McpServerStdio() = default;

void McpServerStdio::connection()
{
    const QVariant connection = mInterface->connectionInfo();
    if (!connection.isNull()) {
        const QStringList info = connection.toStringList();
        // TODO
    }
}

void McpServerStdio::send(const QJsonObject &obj)
{
    const auto data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    mProcess->write(data + "\n");
}

#include "moc_mcpserverstdio.cpp"
