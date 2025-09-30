/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emojilistview.h"
using namespace Qt::Literals::StringLiterals;

#include "emojiitemdelegate.h"
#include "emojimodel.h"

#include <TextEmoticonsCore/EmojiModel>
#include <TextEmoticonsCore/EmoticonUnicodeUtils>

#include <KLocalizedString>

#include <QKeyEvent>
#include <QMenu>

using namespace TextEmoticonsWidgets;
EmojiListView::EmojiListView(QWidget *parent)
    : QListView(parent)
{
    // setUniformItemSizes(true);
    setViewMode(QListView::IconMode);
    setDragEnabled(false);
    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setContextMenuPolicy(Qt::DefaultContextMenu);
    auto emoticonDelegate = new EmojiItemDelegate(this);
    emoticonDelegate->setObjectName(u"emoticonDelegate"_s);
    setItemDelegate(emoticonDelegate);
    connect(this, &QListView::clicked, this, &EmojiListView::selectEmoji);
}

EmojiListView::~EmojiListView() = default;

void EmojiListView::selectEmoji(const QModelIndex &index)
{
    const QString emojiIdentifier = index.data(TextEmoticonsCore::EmojiModel::Identifier).toString();
    const QString emojiStr = index.data().toString();
    Q_EMIT emojiItemSelected(emojiStr, emojiIdentifier);
}

void EmojiListView::keyPressEvent(QKeyEvent *event)
{
    const bool isControlClicked = event->modifiers() & Qt::ControlModifier;
    int fontSize = mFontSize;
    if (isControlClicked) {
        if (event->key() == Qt::Key_Plus) {
            Q_EMIT fontSizeChanged(++fontSize);
        } else if (event->key() == Qt::Key_Minus) {
            Q_EMIT fontSizeChanged(--fontSize);
        }
    } else {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            auto index = currentIndex();
            if (index.isValid()) {
                selectEmoji(index);
            }
        }
        QListView::keyPressEvent(event);
    }
}

void EmojiListView::wheelEvent(QWheelEvent *e)
{
    int fontSize = mFontSize;
    if (e->modifiers() == Qt::ControlModifier) {
        const int y = e->angleDelta().y();
        if (y < 0) {
            Q_EMIT fontSizeChanged(--fontSize);
        } else if (y > 0) {
            Q_EMIT fontSizeChanged(++fontSize);
        } // else: y == 0 => horizontal scroll => do not handle
    } else {
        QListView::wheelEvent(e);
    }
}

void EmojiListView::setFontSize(int newFontSize)
{
    if (newFontSize < 10 || newFontSize > 30) {
        return;
    }
    if (mFontSize != newFontSize) {
        mFontSize = newFontSize;
        applyFontSize();
    }
}

void EmojiListView::applyFontSize()
{
    QFont f = font();
    f.setPointSize(mFontSize);
    f.setFamily(TextEmoticonsCore::EmoticonUnicodeUtils::emojiFontName());

    mRowSize = QFontMetrics(f).height();
    setFont(f);
}

bool EmojiListView::isRecentView() const
{
    return mIsRecentView;
}

void EmojiListView::setIsRecentView(bool newIsRecentView)
{
    mIsRecentView = newIsRecentView;
}

void EmojiListView::contextMenuEvent(QContextMenuEvent *event)
{
    if (mIsRecentView) {
        if (model()->rowCount() > 0) {
            QMenu menu(this);
            auto clearRecent = new QAction(i18nc("@action", "Clear Recents"), &menu);
            connect(clearRecent, &QAction::triggered, this, &EmojiListView::clearHistory);
            menu.addAction(clearRecent);
            menu.exec(event->globalPos());
        }
    }
}

#include "moc_emojilistview.cpp"
