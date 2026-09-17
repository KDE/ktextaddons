/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextinfo.h"

using namespace Qt::Literals::StringLiterals;

VoskSpeechToTextInfo::VoskSpeechToTextInfo() = default;

bool VoskSpeechToTextInfo::isValid() const
{
    return !mIdentifier.isEmpty() && !mUrl.isEmpty() && !mObsolete && isRecognitionModel();
}

bool VoskSpeechToTextInfo::isRecognitionModel() const
{
    // The upstream list also advertises "spk" models (speaker identification x-vectors, loaded
    // with vosk_spk_model_new()) and "tts" models (synthesis voices). vosk_model_new() cannot
    // load either, so they must never be offered as a language to transcribe with.
    return mType == "big"_L1 || mType == "small"_L1 || mType == "big-lgraph"_L1;
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
    return mIdentifier == other.mIdentifier && mLangText == other.mLangText && mMd5 == other.mMd5 && mVersion == other.mVersion && mUrl == other.mUrl
        && mSize == other.mSize && mObsolete == other.mObsolete && mType == other.mType && mName == other.mName;
}

void VoskSpeechToTextInfo::parse(const QJsonObject &obj)
{
    mLangText = obj["lang_text"_L1].toString();
    mIdentifier = obj["lang"_L1].toString();
    mMd5 = obj["md5"_L1].toString();
    mObsolete = obj["obsolete"_L1].toString() == "true"_L1;
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
