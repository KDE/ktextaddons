/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistviewdelegate.h"
#include "core/textautogeneratechatmodel.h"
#include <QAbstractItemView>
#include <QHelpEvent>
#include <QToolTip>

using namespace TextAutogenerateText;
TextAutogenerateHistoryListViewDelegate::TextAutogenerateHistoryListViewDelegate(QObject *parent)
    : QItemDelegate{parent}
{
}

TextAutogenerateHistoryListViewDelegate::~TextAutogenerateHistoryListViewDelegate() = default;

bool TextAutogenerateHistoryListViewDelegate::helpEvent(QHelpEvent *helpEvent,
                                                        QAbstractItemView *view,
                                                        const QStyleOptionViewItem &option,
                                                        const QModelIndex &index)
{
    if (!index.isValid()) {
        return false;
    }
    if (helpEvent->type() == QEvent::ToolTip) {
        const QString subject = index.data(TextAutoGenerateChatModel::MessageRole).toString();
        const QString topic = index.data(TextAutoGenerateChatModel::TopicRole).toString();
        const QString formattedTooltip = topic.isEmpty() ? subject : topic;
        QToolTip::showText(helpEvent->globalPos(), formattedTooltip, view);
        return true;
    }
    return false;
}

#include "moc_textautogeneratehistorylistviewdelegate.cpp"
