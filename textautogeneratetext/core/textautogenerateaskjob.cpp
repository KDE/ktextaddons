/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaskjob.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateAskJob::TextAutoGenerateAskJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateAskJob::~TextAutoGenerateAskJob() = default;

bool TextAutoGenerateAskJob::canStart() const
{
    if (!mManager) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Manager is empty! It's a bug";
        return false;
    }
    if (mText.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Text is empty! It's a bug";
        return false;
    }
    // TODO
    return false;
}

void TextAutoGenerateAskJob::start()
{
    if (!canStart()) {
        deleteLater();
        return;
    }
    // TODO
    deleteLater();
}

TextAutoGenerateManager *TextAutoGenerateAskJob::manager() const
{
    return mManager;
}

void TextAutoGenerateAskJob::setManager(TextAutoGenerateManager *newManager)
{
    mManager = newManager;
}

QString TextAutoGenerateAskJob::text() const
{
    return mText;
}

void TextAutoGenerateAskJob::setText(const QString &newText)
{
    mText = newText;
}

#include "moc_textautogenerateaskjob.cpp"
