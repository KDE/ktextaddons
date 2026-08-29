/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratemessagewaitingansweranimation.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include "core/textautogeneratemanager.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateMessageWaitingAnswerAnimation::TextAutoGenerateMessageWaitingAnswerAnimation(const QByteArray &chatId,
                                                                                             TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                             QObject *parent)
    : TextAutoGenerateMessageWaitingAnswerAnimationBase{parent}
{
    if (manager) {
        if (auto messagesModel = manager->messagesModelFromChatId(chatId); messagesModel) {
            connect(messagesModel, &QAbstractItemModel::dataChanged, this, [this](const QModelIndex &topLeft, const QModelIndex &, const QList<int> &roles) {
                if (roles.contains(TextAutoGenerateMessagesModel::FinishedRole)) {
                    if (const bool inProgress = !topLeft.data(TextAutoGenerateMessagesModel::FinishedRole).toBool(); !inProgress) {
                        if (mModelIndex == topLeft) {
                            stopAndDelete();
                            Q_EMIT waitingAnswerDone(topLeft);
                        }
                    }
                }
            });
        }
    }
}

TextAutoGenerateMessageWaitingAnswerAnimation::~TextAutoGenerateMessageWaitingAnswerAnimation() = default;

#include "moc_textautogeneratemessagewaitingansweranimation.cpp"
