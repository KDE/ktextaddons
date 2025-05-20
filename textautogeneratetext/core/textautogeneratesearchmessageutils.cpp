/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchmessageutils.h"
#include <KLocalizedString>
using namespace TextAutoGenerateText;

QString TextAutoGenerateSearchMessageUtils::generatePreview(const QString &str)
{
    if (str.length() > 120) {
        return QStringLiteral("%1...").arg(str.left(120));
    }
    return str;
}

QString TextAutoGenerateSearchMessageUtils::scheme()
{
    return QStringLiteral("storage");
}

QString TextAutoGenerateSearchMessageUtils::generateGoToMessageLink(const QString &chatId, const QString &messageId)
{
    return QStringLiteral("%1://%2:%3").arg(scheme(), chatId, messageId);
}

QString TextAutoGenerateSearchMessageUtils::generatePreviewText(const QByteArray &chatId, const TextAutoGenerateMessage &msg)
{
    return QStringLiteral("%1<br/> <a href=\'%2'>%3</a>")
        .arg(TextAutoGenerateSearchMessageUtils::generatePreview(msg.content()),
             generateGoToMessageLink(QString::fromLatin1(chatId), QString::fromLatin1(msg.uuid())),
             i18n("Go to message"));
}
