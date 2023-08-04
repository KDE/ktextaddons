/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "libbergamot_private_export.h"
#include <QJsonObject>

class LIBBERGAMOT_TESTS_EXPORT Translator
{
public:
    Translator();
    ~Translator();

    void parse(const QJsonObject &obj);

    Q_REQUIRED_RESULT QString shortName() const;
    void setShortName(const QString &newShortName);

    Q_REQUIRED_RESULT QString modelName() const;
    void setModelName(const QString &newModelName);

    Q_REQUIRED_RESULT QString source() const;
    void setSource(const QString &newSource);

    Q_REQUIRED_RESULT QString checkSum() const;
    void setCheckSum(const QString &newCheckSum);

    Q_REQUIRED_RESULT QString target() const;
    void setTarget(const QString &newTarget);

    Q_REQUIRED_RESULT int version() const;
    void setVersion(int newVersion);

    Q_REQUIRED_RESULT int api() const;
    void setApi(int newApi);

    Q_REQUIRED_RESULT QString url() const;
    void setUrl(const QString &newUrl);

    Q_REQUIRED_RESULT QString repository() const;
    void setRepository(const QString &newRepository);

    Q_REQUIRED_RESULT QString type() const;
    void setType(const QString &newType);

    Q_REQUIRED_RESULT bool isValid() const;

private:
    QString mShortName;
    QString mModelName;
    QString mSource;
    QString mTarget;
    QString mCheckSum;
    QString mRepository;
    QString mUrl;
    QString mType;
    int mVersion = -1;
    int mApi = -1;
};
LIBBERGAMOT_EXPORT QDebug operator<<(QDebug d, const Translator &t);
Q_DECLARE_TYPEINFO(Translator, Q_MOVABLE_TYPE);
