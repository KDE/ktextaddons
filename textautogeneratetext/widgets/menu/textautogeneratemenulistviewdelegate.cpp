/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratemenulistviewdelegate.h"
#include "textautogeneratemenumodel.h"
#include <QLineEdit>
using namespace TextAutoGenerateText;
TextAutoGenerateMenuListViewDelegate::TextAutoGenerateMenuListViewDelegate(QObject *parent)
    : QItemDelegate{parent}
{
}

TextAutoGenerateMenuListViewDelegate::~TextAutoGenerateMenuListViewDelegate() = default;

QWidget *TextAutoGenerateMenuListViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void TextAutoGenerateMenuListViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if (lineEdit) {
        const QString text = index.data(TextAutoGenerateMenuModel::TextRole).toString();
        lineEdit->setText(text);
    }
}

void TextAutoGenerateMenuListViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if (lineEdit) {
        if (!lineEdit->text().trimmed().isEmpty()) {
            model->setData(index, lineEdit->text(), TextAutoGenerateMenuModel::TextRole);
        }
    }
}

void TextAutoGenerateMenuListViewDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

#include "moc_textautogeneratemenulistviewdelegate.cpp"
