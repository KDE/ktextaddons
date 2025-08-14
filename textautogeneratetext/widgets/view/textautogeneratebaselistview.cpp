/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogeneratebaselistview.h"
using namespace Qt::Literals::StringLiterals;

#include "widgets/view/textautogeneratelistviewbasedelegate.h"
#include <KLocalizedString>
#include <QApplication>
#include <QClipboard>
#include <QMenu>
#include <QMouseEvent>
#include <QScrollBar>
#include <TextAutoGenerateText/TextAutoGenerateManager>
#include <TextAutoGenerateText/TextAutoGeneratePluginText>
#include <TextAutoGenerateText/TextAutoGeneratePluginTextInterface>
#include <TextAutoGenerateText/TextAutoGeneratePluginTextManager>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateBaseListView::TextAutoGenerateBaseListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QListView(parent)
    , mManager(manager)
{
    if (mManager) {
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::fontSizeChanged, this, &TextAutoGenerateBaseListView::slotFontChanged);
    }

    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // nicer in case of huge messages
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWordWrap(true); // so that the delegate sizeHint is called again when the width changes

    setFocusPolicy(Qt::NoFocus);
    scrollToBottom();
    setMouseTracking(true);
    // Connect to rangeChanged rather than rowsInserted/rowsRemoved/modelReset.
    // This way it also catches the case of an item changing height (e.g. after async image loading)
    connect(verticalScrollBar(), &QScrollBar::rangeChanged, this, &TextAutoGenerateBaseListView::maybeScrollToBottom);
    QList<TextAutoGeneratePluginText *> plugins = TextAutoGeneratePluginTextManager::self()->pluginsList();
    if (plugins.count() > 1) {
        std::sort(plugins.begin(), plugins.end(), [](TextAutoGeneratePluginText *left, TextAutoGeneratePluginText *right) {
            return left->order() < right->order();
        });
    }
    for (TextAutoGeneratePluginText *plugin : plugins) {
        if (plugin->enabled()) {
            /*
            connect(plugin, &TextAutoGeneratePluginText::errorMessage, this, &MessageListViewBase::errorMessage);
            connect(plugin, &TextAutoGeneratePluginText::successMessage, this, &MessageListViewBase::successMessage);
*/
            auto interface = plugin->createInterface(this);
            mPluginTextInterface.append(interface);
        }
    }
}

TextAutoGenerateBaseListView::~TextAutoGenerateBaseListView()
{
    qDeleteAll(mPluginTextInterface);
}

void TextAutoGenerateBaseListView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    const QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        auto copyAction =
            new QAction(QIcon::fromTheme(u"edit-copy"_s), mDelegate->hasSelection() ? i18nc("@action", "Copy Selection") : i18nc("@action", "Copy"), &menu);
        copyAction->setShortcut(QKeySequence::Copy);
        connect(copyAction, &QAction::triggered, this, [index, this]() {
            slotCopyMessage(index);
        });
        menu.addAction(copyAction);
        menu.addSeparator();

        auto copyUrlAction = [&]() -> QAction * {
            const QString url = mDelegate->urlAt(index, viewport()->mapFromGlobal(event->globalPos()));
            qDebug() << " url " << url;
            if (url.isEmpty())
                return nullptr;
            auto action = new QAction(QIcon::fromTheme(u"edit-copy"_s), i18nc("@action", "Copy URL"), &menu);
            connect(action, &QAction::triggered, this, [url]() {
                QGuiApplication::clipboard()->setText(url);
            });
            return action;
        }();

        if (copyUrlAction) {
            menu.addAction(copyUrlAction);
            menu.addSeparator();
        }

        auto selectAllAction = new QAction(QIcon::fromTheme(u"edit-select-all"_s), i18nc("@action", "Select All"), &menu);
        connect(selectAllAction, &QAction::triggered, this, [this, index]() {
            slotSelectAll(index);
        });
        selectAllAction->setShortcut(QKeySequence::SelectAll);
        menu.addAction(selectAllAction);

        if (mDelegate->hasSelection()) {
            menu.addSeparator();
            for (TextAutoGeneratePluginTextInterface *interface : std::as_const(mPluginTextInterface)) {
                interface->setSelectedText(mDelegate->selectedText());
                interface->addAction(&menu);
            }
        }
        menu.exec(event->globalPos());
    }
}

