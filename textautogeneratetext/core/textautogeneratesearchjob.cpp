/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchjob.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSearchJob::TextAutoGenerateSearchJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateSearchJob::~TextAutoGenerateSearchJob() = default;

bool TextAutoGenerateSearchJob::canStart() const
{
    return !mSearchText.isEmpty();
}

void TextAutoGenerateSearchJob::start()
{
    if (!canStart()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to start job";
        deleteLater();
        return;
    }
    // TODO
}

QString TextAutoGenerateSearchJob::searchText() const
{
    return mSearchText;
}

void TextAutoGenerateSearchJob::setSearchText(const QString &newSearchText)
{
    mSearchText = newSearchText;
}

#include "moc_textautogeneratesearchjob.cpp"
