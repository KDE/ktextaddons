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
    if (!mManager) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Manager is null! It's a bug";
        return false;
    }
    if (mSearchText.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Text is empty! It's a bug";
        return false;
    }
    return true;
}

void TextAutoGenerateSearchJob::start()
{
    if (!canStart()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to start job";
        deleteLater();
        return;
    }
    QList<TextAutoGenerateSearchMessage> messages = mManager->searchTextInDatabase(mSearchText.toLower());
    // Sort messages
    std::sort(messages.begin(), messages.end(), [](const TextAutoGenerateSearchMessage &left, const TextAutoGenerateSearchMessage &right) {
        if (left.dateTime() == right.dateTime()) {
            return true;
        }
        return left.dateTime() < right.dateTime();
    });

    Q_EMIT searchDone(messages);
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
