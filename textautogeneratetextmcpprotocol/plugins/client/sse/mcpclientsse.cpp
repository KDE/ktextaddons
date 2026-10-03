/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientsse.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include "mcpclientutils.h"
#include "sse/mcpclientsseplugininterface.h"
#include <KLocalizedString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslError>
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
    mParser.clear();
    mPostUrl.clear();
    QNetworkRequest request(url);
    request.setRawHeader("Accept"_ba, "text/event-stream"_ba);
    request.setRawHeader("Cache-Control"_ba, "no-cache"_ba);
    McpClientUtils::addHeaders(request, mInterface->protocolSettings().headers());

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

void McpClientSse::stop()
{
    mPostUrl.clear();
    if (mReply) {
        // finished() is emitted by reply
        mReply->abort();
    }
}

void McpClientSse::send(const QJsonObject &obj)
{
    if (!mPostUrl.isValid()) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Endpoint not received from server. Can't send message";
        Q_EMIT error(i18n("Server is not ready."));
        return;
    }
    QNetworkRequest request(mPostUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"_ba);
    McpClientUtils::addHeaders(request, mInterface->protocolSettings().headers());
    // Answer is sent in sse stream, post reply contains only status.
    QNetworkReply *reply = mNetworkAccessManager->post(request, QJsonDocument(obj).toJson(QJsonDocument::Compact));
    // Undefined when we post a notification or a response
    const QJsonValue requestId = obj.contains("method"_L1) ? obj.value("id"_L1) : QJsonValue(QJsonValue::Undefined);
    connect(reply, &QNetworkReply::finished, this, [this, reply, requestId]() {
        if (reply->error() != QNetworkReply::NoError) {
            qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Post failed:" << reply->errorString();
            Q_EMIT error(reply->errorString());
            if (!requestId.isUndefined()) {
                // Server didn't get request, it will never answer
                Q_EMIT received(McpClientUtils::createConnectionErrorResponse(requestId, reply->errorString()));
            }
        }
        reply->deleteLater();
    });
}

void McpClientSse::slotRead(QNetworkReply *reply)
{
    const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolSseParser::Event> events = mParser.feed(reply->readAll());
    for (const auto &event : events) {
        if (event.event == "endpoint") {
            const bool alreadyStarted = mPostUrl.isValid();
            mPostUrl = reply->url().resolved(QUrl(QString::fromUtf8(event.data)));
            qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Endpoint:" << mPostUrl;
            if (!alreadyStarted) {
                Q_EMIT started();
            }
        } else if (event.event == "message") {
            QJsonParseError parseError;
            const QJsonDocument doc = QJsonDocument::fromJson(event.data, &parseError);
            if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
                qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Invalid message:" << parseError.errorString() << event.data;
                continue;
            }
            Q_EMIT received(doc.object());
        } else {
            qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Ignore event:" << event.event;
        }
    }
}

#include "moc_mcpclientsse.cpp"
