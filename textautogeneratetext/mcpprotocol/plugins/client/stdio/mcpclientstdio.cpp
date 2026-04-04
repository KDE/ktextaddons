/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstdio.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include <QProcess>

McpClientStdio::McpClientStdio(QObject *parent)
    : QObject{parent}
    , mProcess(new QProcess(this))
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
}

void McpClientStdio::send(const QJsonObject &obj)
{
    // TODO process write info
}

#include "moc_mcpclientstdio.cpp"
