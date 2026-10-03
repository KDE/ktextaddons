/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstdio.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include "stdio/mcpclientstdioplugininterface.h"
#include <KLocalizedString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>

McpClientStdio::McpClientStdio(McpClientStdioPluginInterface *interface, QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpBase{parent}
    , mProcess(new QProcess(this))
    , mInterface(interface)
{
    mProcess->setProcessChannelMode(QProcess::SeparateChannels);
    connect(mProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError processError) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << mProcess->errorString();
        Q_EMIT error(mProcess->errorString());
        // QProcess doesn't emit finished() when the process failed to start
        if (processError == QProcess::FailedToStart) {
            Q_EMIT finished();
        }
    });
    connect(mProcess, &QProcess::started, this, &McpClientStdio::started);
    connect(mProcess, &QProcess::finished, this, &McpClientStdio::finished);
    connect(mProcess, &QProcess::readyReadStandardOutput, this, &McpClientStdio::slotReadStandardOutput);
    connect(mProcess, &QProcess::readyReadStandardError, this, &McpClientStdio::slotReadStandardError);
}

McpClientStdio::~McpClientStdio()
{
    // Don't emit signals while we are destroyed.
    mProcess->disconnect(this);
    stop();
}

bool McpClientStdio::isRunning() const
{
    return mProcess->state() != QProcess::NotRunning;
}

void McpClientStdio::stop()
{
    if (!isRunning()) {
        return;
    }
    // Close stdin first and let server exit, then SIGTERM, then SIGKILL
    mProcess->closeWriteChannel();
    if (mProcess->waitForFinished(500)) {
        return;
    }
    mProcess->terminate();
    if (!mProcess->waitForFinished(1000)) {
        mProcess->kill();
        mProcess->waitForFinished(1000);
    }
}

void McpClientStdio::connection()
{
    if (isRunning()) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Client already started:" << mProcess->program();
        return;
    }
    const auto settings = mInterface->protocolSettings();
    if (settings.command().isEmpty()) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Impossible to start client. Command is empty.";
        Q_EMIT error(i18n("Impossible to start client. Command is empty."));
        return;
    }
    mBuffer.clear();
    mProcess->setProgram(settings.command());
    mProcess->setArguments(settings.arguments().isEmpty() ? QStringList{} : QProcess::splitCommand(settings.arguments()));
    // Always set environment: process is reused, previous environment must not be kept
    QProcessEnvironment processEnvironment = QProcessEnvironment::systemEnvironment();
    const QMap<QString, QString> environments = settings.environments();
    for (auto it = environments.cbegin(); it != environments.cend(); ++it) {
        processEnvironment.insert(it.key(), it.value());
    }
    mProcess->setProcessEnvironment(processEnvironment);
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Starting" << mProcess->program() << "with" << mProcess->arguments().count() << "arguments";
    mProcess->start(QIODevice::ReadWrite);
}

void McpClientStdio::send(const QJsonObject &obj)
{
    if (mProcess->state() == QProcess::NotRunning) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Impossible to send message. Client is not running." << obj;
        Q_EMIT error(i18n("Impossible to send message. Client is not running."));
        return;
    }
    const auto data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << " send " << data;
    mProcess->write(data + '\n');
}

void McpClientStdio::slotReadStandardOutput()
{
    // Messages are newline delimited json, a read can contain several of them or an incomplete one.
    mBuffer += mProcess->readAllStandardOutput();
    qsizetype index = -1;
    while ((index = mBuffer.indexOf('\n')) != -1) {
        const QByteArray line = mBuffer.left(index).trimmed();
        mBuffer.remove(0, index + 1);
        if (line.isEmpty()) {
            continue;
        }
        QJsonParseError parseError;
        const QJsonDocument doc = QJsonDocument::fromJson(line, &parseError);
        if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
            qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Invalid json received:" << line << parseError.errorString();
            continue;
        }
        qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << " received " << doc;
        Q_EMIT received(doc.object());
    }
}

void McpClientStdio::slotReadStandardError()
{
    const QByteArray errorOutput = mProcess->readAllStandardError();
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "stderr:" << errorOutput;
}

#include "moc_mcpclientstdio.cpp"
