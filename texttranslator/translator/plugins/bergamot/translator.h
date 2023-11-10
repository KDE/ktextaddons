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

    void parse(const QJsonObject &obj, bool remote = true);

    [[nodiscard]] QString shortName() const;
    void setShortName(const QString &newShortName);

    [[nodiscard]] QString modelName() const;
    void setModelName(const QString &newModelName);

    [[nodiscard]] QString source() const;
    void setSource(const QString &newSource);

    [[nodiscard]] QString checkSum() const;
    void setCheckSum(const QString &newCheckSum);

    [[nodiscard]] QString target() const;
    void setTarget(const QString &newTarget);

    [[nodiscard]] int version() const;
    void setVersion(int newVersion);

    [[nodiscard]] int api() const;
    void setApi(int newApi);

    [[nodiscard]] QString url() const;
    void setUrl(const QString &newUrl);

    [[nodiscard]] QString repository() const;
    void setRepository(const QString &newRepository);

    [[nodiscard]] QString type() const;
    void setType(const QString &newType);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] bool operator==(const Translator &other) const;

    [[nodiscard]] bool remote() const;
    void setRemote(bool newRemote);

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
    bool mRemote = true;
};
LIBBERGAMOT_EXPORT QDebug operator<<(QDebug d, const Translator &t);
Q_DECLARE_METATYPE(Translator)
Q_DECLARE_TYPEINFO(Translator, Q_MOVABLE_TYPE);
