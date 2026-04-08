/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserversse.h"
#include "autogeneratetext_mcpprotocolserverplugin_lib_debug.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
using namespace Qt::Literals::StringLiterals;
McpServerSse::McpServerSse(McpServerSsePluginInterface *interface, QObject *parent)
    : QObject{parent}
    , mNetworkAccessManager(new QNetworkAccessManager(this))
    , mInterface(interface)
{
}

McpServerSse::~McpServerSse() = default;

void McpServerSse::connection()
{
    // TODO use get
    QUrl url;
    QNetworkRequest request(url);
    request.setRawHeader("Accept"_ba, "text/event-stream"_ba);
    request.setRawHeader("Cache-Control"_ba, "no-cache"_ba);

    mReply = mNetworkAccessManager->get(request);
    connect(mReply, &QNetworkReply::finished, this, &McpServerSse::finished);
    connect(mReply, &QNetworkReply::sslErrors, this, [this](const QList<QSslError> &errors) {
        for (const QSslError &error : errors) {
            qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << error.errorString();
        }
        mReply->ignoreSslErrors();
    });
    connect(mReply, &QNetworkReply::errorOccurred, this, [this]() {
        Q_EMIT error(mReply->errorString());
    });

    connect(mReply, &QNetworkReply::readyRead, this, &McpServerSse::slotRead);
}

void McpServerSse::send(const QJsonObject &obj)
{
    // Use post
    // TODO
}

void McpServerSse::slotRead()
{
    // TODO
    const QByteArray response = mReply->readAll();
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << " response " << response;
}

#include "moc_mcpserversse.cpp"
