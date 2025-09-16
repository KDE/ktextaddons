/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on code from alpaka
*/

#include "textautogeneratetextrequest.h"
using namespace TextAutoGenerateText;
TextAutoGenerateTextRequest::TextAutoGenerateTextRequest() = default;

TextAutoGenerateTextRequest::~TextAutoGenerateTextRequest() = default;

QString TextAutoGenerateTextRequest::message() const
{
    return mMessage;
}

void TextAutoGenerateTextRequest::setMessage(const QString &newMessage)
{
    mMessage = newMessage;
}

bool TextAutoGenerateTextRequest::operator==(const TextAutoGenerateTextRequest &other) const
{
    return other.message() == mMessage && other.model() == mModel && mMessages == other.messages() && mTools == other.tools();
}

QString TextAutoGenerateTextRequest::model() const
{
    return mModel;
}

void TextAutoGenerateTextRequest::setModel(const QString &newModel)
{
    mModel = newModel;
}

QJsonArray TextAutoGenerateTextRequest::messages() const
{
    return mMessages;
}

void TextAutoGenerateTextRequest::setMessages(const QJsonArray &newMessages)
{
    mMessages = newMessages;
}

QList<QByteArray> TextAutoGenerateTextRequest::tools() const
{
    return mTools;
}

void TextAutoGenerateTextRequest::setTools(const QList<QByteArray> &newTools)
{
    mTools = newTools;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextRequest &t)
{
    d.space() << "message:" << t.message();
    d.space() << "model:" << t.model();
    d.space() << "messages:" << t.messages();
    d.space() << "tools:" << t.tools();
    return d;
}

#include "moc_textautogeneratetextrequest.cpp"
