/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistviewdelegate.h"
#include "core/models/textautogeneratechatsmodel.h"
#include <QAbstractItemView>
#include <QHelpEvent>
#include <QLineEdit>
#include <QToolTip>

using namespace TextAutoGenerateText;
TextAutoGenerateHistoryListViewDelegate::TextAutoGenerateHistoryListViewDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

TextAutoGenerateHistoryListViewDelegate::~TextAutoGenerateHistoryListViewDelegate() = default;

bool TextAutoGenerateHistoryListViewDelegate::helpEvent(QHelpEvent *helpEvent,
                                                        QAbstractItemView *view,
                                                        const QStyleOptionViewItem &option,
                                                        const QModelIndex &index)
{
    Q_UNUSED(option);
    if (!index.isValid()) {
        return false;
    }
    if (helpEvent->type() == QEvent::ToolTip) {
        const QString subject = index.data(TextAutoGenerateChatsModel::Title).toString();
        QToolTip::showText(helpEvent->globalPos(), subject, view);
        return true;
    }
    return false;
}

QWidget *TextAutoGenerateHistoryListViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void TextAutoGenerateHistoryListViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if (lineEdit) {
        const QString text = index.data(TextAutoGenerateChatsModel::Title).toString();
        lineEdit->setText(text);
    }
}

void TextAutoGenerateHistoryListViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if (lineEdit) {
        model->setData(index, lineEdit->text(), TextAutoGenerateChatsModel::Title);
    }
}

void TextAutoGenerateHistoryListViewDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

#include "moc_textautogeneratehistorylistviewdelegate.cpp"
