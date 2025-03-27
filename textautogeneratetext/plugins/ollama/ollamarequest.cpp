/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamarequest.h"

OllamaRequest::OllamaRequest() = default;

OllamaRequest::~OllamaRequest() = default;

QString OllamaRequest::message() const
{
    return mMessage;
}

void OllamaRequest::setMessage(const QString &newMessage)
{
    mMessage = newMessage;
}

QDebug operator<<(QDebug d, const OllamaRequest &t)
{
    d.space() << "message:" << t.message();
    return d;
}

#include "moc_ollamarequest.cpp"
