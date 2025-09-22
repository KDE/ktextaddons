/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratereply.h"
#include <QNetworkReply>

using namespace Qt::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateReply::TextAutoGenerateReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent)
    : QObject{parent}
    , mReply{netReply}
    , mRequestType{requestType}
{
}

TextAutoGenerateReply::~TextAutoGenerateReply() = default;

const TextAutoGenerateReply::RequestTypes &TextAutoGenerateReply::requestType() const
{
    return mRequestType;
}

const TextAutoGenerateText::TextAutoGenerateTextReplyInfo &TextAutoGenerateReply::info() const
{
    return mInfo;
}

void TextAutoGenerateReply::cancel()
{
    if (mReply) {
        mReply->abort();
    }
}

const QList<TextAutoGenerateReply::ToolCallArgument> &TextAutoGenerateReply::toolCallArguments() const
{
    return mToolCallArguments;
}

void TextAutoGenerateReply::setToolCallArguments(const QList<ToolCallArgument> &newToolCallArguments)
{
    mToolCallArguments = newToolCallArguments;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument &t)
{
    d.space() << "keyTool:" << t.keyTool;
    d.space() << "value:" << t.value;
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &t)
{
    d.space() << "total:" << t.total;
    d.space() << "completed:" << t.completed;
    d.space() << "status:" << t.status;
    return d;
}
#include "moc_textautogeneratereply.cpp"
