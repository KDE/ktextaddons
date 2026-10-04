/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstdio.h"
#include "autogeneratetext_mcpprotocolserverplugin_lib_debug.h"
#include "stdio/mcpserverstdioplugininterface.h"
#include <KLocalizedString>
#include <KShell>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>

namespace
{
// Maximum size of a message (it can contain images or files)
constexpr qsizetype maxBufferSize = 64 * 1024 * 1024;
}

McpServerStdio::McpServerStdio(McpServerStdioPluginInterface *interface, QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpBase{parent}
    , mProcess(new QProcess(this))
    , mInterface(interface)
{
    mProcess->setProcessChannelMode(QProcess::SeparateChannels);
    connect(mProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError processError) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << mProcess->errorString();
        Q_EMIT error(mProcess->errorString());
        // QProcess doesn't emit finished() when the process failed to start
        if (processError == QProcess::FailedToStart) {
            Q_EMIT finished();
        }
    });
    connect(mProcess, &QProcess::started, this, &McpServerStdio::started);
    connect(mProcess, &QProcess::finished, this, &McpServerStdio::finished);
    connect(mProcess, &QProcess::readyReadStandardOutput, this, &McpServerStdio::slotReadStandardOutput);
    connect(mProcess, &QProcess::readyReadStandardError, this, &McpServerStdio::slotReadStandardError);
}

McpServerStdio::~McpServerStdio()
{
    // Don't emit signals while we are destroyed.
    mProcess->disconnect(this);
    stop();
}

bool McpServerStdio::isRunning() const
{
    return mProcess->state() != QProcess::NotRunning;
}

void McpServerStdio::connection()
{
    if (isRunning()) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Server already started:" << mProcess->program();
        return;
    }
    const auto settings = mInterface->protocolSettings();
    if (settings.command().isEmpty()) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Impossible to start server. Command is empty.";
        Q_EMIT error(i18n("Impossible to start server. Command is empty."));
        return;
    }
    // Support shell quoting ('a b', "a b", a\ b)
    KShell::Errors splitError = KShell::NoError;
    const QStringList arguments = KShell::splitArgs(settings.arguments(), KShell::NoOptions, &splitError);
    if (splitError != KShell::NoError) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Impossible to start server. Invalid arguments:" << settings.arguments();
        Q_EMIT error(i18n("Impossible to start server. Arguments are invalid."));
        // Allow to restart with other settings
        Q_EMIT finished();
        return;
    }
    mBuffer.clear();
    mProcess->setProgram(settings.command());
    mProcess->setArguments(arguments);
    // Always set environment: process is reused, previous environment must not be kept
    QProcessEnvironment processEnvironment = QProcessEnvironment::systemEnvironment();
    const QMap<QString, QString> environments = settings.environments();
    for (auto it = environments.cbegin(); it != environments.cend(); ++it) {
        processEnvironment.insert(it.key(), it.value());
    }
    mProcess->setProcessEnvironment(processEnvironment);
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Starting" << mProcess->program() << "with" << mProcess->arguments().count() << "arguments";
    mProcess->start(QIODevice::ReadWrite);
}

void McpServerStdio::stop()
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

void McpServerStdio::send(const QJsonObject &obj)
{
    if (mProcess->state() == QProcess::NotRunning) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Impossible to send message. Server is not running." << obj;
        Q_EMIT error(i18n("Impossible to send message. Server is not running."));
        return;
    }
    const auto data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << " send " << data;
    if (mProcess->write(data + '\n') == -1) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Impossible to send message:" << mProcess->errorString();
        Q_EMIT error(mProcess->errorString());
    }
}

void McpServerStdio::slotReadStandardOutput()
{
    // Messages are newline delimited json, a read can contain several of them or an incomplete one.
    mBuffer += mProcess->readAllStandardOutput();
    if (mBuffer.size() > maxBufferSize && !mBuffer.contains('\n')) {
        // Invalid output (no newline), don't let buffer grow forever
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Message too big, drop it";
        mBuffer.clear();
        Q_EMIT error(i18n("Message received from server is too big."));
        return;
    }
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
            qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Invalid json received:" << line << parseError.errorString();
            continue;
        }
        qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << " received " << doc;
        Q_EMIT received(doc.object());
    }
}

void McpServerStdio::slotReadStandardError()
{
    // Servers use stderr for logging.
    const QByteArray errorOutput = mProcess->readAllStandardError();
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "stderr:" << errorOutput;
}

#include "moc_mcpserverstdio.cpp"
