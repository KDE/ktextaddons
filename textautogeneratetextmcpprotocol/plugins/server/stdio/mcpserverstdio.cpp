/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstdio.h"
#include "autogeneratetext_mcpprotocolserverplugin_lib_debug.h"
#include "common/mcpprotocolsettings.h"
#include "stdio/mcpserverstdioplugininterface.h"
#include <QJsonDocument>
#include <QProcess>
#include <QVariant>

McpServerStdio::McpServerStdio(McpServerStdioPluginInterface *interface, QObject *parent)
    : QObject{parent}
    , mProcess(new QProcess(this))
    , mInterface(interface)
{
    connect(mProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << mProcess->errorString();
        Q_EMIT error(mProcess->errorString());
    });
    connect(mProcess, &QProcess::started, this, &McpServerStdio::started);
    connect(mProcess, &QProcess::finished, this, &McpServerStdio::finished);
}

McpServerStdio::~McpServerStdio() = default;

void McpServerStdio::connection()
{
    const auto settings = mInterface->protocolSettings();
    qDebug() << " settings " << settings;
    mProcess->setProgram(settings.command());
    const QStringList lst = settings.arguments().split(u' ');
    mProcess->setArguments(lst);
    mProcess->start();
}

void McpServerStdio::send(const QJsonObject &obj)
{
    const auto data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    mProcess->write(data + "\n");
}

#include "moc_mcpserverstdio.cpp"
