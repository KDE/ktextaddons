/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstdio.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include "stdio/mcpclientstdioplugininterface.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QVariant>

McpClientStdio::McpClientStdio(McpClientStdioPluginInterface *interface, QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpBase{parent}
    , mProcess(new QProcess(this))
    , mInterface(interface)
{
    connect(mProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << mProcess->errorString();
        Q_EMIT error(mProcess->errorString());
    });
    connect(mProcess, &QProcess::started, this, &McpClientStdio::started);
    connect(mProcess, &QProcess::finished, this, &McpClientStdio::finished);
    connect(mProcess, &QProcess::readyReadStandardOutput, this, [this]() {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << mProcess->errorString();
        qDebug() << " received !!! ; " << mProcess->readAllStandardOutput();
        // Q_EMIT error(mProcess->errorString());
    });
    connect(mProcess, &QProcess::readyReadStandardError, this, [this]() {
        qWarning() << "error " << mProcess->readAllStandardError();
    });
    qDebug() << " cCCCCCCCCcccccccsdfsdfdsf";
}

McpClientStdio::~McpClientStdio() = default;

void McpClientStdio::connection()
{
    const auto settings = mInterface->protocolSettings();
    qDebug() << " settings " << settings;
    mProcess->setProgram(settings.command());
    const QStringList lst = settings.arguments().split(u' ');
    mProcess->setArguments(lst);
    mProcess->start();
}

void McpClientStdio::send(const QJsonObject &obj)
{
    const auto data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    mProcess->write(data + "\n");
    qDebug() << " obj " << obj;
}

#include "moc_mcpclientstdio.cpp"
