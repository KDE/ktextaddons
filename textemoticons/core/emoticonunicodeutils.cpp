/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticonunicodeutils.h"
#include <QList>
using namespace TextEmoticonsCore;
QString EmoticonUnicodeUtils::emojiFontName()
{
#ifdef Q_OS_WIN
    return QStringLiteral("Segoe UI Emoji");
#else
    return QStringLiteral("NotoColorEmoji");
#endif
}

QString EmoticonUnicodeUtils::recentIdentifier()
{
    return QStringLiteral("recents");
}

QString EmoticonUnicodeUtils::customIdentifier()
{
    return QStringLiteral("customs");
}

QString EmoticonUnicodeUtils::recentName()
{
    return QStringLiteral("⌛️");
}

QString EmoticonUnicodeUtils::customName()
{
    return QStringLiteral("🖼️");
}

// input: codepoints in hex like 1f9d7-1f3fb-2640
// output: QString with 3 ucs4 code points for the above, which is in fact 5 QChars.
QString EmoticonUnicodeUtils::escapeUnicodeEmoji(const QString &pString)
{
    QString retString;

    const QList<QStringView> parts = QStringView(pString).split(QLatin1Char('-'));
    for (const QStringView &item : parts) {
        bool ok;
        const int part = item.toInt(&ok, 16);
        Q_ASSERT(ok);
        if (QChar::requiresSurrogates(part)) {
            retString += QChar::highSurrogate(part);
            retString += QChar::lowSurrogate(part);
        } else {
            retString += QChar(part);
        }
    }

    return retString;
}
