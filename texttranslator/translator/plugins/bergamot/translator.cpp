/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "translator.h"

Translator::Translator() = default;

Translator::~Translator() = default;

void Translator::parse(const QJsonObject &obj, bool remote)
{
    mUrl = obj[QLatin1String("url")].toString();
    mModelName = obj[QLatin1String("modelName")].toString();
    mShortName = obj[QLatin1String("shortName")].toString();
    mCheckSum = obj[QLatin1String("checksum")].toString();
    mRepository = obj[QLatin1String("repository")].toString();
    mType = obj[QLatin1String("type")].toString();
    mSource = obj[QLatin1String("src")].toString();
    mTarget = obj[QLatin1String("trg")].toString();
    mVersion = obj[QLatin1String("version")].toInt(-1);
    mApi = obj[QLatin1String("API")].toInt(-1);
    mRemote = remote;
}

QString Translator::shortName() const
{
    return mShortName;
}

bool Translator::operator==(const Translator &other) const
{
    return mShortName == other.mShortName && mModelName == other.mModelName && mSource == other.mSource && mTarget == other.mTarget
        && mCheckSum == other.mCheckSum && mRepository == other.mRepository && mUrl == other.mUrl && mType == other.mType && mVersion == other.mVersion
        && mApi == other.mApi && mRemote == other.mRemote;
}

bool Translator::remote() const
{
    return mRemote;
}

void Translator::setRemote(bool newRemote)
{
    mRemote = newRemote;
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
    if (mRemote) {
        return !mUrl.isEmpty() && !mTarget.isEmpty() && !mSource.isEmpty();
    } else {
        return !mTarget.isEmpty() && !mSource.isEmpty();
    }
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
    d << "mRemote " << t.remote();
    return d;
}
