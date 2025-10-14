/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchmessagesettings.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSearchMessageSettings::TextAutoGenerateSearchMessageSettings(TextAutoGenerateMessagesModel *model, QObject *parent)
    : QObject(parent)
    , mMessageModel(model)
{
}

TextAutoGenerateSearchMessageSettings::~TextAutoGenerateSearchMessageSettings() = default;

void TextAutoGenerateSearchMessageSettings::clear()
{
    mCurrentMessageIdentifier.clear();
    mCurrentSearchIndex = -1;
    mNumberOfSearchReference = -1;
}

bool TextAutoGenerateSearchMessageSettings::canSearchMessage() const
{
    if (!mMessageModel) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << " Model is not defined. It's a bug";
        return false;
    }
    if (mCurrentMessageIdentifier.isEmpty()) {
        if (mMessageModel->isEmpty()) {
            return false;
        }
    }
    if (mNumberOfSearchReference == -1) {
        return false;
    }
    return true;
}

void TextAutoGenerateSearchMessageSettings::next()
{
    if (!canSearchMessage()) {
        return;
    }
    if (mCurrentMessageIdentifier.isEmpty()) {
        // TODO
    }
    if (mCurrentSearchIndex == -1) {
        mCurrentSearchIndex = 0;
    } else {
        mCurrentSearchIndex++;
        if (mCurrentSearchIndex >= mNumberOfSearchReference) {
            // TODO update     mCurrentMessageIdentifier
            mCurrentSearchIndex = 0;
        }
    }
    Q_EMIT refreshMessage(mCurrentMessageIdentifier, mCurrentSearchIndex);
}

void TextAutoGenerateSearchMessageSettings::previous()
{
    if (!canSearchMessage()) {
        return;
    }
    if (mCurrentMessageIdentifier.isEmpty()) {
        // TODO
    }
    if (mCurrentSearchIndex == -1) {
        mCurrentSearchIndex = 0;
    } else {
        mCurrentSearchIndex--;
        if (mCurrentSearchIndex < 0) {
            // TODO update     mCurrentMessageIdentifier
            // mCurrentSearchIndex = last index.
        }
    }
    Q_EMIT refreshMessage(mCurrentMessageIdentifier, mCurrentSearchIndex);
}

QByteArray TextAutoGenerateSearchMessageSettings::currentMessageIdentifier() const
{
    return mCurrentMessageIdentifier;
}

void TextAutoGenerateSearchMessageSettings::setCurrentMessageIdentifier(const QByteArray &newCurrentMessageIdentifier)
{
    mCurrentMessageIdentifier = newCurrentMessageIdentifier;
}

int TextAutoGenerateSearchMessageSettings::currentSearchIndex() const
{
    return mCurrentSearchIndex;
}

void TextAutoGenerateSearchMessageSettings::setCurrentSearchIndex(int newCurrentSearchIndex)
{
    mCurrentSearchIndex = newCurrentSearchIndex;
}

int TextAutoGenerateSearchMessageSettings::numberOfSearchReference() const
{
    return mNumberOfSearchReference;
}

void TextAutoGenerateSearchMessageSettings::setNumberOfSearchReference(int newNumberOfSearchReference)
{
    mNumberOfSearchReference = newNumberOfSearchReference;
}

#include "moc_textautogeneratesearchmessagesettings.cpp"
