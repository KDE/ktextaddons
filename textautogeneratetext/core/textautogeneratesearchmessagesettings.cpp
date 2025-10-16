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
    return true;
}

void TextAutoGenerateSearchMessageSettings::lastMessageUuid()
{
    auto msg = mMessageModel->messages().constLast();
    if (msg.isValid()) {
        mCurrentMessageIdentifier = msg.uuid();
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Invalid message. It's a bug";
    }
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
    if (mCurrentSearchIndex >= mMessageModel->message(mCurrentMessageIdentifier).numberOfTextSearched()) {
        auto hasSearchedString = [](const TextAutoGenerateMessage &msg) {
            return msg.numberOfTextSearched() > 0;
        };

        mCurrentSearchIndex = 0;
        auto msg = mMessageModel->findNextMessageAfter(mCurrentMessageIdentifier, hasSearchedString);
        if (msg.isValid()) {
            mCurrentMessageIdentifier = msg.uuid();
        } else {
            mCurrentSearchIndex = storeCurrentSearchIndex;
            Q_EMIT updateNextPreviousButtons(false, true /*TODO ????*/);
            // Invalidate it.
            // clear();
            return;
        }
        Q_EMIT updateNextPreviousButtons((msg.numberOfTextSearched() > 0), true);
    } else {
        Q_EMIT updateNextPreviousButtons((mMessageModel->message(mCurrentMessageIdentifier).numberOfTextSearched() > 0), true);
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
            auto hasSearchedString = [](const TextAutoGenerateMessage &msg) {
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
                Q_EMIT updateNextPreviousButtons(true, false); // TODO verify it
                return;
            }
            Q_EMIT updateNextPreviousButtons((msg.numberOfTextSearched() > 0), true);
        } else {
            Q_EMIT updateNextPreviousButtons(true, true);
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
