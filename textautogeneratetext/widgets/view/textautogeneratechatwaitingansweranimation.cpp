/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratechatwaitingansweranimation.h"
#include "core/models/textautogeneratechatsmodel.h"
#include "core/textautogeneratemanager.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateChatWaitingAnswerAnimation::TextAutoGenerateChatWaitingAnswerAnimation(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent)
    : TextAutoGenerateMessageWaitingAnswerAnimationBase{parent}
{
    if (manager) {
        auto chatsModel = manager->textAutoGenerateChatsModel();
        if (chatsModel) {
            connect(chatsModel, &QAbstractItemModel::dataChanged, this, [this](const QModelIndex &topLeft, const QModelIndex &, const QList<int> &roles) {
                if (roles.contains(TextAutoGenerateChatsModel::InProgress)) {
                    const bool inProgress = topLeft.data(TextAutoGenerateChatsModel::InProgress).toBool();
                    if (!inProgress) {
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

TextAutoGenerateChatWaitingAnswerAnimation::~TextAutoGenerateChatWaitingAnswerAnimation() = default;

#include "moc_textautogeneratechatwaitingansweranimation.cpp"
