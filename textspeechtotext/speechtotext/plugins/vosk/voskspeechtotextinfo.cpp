/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextinfo.h"

VoskSpeechToTextInfo::VoskSpeechToTextInfo() = default;

VoskSpeechToTextInfo::~VoskSpeechToTextInfo() = default;

bool VoskSpeechToTextInfo::isValid() const
{
    return !mIdentifier.isEmpty() && !mUrl.isEmpty() && !mObsolete;
}

QString VoskSpeechToTextInfo::identifier() const
{
    return mIdentifier;
}

void VoskSpeechToTextInfo::setIdentifier(const QString &newLang)
{
    mIdentifier = newLang;
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
    return mIdentifier == other.identifier() && mLangText == other.langText() && mMd5 == other.md5() && mVersion == other.version() && mUrl == other.url()
        && mSize == other.size() && mObsolete == other.obsolete() && mType == other.type() && mName == other.name();
}

void VoskSpeechToTextInfo::parse(const QJsonObject &obj)
{
    mLangText = obj[QLatin1String("lang_text")].toString();
    mIdentifier = obj[QLatin1String("lang")].toString();
    mMd5 = obj[QLatin1String("md5")].toString();
    mObsolete = obj[QLatin1String("obsolete")].toBool();
    mVersion = obj[QLatin1String("version")].toString();
    mSize = obj[QLatin1String("size")].toInteger();
    mUrl = obj[QLatin1String("url")].toString();
    mType = obj[QLatin1String("type")].toString();
    mName = obj[QLatin1String("name")].toString();
}

QString VoskSpeechToTextInfo::type() const
{
    return mType;
}

void VoskSpeechToTextInfo::setType(const QString &newType)
{
    mType = newType;
}

QString VoskSpeechToTextInfo::name() const
{
    return mName;
}

void VoskSpeechToTextInfo::setName(const QString &newName)
{
    mName = newName;
}

QDebug operator<<(QDebug d, const VoskSpeechToTextInfo &t)
{
    d << "mLang : " << t.identifier();
    d << "mLangText : " << t.langText();
    d << "mMd5 : " << t.md5();
    d << "mVersion : " << t.version();
    d << "mUrl : " << t.url();
    d << "mSize : " << t.size();
    d << "mObsolete : " << t.obsolete();
    d << "mType : " << t.type();
    d << "mName : " << t.name();
    return d;
}
