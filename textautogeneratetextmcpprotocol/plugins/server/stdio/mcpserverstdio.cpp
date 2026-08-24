/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstdio.h"
#include "autogeneratetext_mcpprotocolserverplugin_lib_debug.h"
#include "common/mcpprotocolsettings.h"
#include "stdio/mcpserverstdioplugininterface.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>

using namespace Qt::Literals::StringLiterals;

McpServerStdio::McpServerStdio(McpServerStdioPluginInterface *interface, QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpBase{parent}
    , mProcess(new QProcess(this))
    , mInterface(interface)
{
    mProcess->setProcessChannelMode(QProcess::SeparateChannels);
    connect(mProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << mProcess->errorString();
        Q_EMIT error(mProcess->errorString());
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
        Q_EMIT error(u"Impossible to start server. Command is empty."_s);
        return;
    }
    mBuffer.clear();
    mProcess->setProgram(settings.command());
    mProcess->setArguments(settings.arguments().isEmpty() ? QStringList{} : QProcess::splitCommand(settings.arguments()));
    const QMap<QString, QString> environments = settings.environments();
    if (!environments.isEmpty()) {
        QProcessEnvironment processEnvironment = QProcessEnvironment::systemEnvironment();
        for (auto it = environments.cbegin(); it != environments.cend(); ++it) {
            processEnvironment.insert(it.key(), it.value());
        }
        mProcess->setProcessEnvironment(processEnvironment);
    }
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Starting" << mProcess->program() << mProcess->arguments();
    mProcess->start(QIODevice::ReadWrite);
}

void McpServerStdio::stop()
{
    if (!isRunning()) {
        return;
    }
    mProcess->closeWriteChannel();
    mProcess->terminate();
    if (!mProcess->waitForFinished(1000)) {
        mProcess->kill();
        mProcess->waitForFinished(1000);
    }
}

void McpServerStdio::send(const QJsonObject &obj)
{
    if (mProcess->state() != QProcess::Running) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Impossible to send message. Server is not running." << obj;
        Q_EMIT error(u"Impossible to send message. Server is not running."_s);
        return;
    }
    const auto data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << " send " << data;
    mProcess->write(data + '\n');
}

void McpServerStdio::slotReadStandardOutput()
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
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "stderr:" << mProcess->readAllStandardError();
}

#include "moc_mcpserverstdio.cpp"
