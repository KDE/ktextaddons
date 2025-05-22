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

TextAutoGenerateText::TextAutoGenerateTextContext TextAutoGenerateTextRequest::context() const
{
    return mContext;
}

void TextAutoGenerateTextRequest::setContext(const TextAutoGenerateText::TextAutoGenerateTextContext &newContext)
{
    mContext = newContext;
}

bool TextAutoGenerateTextRequest::operator==(const TextAutoGenerateTextRequest &other) const
{
    return other.context() == mContext && other.message() == mMessage && other.model() == mModel && mMessages == other.messages();
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

QDebug operator<<(QDebug d, const TextAutoGenerateTextRequest &t)
{
    d.space() << "message:" << t.message();
    d.space() << "context:" << t.context();
    d.space() << "model:" << t.model();
    d.space() << "messages:" << t.messages();
    return d;
}

#include "moc_textautogeneratetextrequest.cpp"
