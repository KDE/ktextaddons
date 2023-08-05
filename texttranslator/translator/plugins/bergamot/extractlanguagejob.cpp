/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "extractlanguagejob.h"
#include "bergamotengineutils.h"
#include "libbergamot_debug.h"
#include <KLocalizedString>
#include <KTar>

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
