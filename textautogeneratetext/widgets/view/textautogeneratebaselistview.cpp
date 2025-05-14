/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogeneratebaselistview.h"
#include <QApplication>
#include <QClipboard>

using namespace TextAutoGenerateText;
TextAutoGenerateBaseListView::TextAutoGenerateBaseListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QListView(parent)
    , mManager(manager)
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // nicer in case of huge messages
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWordWrap(true); // so that the delegate sizeHint is called again when the width changes

    setFocusPolicy(Qt::NoFocus);
    scrollToBottom();
    setMouseTracking(true);
}

TextAutoGenerateBaseListView::~TextAutoGenerateBaseListView() = default;

void TextAutoGenerateBaseListView::slotCopyMessage(const QModelIndex &index)
{
    const QString currentValue = index.data().toString();
    QClipboard *clip = QApplication::clipboard();
    clip->setText(currentValue, QClipboard::Clipboard);
    clip->setText(currentValue, QClipboard::Selection);
}

QStyleOptionViewItem TextAutoGenerateBaseListView::listViewOptions() const
{
    QStyleOptionViewItem option;
    initViewItemOption(&option);
    return option;
}

#include "moc_textautogeneratebaselistview.cpp"
