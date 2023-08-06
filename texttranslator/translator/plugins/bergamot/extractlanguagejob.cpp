/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "extractlanguagejob.h"
#include "libbergamot_debug.h"
#include <KLocalizedString>
#include <KTar>
#include <QDir>

ExtractLanguageJob::ExtractLanguageJob(QObject *parent)
    : QObject{parent}
{
}

ExtractLanguageJob::~ExtractLanguageJob() = default;

bool ExtractLanguageJob::canStart() const
{
    return !mSource.isEmpty() && !mTarget.isEmpty();
}

void ExtractLanguageJob::start()
{
    if (!canStart()) {
        qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to start ExtractLanguageJob";
        Q_EMIT errorText(i18n("Impossible to extract language"));
        deleteLater();
        return;
    }
    auto tar = new KTar(mSource);
    if (!tar->open(QIODevice::ReadOnly)) {
        qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to open temporary file" << mSource;
        deleteLater();
        return;
    }
    if (!QDir().mkpath(mTarget)) {
        qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "Impossible to create path" << mTarget;
        deleteLater();
        return;
    }
    qDebug() << " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx" << mTarget;
    delete tar;
    // TODO
    deleteLater();
}

QString ExtractLanguageJob::source() const
{
    return mSource;
}

void ExtractLanguageJob::setSource(const QString &newSource)
{
    mSource = newSource;
}

QString ExtractLanguageJob::target() const
{
    return mTarget;
}

void ExtractLanguageJob::setTarget(const QString &newTarget)
{
    mTarget = newTarget;
}

#include "moc_extractlanguagejob.cpp"