void TextAutoGenerateBaseListView::slotFontChanged()
{
    mDelegate->clearCache();
}

void TextAutoGenerateBaseListView::slotSelectAll(const QModelIndex &index)
{
    mDelegate->selectAll(listViewOptions(), index);
}

void TextAutoGenerateBaseListView::resizeEvent(QResizeEvent *ev)
{
    QListView::resizeEvent(ev);

    // Fix not being really at bottom when the view gets reduced by the header widget becoming taller
    checkIfAtBottom();
    maybeScrollToBottom(); // this forces a layout in QAIV, which then changes the vbar max value
    updateVerticalPageStep();
    mDelegate->clearSizeHintCache();
}

QString TextAutoGenerateBaseListView::selectedText(const QModelIndex &index) const
{
    QString message = mDelegate->selectedText();
    if (message.isEmpty()) {
        if (!index.isValid()) {
            return {};
        }
        message = originalMessage(index);
    }
    return message;
}

void TextAutoGenerateBaseListView::slotCopyMessage(const QModelIndex &index)
{
    const QString messageText = selectedText(index);
    if (messageText.isEmpty()) {
        return;
    }
    QClipboard *clip = QApplication::clipboard();
    clip->setText(messageText, QClipboard::Clipboard);
    clip->setText(messageText, QClipboard::Selection);
}

QStyleOptionViewItem TextAutoGenerateBaseListView::listViewOptions() const
{
    QStyleOptionViewItem option;
    initViewItemOption(&option);
    return option;
}

void TextAutoGenerateBaseListView::checkIfAtBottom()
{
    auto *vbar = verticalScrollBar();
    mAtBottom = vbar->value() == vbar->maximum();
}

void TextAutoGenerateBaseListView::maybeScrollToBottom()
{
    if (mAtBottom) {
        scrollToBottom();
    }
}

void TextAutoGenerateBaseListView::updateVerticalPageStep()
{
    verticalScrollBar()->setPageStep(viewport()->height() * 3 / 4);
}

bool TextAutoGenerateBaseListView::maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return mDelegate->maybeStartDrag(event, option, index);
}

bool TextAutoGenerateBaseListView::mouseEvent(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return mDelegate->mouseEvent(event, option, index);
}

void TextAutoGenerateBaseListView::mouseReleaseEvent(QMouseEvent *event)
{
    handleMouseEvent(event);
}

void TextAutoGenerateBaseListView::mouseDoubleClickEvent(QMouseEvent *event)
{
    handleMouseEvent(event);
}

void TextAutoGenerateBaseListView::mousePressEvent(QMouseEvent *event)
{
    mPressedPosition = event->pos();
    handleMouseEvent(event);
}

void TextAutoGenerateBaseListView::mouseMoveEvent(QMouseEvent *event)
{
    // Drag support
    const int distance = (event->pos() - mPressedPosition).manhattanLength();
    if (distance > QApplication::startDragDistance()) {
        mPressedPosition = {};
        const QPersistentModelIndex index = indexAt(event->pos());
        if (index.isValid()) {
            QStyleOptionViewItem options = listViewOptions();
            options.rect = visualRect(index);
            if (maybeStartDrag(event, options, index)) {
                return;
            }
        }
    }
    handleMouseEvent(event);
}

void TextAutoGenerateBaseListView::handleMouseEvent(QMouseEvent *event)
{
    const QPersistentModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        mCurrentIndex = index;
        QStyleOptionViewItem options = listViewOptions();
        options.rect = visualRect(mCurrentIndex);
        if (mouseEvent(event, options, mCurrentIndex)) {
            update(mCurrentIndex);
        }
    }
}

#include "moc_textautogeneratebaselistview.cpp"
