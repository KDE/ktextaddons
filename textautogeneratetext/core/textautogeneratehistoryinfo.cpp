/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistoryinfo.h"

using namespace TextAutogenerateText;
TextAutoGenerateHistoryInfo::TextAutoGenerateHistoryInfo() = default;

TextAutoGenerateHistoryInfo::~TextAutoGenerateHistoryInfo() = default;

QDebug operator<<(QDebug d, const TextAutogenerateText::TextAutoGenerateHistoryInfo &t)
{
    d.space() << "subject:" << t.subject();
    d.space() << "datetime:" << t.dateTime();
    d.space() << "model" << t.model();
    d.space() << "engine" << t.engine();
    d.space() << "referenceUuid" << t.referenceUuid();
    return d;
}

QString TextAutoGenerateHistoryInfo::subject() const
{
    return mSubject;
}

void TextAutoGenerateHistoryInfo::setSubject(const QString &newSubject)
{
    mSubject = newSubject;
}

qint64 TextAutoGenerateHistoryInfo::dateTime() const
{
    return mDateTime;
}

void TextAutoGenerateHistoryInfo::setDateTime(qint64 newDateTime)
{
    mDateTime = newDateTime;
}

QString TextAutoGenerateHistoryInfo::model() const
{
    return mModel;
}

void TextAutoGenerateHistoryInfo::setModel(const QString &newModel)
{
    mModel = newModel;
}

QString TextAutoGenerateHistoryInfo::engine() const
{
    return mEngine;
}

void TextAutoGenerateHistoryInfo::setEngine(const QString &newEngine)
{
    mEngine = newEngine;
}

QByteArray TextAutoGenerateHistoryInfo::referenceUuid() const
{
    return mReferenceUuid;
}

void TextAutoGenerateHistoryInfo::setReferenceUuid(const QByteArray &newReferenceUuid)
{
    mReferenceUuid = newReferenceUuid;
}
