/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticonlistview.h"
using namespace Qt::Literals::StringLiterals;

#include "emojimodel.h"
#include "emoticonitemdelegate.h"

#include <TextEmoticonsCore/EmojiModel>
#include <TextEmoticonsCore/EmoticonUnicodeUtils>

#include <KLocalizedString>

#include <QKeyEvent>
#include <QMenu>

using namespace TextEmoticonsWidgets;
EmoticonListView::EmoticonListView(QWidget *parent)
    : QListView(parent)
{
    // setUniformItemSizes(true);
    setViewMode(QListView::IconMode);
    setDragEnabled(false);
    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setContextMenuPolicy(Qt::DefaultContextMenu);
    auto emoticonDelegate = new EmoticonItemDelegate(this);
    emoticonDelegate->setObjectName(u"emoticonDelegate"_s);
    setItemDelegate(emoticonDelegate);
    connect(this, &QListView::clicked, this, &EmoticonListView::selectEmoji);
}

EmoticonListView::~EmoticonListView() = default;

void EmoticonListView::selectEmoji(const QModelIndex &index)
{
    const QString emojiIdentifier = index.data(TextEmoticonsCore::EmojiModel::Identifier).toString();
    const QString emojiStr = index.data().toString();
    Q_EMIT emojiItemSelected(emojiStr, emojiIdentifier);
}

void EmoticonListView::keyPressEvent(QKeyEvent *event)
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

void EmoticonListView::wheelEvent(QWheelEvent *e)
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

void EmoticonListView::setFontSize(int newFontSize)
{
    if (newFontSize < 10 || newFontSize > 30) {
        return;
    }
    if (mFontSize != newFontSize) {
        mFontSize = newFontSize;
        applyFontSize();
    }
}

void EmoticonListView::applyFontSize()
{
    QFont f = font();
    f.setPointSize(mFontSize);
    f.setFamily(TextEmoticonsCore::EmoticonUnicodeUtils::emojiFontName());

    mRowSize = QFontMetrics(f).height();
    setFont(f);
}

bool EmoticonListView::isRecentView() const
{
    return mIsRecentView;
}

void EmoticonListView::setIsRecentView(bool newIsRecentView)
{
    mIsRecentView = newIsRecentView;
}

void EmoticonListView::contextMenuEvent(QContextMenuEvent *event)
{
    if (mIsRecentView) {
        if (model()->rowCount() > 0) {
            QMenu menu(this);
            auto clearRecent = new QAction(i18nc("@action", "Clear Recents"), &menu);
            connect(clearRecent, &QAction::triggered, this, &EmoticonListView::clearHistory);
            menu.addAction(clearRecent);
            menu.exec(event->globalPos());
        }
    }
}

#include "moc_emoticonlistview.cpp"
