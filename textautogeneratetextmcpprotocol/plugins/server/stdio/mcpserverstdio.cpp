/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstdio.h"
#include "autogeneratetext_mcpprotocolserverplugin_lib_debug.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSocketNotifier>
#ifdef Q_OS_UNIX
#include <cerrno>
#include <unistd.h>
#endif

namespace
{
// Maximum size of a message (it can contain images or files)
constexpr qsizetype maxBufferSize = 64 * 1024 * 1024;
constexpr qsizetype readSize = 64 * 1024;
constexpr int standardInput = 0;
constexpr int standardOutput = 1;
}

McpServerStdio::McpServerStdio(QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpBase{parent}
{
}

McpServerStdio::~McpServerStdio()
{
    // Don't emit signals while we are destroyed.
    if (mNotifier) {
        mNotifier->setEnabled(false);
    }
}

bool McpServerStdio::isRunning() const
{
    return mStarted;
}

void McpServerStdio::connection()
{
    if (mStarted) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Server already started";
        return;
    }
#ifdef Q_OS_UNIX
    if (!mStandardOutput.isOpen() && !mStandardOutput.open(standardOutput, QIODevice::WriteOnly | QIODevice::Unbuffered)) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Impossible to open stdout:" << mStandardOutput.errorString();
        Q_EMIT error(i18n("Impossible to start server: %1", mStandardOutput.errorString()));
        Q_EMIT finished();
        return;
    }
    if (!mNotifier) {
        mNotifier = new QSocketNotifier(standardInput, QSocketNotifier::Read, this);
        connect(mNotifier, &QSocketNotifier::activated, this, &McpServerStdio::slotReadStandardInput);
    }
    mBuffer.clear();
    mNotifier->setEnabled(true);
    mStarted = true;
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Listen on stdin";
    Q_EMIT started();
#else
    // QSocketNotifier doesn't support pipes on Windows
    qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Stdio server is not supported on this platform";
    Q_EMIT error(i18n("Stdio server is not supported on this platform."));
    Q_EMIT finished();
#endif
}

void McpServerStdio::stop()
{
    if (!mStarted) {
        return;
    }
    mNotifier->setEnabled(false);
    mBuffer.clear();
    mStarted = false;
    Q_EMIT finished();
}

void McpServerStdio::send(const QJsonObject &obj)
{
    if (!mStarted) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Server not started. Can't send message";
        Q_EMIT error(i18n("Server is not started."));
        return;
    }
    // Compact json doesn't contain newline: one message by line
    const QByteArray data = QJsonDocument(obj).toJson(QJsonDocument::Compact) + '\n';
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << " send " << data;
    if (mStandardOutput.write(data) != data.size()) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Impossible to send message:" << mStandardOutput.errorString();
        Q_EMIT error(mStandardOutput.errorString());
    }
}

void McpServerStdio::slotReadStandardInput()
{
#ifdef Q_OS_UNIX
    char data[readSize];
    const ssize_t size = ::read(standardInput, data, sizeof(data));
    if (size < 0 && (errno == EINTR || errno == EAGAIN)) {
        return;
    }
    if (size <= 0) {
        // Client closed stdin: server must exit
        qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "stdin closed";
        stop();
        return;
    }
    mBuffer.append(data, size);
    processBuffer();
#endif
}

void McpServerStdio::processBuffer()
{
    // Messages are newline delimited json, a read can contain several of them or an incomplete one.
    qsizetype index = -1;
    while (mStarted && (index = mBuffer.indexOf('\n')) != -1) {
        const QByteArray line = mBuffer.left(index).trimmed();
        mBuffer.remove(0, index + 1);
        if (line.isEmpty()) {
            continue;
        }
        QJsonParseError parseError;
        const QJsonDocument doc = QJsonDocument::fromJson(line, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Invalid json received:" << parseError.errorString();
            continue;
        }
        if (doc.isObject()) {
            qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << " received " << doc;
            Q_EMIT received(doc.object());
        } else if (doc.isArray()) {
            // JSON-RPC batch (protocol 2025-03-26)
            const QJsonArray array = doc.array();
            for (const auto &value : array) {
                if (value.isObject()) {
                    Q_EMIT received(value.toObject());
                }
            }
        }
    }
    if (mBuffer.size() > maxBufferSize) {
        // Invalid input (no newline), don't let buffer grow forever
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Message too big, drop it";
        mBuffer.clear();
        Q_EMIT error(i18n("Message received from client is too big."));
    }
}

#include "moc_mcpserverstdio.cpp"
