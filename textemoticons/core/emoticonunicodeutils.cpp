/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticonunicodeutils.h"
using namespace Qt::Literals::StringLiterals;

#include <QList>
using namespace TextEmoticonsCore;
QString EmoticonUnicodeUtils::emojiFontName()
{
#ifdef Q_OS_WIN
    return u"Segoe UI Emoji"_s;
#else
    return u"NotoColorEmoji"_s;
#endif
}

QString EmoticonUnicodeUtils::recentIdentifier()
{
    return u"recents"_s;
}

QString EmoticonUnicodeUtils::customIdentifier()
{
    return u"customs"_s;
}

QString EmoticonUnicodeUtils::recentName()
{
    return u"⌛️"_s;
}

QString EmoticonUnicodeUtils::customName()
{
    return u"🖼️"_s;
}

// input: codepoints in hex like 1f9d7-1f3fb-2640
// output: QString with 3 ucs4 code points for the above, which is in fact 5 QChars.
QString EmoticonUnicodeUtils::escapeUnicodeEmoji(const QString &pString)
{
    QString retString;

    const QList<QStringView> parts = QStringView(pString).split(u'-');
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
