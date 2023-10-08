/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextinfo.h"

VoskSpeechToTextInfo::VoskSpeechToTextInfo() = default;

VoskSpeechToTextInfo::~VoskSpeechToTextInfo() = default;

QString VoskSpeechToTextInfo::lang() const
{
    return mLang;
}

void VoskSpeechToTextInfo::setLang(const QString &newLang)
{
    mLang = newLang;
}

QString VoskSpeechToTextInfo::langText() const
{
    return mLangText;
}

void VoskSpeechToTextInfo::setLangText(const QString &newLangText)
{
    mLangText = newLangText;
}

QString VoskSpeechToTextInfo::md5() const
{
    return mMd5;
}

void VoskSpeechToTextInfo::setMd5(const QString &newMd5)
{
    mMd5 = newMd5;
}

QString VoskSpeechToTextInfo::version() const
{
    return mVersion;
}

void VoskSpeechToTextInfo::setVersion(const QString &newVersion)
{
    mVersion = newVersion;
}

QString VoskSpeechToTextInfo::url() const
{
    return mUrl;
}

void VoskSpeechToTextInfo::setUrl(const QString &newUrl)
{
    mUrl = newUrl;
}

quint64 VoskSpeechToTextInfo::size() const
{
    return mSize;
}

void VoskSpeechToTextInfo::setSize(quint64 newSize)
{
    mSize = newSize;
}

bool VoskSpeechToTextInfo::obsolete() const
{
    return mObsolete;
}

void VoskSpeechToTextInfo::setObsolete(bool newObsolete)
{
    mObsolete = newObsolete;
}

bool VoskSpeechToTextInfo::operator==(const VoskSpeechToTextInfo &other) const
{
    // TODO
    return false;
}

void VoskSpeechToTextInfo::parse(const QJsonObject &obj)
{
    // TODO
}

QDebug operator<<(QDebug d, const VoskSpeechToTextInfo &t)
{
    // TODO
    return d;
}
