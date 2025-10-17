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
    mFoundSearchCount = -1;
}

bool TextAutoGenerateSearchMessageSettings::canSearchMessage() const
{
    if (!mMessageModel) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << " Model is not defined. It's a bug";
        return false;
    }
    if (mFoundSearchCount == -1) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "mFoundSearchCount == -1 it's a bug";
        return false;
    }
    if (mCurrentMessageIdentifier.isEmpty()) {
        if (mMessageModel->isEmpty()) {
            return false;
        }
    }
    return true;
}

void TextAutoGenerateSearchMessageSettings::lastMessageUuid()
{
    const QByteArray msgUuid = mMessageModel->lastMessageUuid();
    if (msgUuid.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Invalid message. It's a bug";
    } else {
        mCurrentMessageIdentifier = msgUuid;
    }
}

int TextAutoGenerateSearchMessageSettings::foundSearchCount() const
{
    return mFoundSearchCount;
}

void TextAutoGenerateSearchMessageSettings::setFoundSearchCount(int newFoundSearchCount)
{
    mFoundSearchCount = newFoundSearchCount;
}

void TextAutoGenerateSearchMessageSettings::next()
{
    if (!canSearchMessage()) {
        return;
    }
    const QByteArray previousMessageIdentifier = mCurrentMessageIdentifier;
    if (mCurrentMessageIdentifier.isEmpty()) {
        lastMessageUuid();
        if (mCurrentMessageIdentifier.isEmpty()) {
            Q_EMIT updateNextPreviousButtons(false, false);
            return;
        }
    }
    const int storeCurrentSearchIndex = mCurrentSearchIndex;
    if (mCurrentSearchIndex == -1) {
        mCurrentSearchIndex = 0;
    } else {
        mCurrentSearchIndex++;
    }
    // qDebug() << " mCurrentSearchIndex " << mCurrentSearchIndex << " mMessageModel->message(mCurrentMessageIdentifier).numberOfTextSearched() "
    //          << mMessageModel->message(mCurrentMessageIdentifier).numberOfTextSearched();
    const auto hasSearchedString = [](const TextAutoGenerateMessage &msg) {
        return msg.numberOfTextSearched() > 0;
    };
    if (mCurrentSearchIndex >= mMessageModel->message(mCurrentMessageIdentifier).numberOfTextSearched()) {
        mCurrentSearchIndex = 0;
        auto msg = mMessageModel->findNextMessageAfter(mCurrentMessageIdentifier, hasSearchedString);
        if (msg.isValid()) {
            mCurrentMessageIdentifier = msg.uuid();
        } else {
            mCurrentSearchIndex = storeCurrentSearchIndex;
            Q_EMIT updateNextPreviousButtons(false, true);
            // Invalidate it.
            // clear();
            return;
        }
        Q_EMIT updateNextPreviousButtons((msg.numberOfTextSearched() > 0), true);
    } else {
        Q_EMIT updateNextPreviousButtons(((mMessageModel->message(mCurrentMessageIdentifier).numberOfTextSearched() > 0)
                                          && (mCurrentSearchIndex < mMessageModel->message(mCurrentMessageIdentifier).numberOfTextSearched() - 1))
                                             || mMessageModel->findNextMessageAfter(mCurrentMessageIdentifier, hasSearchedString).isValid(),
                                         true);
    }
    Q_EMIT refreshMessage(mCurrentMessageIdentifier, previousMessageIdentifier, mCurrentSearchIndex);
}

void TextAutoGenerateSearchMessageSettings::previous()
{
    if (!canSearchMessage()) {
        return;
    }
    const QByteArray previousMessageIdentifier = mCurrentMessageIdentifier;
    if (mCurrentMessageIdentifier.isEmpty()) {
        lastMessageUuid();
        if (mCurrentMessageIdentifier.isEmpty()) {
            Q_EMIT updateNextPreviousButtons(false, false);
            return;
        }
    }
    if (mCurrentSearchIndex == -1) {
        mCurrentSearchIndex = 0;
    } else {
        mCurrentSearchIndex--;
        if (mCurrentSearchIndex < 0) {
            const auto hasSearchedString = [](const TextAutoGenerateMessage &msg) {
                return msg.numberOfTextSearched() > 0;
            };

            auto msg = mMessageModel->findLastMessageBefore(mCurrentMessageIdentifier, hasSearchedString);
            if (msg.isValid()) {
                mCurrentMessageIdentifier = msg.uuid();
                mCurrentSearchIndex = msg.numberOfTextSearched() - 1;
            } else {
                // Keep in 0 index
                mCurrentSearchIndex = 0;
                // Invalidate it.
                // clear();
                Q_EMIT updateNextPreviousButtons(true, false);
                return;
            }
            Q_EMIT updateNextPreviousButtons((msg.numberOfTextSearched() > 0),
                                             (mCurrentSearchIndex > 0)
                                                 || mMessageModel->findLastMessageBefore(mCurrentMessageIdentifier, hasSearchedString).isValid());
        } else {
            Q_EMIT updateNextPreviousButtons((mFoundSearchCount > 1), true);
        }
    }
    Q_EMIT refreshMessage(mCurrentMessageIdentifier, previousMessageIdentifier, mCurrentSearchIndex);
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

#include "moc_textautogeneratesearchmessagesettings.cpp"
