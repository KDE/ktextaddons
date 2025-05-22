/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralreply.h"

MistralReply::MistralReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateReply{netReply, requestType, parent}
{
}

MistralReply::~MistralReply() = default;

QString MistralReply::readResponse() const
{
    // TODO
    return {};
}

#include "moc_mistralreply.cpp"
