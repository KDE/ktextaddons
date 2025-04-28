/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistviewdelegate.h"
#include "core/textautogeneratechatmodel.h"
#include <QAbstractItemView>
#include <QHelpEvent>
#include <QLineEdit>
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
    Q_UNUSED(option);
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

QWidget *TextAutogenerateHistoryListViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void TextAutogenerateHistoryListViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if (lineEdit) {
        QString text = index.data(TextAutoGenerateChatModel::TopicRole).toString();
        if (text.isEmpty()) {
            text = index.data(TextAutoGenerateChatModel::MessageRole).toString();
        }
        lineEdit->setText(text);
    }
}

void TextAutogenerateHistoryListViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if (lineEdit) {
        model->setData(index, lineEdit->text(), TextAutoGenerateChatModel::TopicRole);
    }
}

void TextAutogenerateHistoryListViewDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

#include "moc_textautogeneratehistorylistviewdelegate.cpp"
