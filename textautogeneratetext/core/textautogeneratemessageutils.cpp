/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessageutils.h"

#include "textautogenerateblockcmarksupport.h"
using namespace Qt::StringLiterals;
using namespace TextAutoGenerateText;

static QString convertMessageText(const QString &str, const QByteArray &uuid, const QString &searchText, int &numberOfTextSearched, int hightLightStringIndex)
{
    TextAutoGenerateBlockCMarkSupport cmark;
    return cmark.convertMessageText(str, uuid, searchText, numberOfTextSearched, hightLightStringIndex);
}

QString TextAutoGenerateMessageUtils::convertTextToHtml(const QString &str,
                                                        const QByteArray &uuid,
                                                        const QString &searchedText,
                                                        int &numberOfTextSearched,
                                                        int hightLightStringIndex)
{
    const QString result = convertMessageText(str, uuid, searchedText, numberOfTextSearched, hightLightStringIndex);
    // qDebug() << " RESULT ************ " << result;
    return "<qt>"_L1 + result + "</qt>"_L1;
}
