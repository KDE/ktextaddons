/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>
class QNetworkAccessManager;
class QNetworkReply;
class McpClientSse : public QObject
{
    Q_OBJECT
public:
    explicit McpClientSse(QObject *parent = nullptr);
    ~McpClientSse() override;

    void connection();

private:
    QNetworkAccessManager *const mNetworkAccessManager;
    QNetworkReply *mReply = nullptr;
};
