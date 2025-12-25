/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textutils_export.h"
#include <QString>
namespace TextUtils
{
/**
 * @brief The TextUtilsBlockCMarkSupport class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTUTILS_EXPORT TextUtilsBlockCMarkSupport
{
public:
    TextUtilsBlockCMarkSupport();
    virtual ~TextUtilsBlockCMarkSupport();
    [[nodiscard]] QString
    convertMessageText(const QString &str, const QByteArray &uuid, const QString &searchText, int &numberOfTextSearched, int hightLightStringIndex);

    [[nodiscard]] static int findNonEscaped(const QString &str, const QString &regionMarker, int startFrom);
    [[nodiscard]] static bool isEscaped(const QString &str, int pos);

    [[nodiscard]] static int findNewLineOrEndLine(const QString &str, const QString &regionMarker, int startFrom);

    [[nodiscard]] static QString convertTextWithUrl(const QString &str);

    [[nodiscard]] static QString markdownToRichTextCMark(const QString &markDown);

protected:
    [[nodiscard]] virtual QString addHighlighter(const QString &str,
                                                 const QString &language,
                                                 const QString &searchText,
                                                 const QByteArray &uuid,
                                                 int &blockCodeIndex,
                                                 int &numberOfTextSearched,
                                                 int hightLightStringIndex) = 0;
};
}
