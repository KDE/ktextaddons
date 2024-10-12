/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "unicodeemoticonparser.h"
#include "emojicategory.h"
#include "textemoticonscore_debug.h"
#include <QJsonObject>

#include <QFile>

using namespace TextEmoticonsCore;
using namespace Qt::Literals::StringLiterals;
UnicodeEmoticonParser::UnicodeEmoticonParser() = default;

UnicodeEmoticonParser::~UnicodeEmoticonParser() = default;

inline QDataStream &operator>>(QDataStream &stream, UnicodeEmoticon &emoji)
{
    QByteArray buffer;
    stream >> buffer;
    emoji.setUnicode(QString::fromUtf8(buffer));
    stream >> buffer;
    emoji.setIdentifier(QString::fromUtf8(buffer));
    qint32 categoryIndex = 0;
    stream >> categoryIndex;
    if (categoryIndex <= 0 || categoryIndex > getCategoryNames().length()) {
        emoji.setCategory({});
    } else {
        emoji.setCategory(getCategoryNames()[categoryIndex - 1]);
    }
    QList<QByteArray> annotationBuffers;
    stream >> annotationBuffers;
    Q_UNUSED(annotationBuffers);
    return stream;
}

QList<UnicodeEmoticon> UnicodeEmoticonParser::parse(const QString &path) const
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        return {};
    }
    auto buffer = file.readAll();
    buffer = qUncompress(buffer);
    QDataStream stream(&buffer, QIODevice::ReadOnly);
    // We use a fixed version to keep it binary compatible.
    // Also we do not use advanced data type so it does not matter.
    stream.setVersion(QDataStream::Qt_5_15);
    // Explicitly set endianess to ensure it's not relevant to architecture.
    stream.setByteOrder(QDataStream::LittleEndian);
    QList<UnicodeEmoticon> emojis;
    stream >> emojis;
    return emojis;
}
