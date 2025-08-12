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
#include <qapplication.h>
#include <qpainter.h>

using namespace TextAutoGenerateText;
TextAutoGenerateHistoryListViewDelegate::TextAutoGenerateHistoryListViewDelegate(QObject *parent)
    : QItemDelegate{parent}
{
}

TextAutoGenerateHistoryListViewDelegate::~TextAutoGenerateHistoryListViewDelegate() = default;

void TextAutoGenerateHistoryListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }

    const TextAutoGenerateHistoryListViewDelegate::Layout layout = doLayout(option, index);
    if (layout.isHeader) {
        QItemDelegate::paint(painter, option, index);
        return;
    }

    QStyleOptionViewItem opt(option);
    opt.showDecorationSelected = true;
    QApplication::style()->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter);

    painter->save();

    // Set the painter font
    painter->setFont(option.font);

    painter->setPen(option.palette.text().color());

#if 0
    const QRect displayRect(0,
                            option.rect.y() + padding,
                            option.rect.width() - xText - layout.unreadSize.width() - 2 * margin,
                            option.rect.height() - extraMargins);
#else
    const QRect displayRect = option.rect;
#endif

    drawDisplay(painter, opt, displayRect, layout.title); // this takes care of eliding if the text is too long
    painter->restore();
}

TextAutoGenerateHistoryListViewDelegate::Layout TextAutoGenerateHistoryListViewDelegate::doLayout(const QStyleOptionViewItem &option,
                                                                                                  const QModelIndex &index) const
{
    Q_UNUSED(option);
    TextAutoGenerateHistoryListViewDelegate::Layout layout;
    layout.isHeader = !index.parent().isValid();
    layout.title = index.data(TextAutoGenerateChatsModel::Title).toString();
    return layout;
}

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
