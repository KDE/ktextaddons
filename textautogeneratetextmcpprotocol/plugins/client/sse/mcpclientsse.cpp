/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientsse.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include "sse/mcpclientsseplugininterface.h"
#include <KLocalizedString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
using namespace Qt::Literals::StringLiterals;
McpClientSse::McpClientSse(McpClientSsePluginInterface *interface, QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpBase{parent}
    , mNetworkAccessManager(new QNetworkAccessManager(this))
    , mInterface(interface)
{
}

McpClientSse::~McpClientSse()
{
    // Don't emit signals while we are destroyed.
    if (mReply) {
        mReply->disconnect(this);
    }
}

void McpClientSse::connection()
{
    if (mReply) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Client already started:" << mReply->url();
        return;
    }
    const auto settings = mInterface->protocolSettings();
    const QUrl url = settings.serverUrl();
    if (!url.isValid() || url.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Impossible to start client. Url is invalid:" << url;
        Q_EMIT error(i18n("Impossible to start client. Url is invalid."));
        return;
    }
    QNetworkRequest request(url);
    request.setRawHeader("Accept"_ba, "text/event-stream"_ba);
    request.setRawHeader("Cache-Control"_ba, "no-cache"_ba);
    const QStringList headers = settings.headers();
    for (const QString &header : headers) {
        const qsizetype index = header.indexOf(u':');
        if (index <= 0) {
            qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Invalid header, expected \"Name: Value\"";
            continue;
        }
        request.setRawHeader(header.left(index).trimmed().toUtf8(), header.mid(index + 1).trimmed().toUtf8());
    }

    QNetworkReply *reply = mNetworkAccessManager->get(request);
    mReply = reply;
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (mReply == reply) {
            mReply = nullptr;
        }
        reply->deleteLater();
        Q_EMIT finished();
    });
    connect(reply, &QNetworkReply::sslErrors, this, [](const QList<QSslError> &errors) {
        for (const QSslError &error : errors) {
            qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << error.errorString();
        }
    });
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply]() {
        Q_EMIT error(reply->errorString());
    });

    connect(reply, &QNetworkReply::readyRead, this, [this, reply]() {
        slotRead(reply);
    });
}

void McpClientSse::send(const QJsonObject &)
{
    // TODO use post
    qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Sending message is not implemented yet.";
    Q_EMIT error(i18n("Sending message is not implemented yet."));
}

void McpClientSse::slotRead(QNetworkReply *reply)
{
    // TODO
    const QByteArray response = reply->readAll();
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << " response " << response;
}

#include "moc_mcpclientsse.cpp"
