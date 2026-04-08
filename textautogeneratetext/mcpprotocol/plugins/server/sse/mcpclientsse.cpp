/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientsse.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
using namespace Qt::Literals::StringLiterals;
McpClientSse::McpClientSse(McpClientSsePluginInterface *interface, QObject *parent)
    : QObject{parent}
    , mNetworkAccessManager(new QNetworkAccessManager(this))
    , mInterface(interface)
{
}

McpClientSse::~McpClientSse() = default;

void McpClientSse::connection()
{
    // TODO use get
    QUrl url;
    QNetworkRequest request(url);
    request.setRawHeader("Accept"_ba, "text/event-stream"_ba);
    request.setRawHeader("Cache-Control"_ba, "no-cache"_ba);

    mReply = mNetworkAccessManager->get(request);
    connect(mReply, &QNetworkReply::finished, this, &McpClientSse::finished);
    connect(mReply, &QNetworkReply::sslErrors, this, [this](const QList<QSslError> &errors) {
        for (const QSslError &error : errors) {
            qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << error.errorString();
        }
        mReply->ignoreSslErrors();
    });
    connect(mReply, &QNetworkReply::errorOccurred, this, [this]() {
        Q_EMIT error(mReply->errorString());
    });

    connect(mReply, &QNetworkReply::readyRead, this, &McpClientSse::slotRead);
}

void McpClientSse::send(const QJsonObject &obj)
{
    // Use post
    // TODO
}

void McpClientSse::slotRead()
{
    // TODO
    const QByteArray response = mReply->readAll();
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << " response " << response;
}

#include "moc_mcpclientsse.cpp"
