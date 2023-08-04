/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "translator.h"

Translator::Translator()
{
}

Translator::~Translator() = default;

void Translator::parse(const QJsonObject &obj)
{
    mUrl = obj[QStringLiteral("url")].toString();
    mModelName = obj[QStringLiteral("modelName")].toString();
    mShortName = obj[QStringLiteral("shortName")].toString();
    mCheckSum = obj[QStringLiteral("checksum")].toString();
    mRepository = obj[QStringLiteral("repository")].toString();
    mType = obj[QStringLiteral("type")].toString();
    mSource = obj[QStringLiteral("src")].toString();
    mTarget = obj[QStringLiteral("trg")].toString();
    mVersion = obj[QStringLiteral("version")].toInt(-1);
    mApi = obj[QStringLiteral("API")].toInt(-1);
}

QString Translator::shortName() const
{
    return mShortName;
}

bool Translator::operator==(const Translator &other) const
{
    return mShortName == other.mShortName && mModelName == other.mModelName && mSource == other.mSource && mTarget == other.mTarget
        && mCheckSum == other.mCheckSum && mRepository == other.mRepository && mUrl == other.mUrl && mType == other.mType && mVersion == other.mVersion
        && mApi == other.mApi;
}

void Translator::setShortName(const QString &newShortName)
{
    mShortName = newShortName;
}

QString Translator::modelName() const
{
    return mModelName;
}

void Translator::setModelName(const QString &newModelName)
{
    mModelName = newModelName;
}

QString Translator::source() const
{
    return mSource;
}

void Translator::setSource(const QString &newSource)
{
    mSource = newSource;
}

QString Translator::checkSum() const
{
    return mCheckSum;
}

void Translator::setCheckSum(const QString &newCheckSum)
{
    mCheckSum = newCheckSum;
}

QString Translator::target() const
{
    return mTarget;
}

void Translator::setTarget(const QString &newTarget)
{
    mTarget = newTarget;
}

int Translator::version() const
{
    return mVersion;
}

void Translator::setVersion(int newVersion)
{
    mVersion = newVersion;
}

int Translator::api() const
{
    return mApi;
}

void Translator::setApi(int newApi)
{
    mApi = newApi;
}

QString Translator::url() const
{
    return mUrl;
}

void Translator::setUrl(const QString &newUrl)
{
    mUrl = newUrl;
}

QString Translator::repository() const
{
    return mRepository;
}

void Translator::setRepository(const QString &newRepository)
{
    mRepository = newRepository;
}

QString Translator::type() const
{
    return mType;
}

void Translator::setType(const QString &newType)
{
    mType = newType;
}

bool Translator::isValid() const
{
    return !mUrl.isEmpty() && !mTarget.isEmpty() && !mSource.isEmpty();
}

QDebug operator<<(QDebug d, const Translator &t)
{
    d << "mShortName " << t.shortName();
    d << "mModelName " << t.modelName();
    d << "mSource " << t.source();
    d << "mTarget " << t.target();
    d << "mCheckSum " << t.checkSum();
    d << "mRepository " << t.repository();
    d << "mUrl " << t.url();
    d << "mType " << t.type();
    d << "mVersion " << t.version();
    d << "mApi " << t.api();
    return d;
}
