/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchjob.h"
#include "textautogeneratemanager.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSearchJob::TextAutoGenerateSearchJob(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent)
    : QObject{parent}
    , mManager(manager)
{
}

TextAutoGenerateSearchJob::~TextAutoGenerateSearchJob() = default;

bool TextAutoGenerateSearchJob::canStart() const
{
    return mManager && !mSearchText.isEmpty();
}

void TextAutoGenerateSearchJob::start()
{
    if (!canStart()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to start job";
        deleteLater();
        return;
    }
    // TODO improve it.
    const QList<TextAutoGenerateSearchMessage> lst = mManager->searchTextInDatabase(mSearchText);
    Q_EMIT searchDone(lst);
    deleteLater();
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
