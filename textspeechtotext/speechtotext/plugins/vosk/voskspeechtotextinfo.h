/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libvoskspeechtotext_export.h"
#include <QJsonObject>
#include <QString>

class LIBVOSKSPEECHTOTEXT_EXPORT VoskSpeechToTextInfo
{
public:
    VoskSpeechToTextInfo();
    ~VoskSpeechToTextInfo();

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] QString identifier() const;
    void setIdentifier(const QString &newLang);

    [[nodiscard]] QString langText() const;
    void setLangText(const QString &newLangText);

    [[nodiscard]] QString md5() const;
    void setMd5(const QString &newMd5);

    [[nodiscard]] QString version() const;
    void setVersion(const QString &newVersion);

    [[nodiscard]] QString url() const;
    void setUrl(const QString &newUrl);

    [[nodiscard]] quint64 size() const;
    void setSize(quint64 newSize);

    [[nodiscard]] bool obsolete() const;
    void setObsolete(bool newObsolete);

    [[nodiscard]] bool operator==(const VoskSpeechToTextInfo &other) const;

    void parse(const QJsonObject &obj);

    [[nodiscard]] QString type() const;
    void setType(const QString &newType);

    QString name() const;
    void setName(const QString &newName);

private:
    QString mName;
    QString mType;
    QString mIdentifier;
    QString mLangText;
    QString mMd5;
    QString mVersion;
    QString mUrl;
    quint64 mSize = 0;
    bool mObsolete = false;
};
LIBVOSKSPEECHTOTEXT_EXPORT QDebug operator<<(QDebug d, const VoskSpeechToTextInfo &t);
Q_DECLARE_METATYPE(VoskSpeechToTextInfo)
Q_DECLARE_TYPEINFO(VoskSpeechToTextInfo, Q_MOVABLE_TYPE);
