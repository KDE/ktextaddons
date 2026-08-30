/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextinfo.h"

using namespace Qt::Literals::StringLiterals;

VoskSpeechToTextInfo::VoskSpeechToTextInfo() = default;

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
    mLangText = obj["lang_text"_L1].toString();
    mIdentifier = obj["lang"_L1].toString();
    mMd5 = obj["md5"_L1].toString();
    mObsolete = obj["obsolete"_L1].toBool();
    mVersion = obj["version"_L1].toString();
    mSize = obj["size"_L1].toInteger();
    mUrl = obj["url"_L1].toString();
    mType = obj["type"_L1].toString();
    mName = obj["name"_L1].toString();
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
