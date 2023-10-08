/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

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
    Q_REQUIRED_RESULT QString lang() const;
    void setLang(const QString &newLang);

    Q_REQUIRED_RESULT QString langText() const;
    void setLangText(const QString &newLangText);

    Q_REQUIRED_RESULT QString md5() const;
    void setMd5(const QString &newMd5);

    Q_REQUIRED_RESULT QString version() const;
    void setVersion(const QString &newVersion);

    Q_REQUIRED_RESULT QString url() const;
    void setUrl(const QString &newUrl);

    Q_REQUIRED_RESULT quint64 size() const;
    void setSize(quint64 newSize);

    Q_REQUIRED_RESULT bool obsolete() const;
    void setObsolete(bool newObsolete);

    Q_REQUIRED_RESULT bool operator==(const VoskSpeechToTextInfo &other) const;

    void parse(const QJsonObject &obj);

private:
    QString mLang;
    QString mLangText;
    QString mMd5;
    QString mVersion;
    QString mUrl;
    quint64 mSize = 0;
    bool mObsolete = false;
};
QDebug operator<<(QDebug d, const VoskSpeechToTextInfo &t);
Q_DECLARE_METATYPE(VoskSpeechToTextInfo)
Q_DECLARE_TYPEINFO(VoskSpeechToTextInfo, Q_MOVABLE_TYPE);
