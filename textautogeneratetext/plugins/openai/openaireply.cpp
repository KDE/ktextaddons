/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openaireply.h"

OpenAIReply::OpenAIReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateReply{netReply, requestType, parent}
{
}

OpenAIReply::~OpenAIReply() = default;

QString OpenAIReply::readResponse() const
{
    // TODO
    return {};
}

#include "moc_openaireply.cpp"
