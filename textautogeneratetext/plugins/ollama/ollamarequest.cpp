/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on code from alpaka
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

TextAutogenerateText::TextAutogenerateTextContext OllamaRequest::context() const
{
    return mContext;
}

void OllamaRequest::setContext(const TextAutogenerateText::TextAutogenerateTextContext &newContext)
{
    mContext = newContext;
}

bool OllamaRequest::operator==(const OllamaRequest &other) const
{
    return other.context() == mContext && other.message() == mMessage && other.model() == mModel;
}

QString OllamaRequest::model() const
{
    return mModel;
}

void OllamaRequest::setModel(const QString &newModel)
{
    mModel = newModel;
}

QDebug operator<<(QDebug d, const OllamaRequest &t)
{
    d.space() << "message:" << t.message();
    d.space() << "context:" << t.context();
    d.space() << "model:" << t.model();
    return d;
}

#include "moc_ollamarequest.cpp"
