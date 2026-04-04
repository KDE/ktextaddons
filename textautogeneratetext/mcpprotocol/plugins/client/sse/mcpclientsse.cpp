/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientsse.h"
#include <QNetworkAccessManager>

McpClientSse::McpClientSse(QObject *parent)
    : QObject{parent}
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
}

McpClientSse::~McpClientSse() = default;

void McpClientSse::connection()
{
    // TODO
}

#include "moc_mcpclientsse.cpp"
