/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkreply.h"

GenericNetworkReply::GenericNetworkReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateReply{netReply, requestType, parent}
{
}

GenericNetworkReply::~GenericNetworkReply() = default;

#include "moc_genericnetworkreply.cpp"
