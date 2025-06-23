/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchmessageutils.h"
using namespace Qt::Literals::StringLiterals;

#include <KLocalizedString>
using namespace TextAutoGenerateText;

QString TextAutoGenerateSearchMessageUtils::generatePreview(const QString &str)
{
    if (str.length() > 120) {
        return u"%1..."_s.arg(str.left(120));
    }
    return str;
}

QString TextAutoGenerateSearchMessageUtils::scheme()
{
    return u"storage"_s;
}

QString TextAutoGenerateSearchMessageUtils::generateGoToMessageLink(const QString &chatId, const QString &messageId)
{
    return u"%1://%2:%3"_s.arg(scheme(), chatId, messageId);
}

QString TextAutoGenerateSearchMessageUtils::generatePreviewText(const QByteArray &chatId, const TextAutoGenerateMessage &msg)
{
    return u"%1<br/> <a href=\'%2'>%3</a>"_s.arg(TextAutoGenerateSearchMessageUtils::generatePreview(msg.content()),
                                                 generateGoToMessageLink(QString::fromLatin1(chatId), QString::fromLatin1(msg.uuid())),
                                                 i18n("Go to message"));
}
