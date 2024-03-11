/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtextbrowser.h"

#include "widgets/textmessageindicator.h"
#include <KCursor>
#include <KLocalizedString>
#include <KMessageBox>
#include <KStandardAction>
#include <KStandardGuiItem>
#include <QIcon>

#include "config-textcustomeditor.h"
#if HAVE_KTEXTADDONS_KIO_SUPPORT
#include <KIO/KUriFilterSearchProviderActions>
#endif
#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
#include <TextEditTextToSpeech/TextToSpeech>
#endif

#include <KColorScheme>
#include <QApplication>
#include <QClipboard>
#include <QContextMenuEvent>
#include <QMenu>
#include <QScrollBar>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocumentFragment>

using namespace TextCustomEditor;
class Q_DECL_HIDDEN RichTextBrowser::RichTextBrowserPrivate
{
public:
    RichTextBrowserPrivate(RichTextBrowser *qq)
        : q(qq)
        , textIndicator(new TextCustomEditor::TextMessageIndicator(q))
#if HAVE_KTEXTADDONS_KIO_SUPPORT
        , webshortcutMenuManager(new KIO::KUriFilterSearchProviderActions(q))
#endif
    {
        supportFeatures |= RichTextBrowser::Search;
        supportFeatures |= RichTextBrowser::TextToSpeech;
#if HAVE_KTEXTADDONS_KIO_SUPPORT
        supportFeatures |= RichTextBrowser::AllowWebShortcut;
#endif

        // Workaround QTextEdit behavior: if the cursor points right after the link
        // and start typing, the char format is kept. If user wants to write normal
        // text right after the link, the only way is to move cursor at the next character
        // (say for "<a>text</a>more text" the character has to be before letter "o"!)
        // It's impossible if the whole document ends with a link.
        // The same happens when text starts with a link: it's impossible to write normal text before it.
        QObject::connect(q, &RichTextBrowser::cursorPositionChanged, q, [this]() {
            QTextCursor c = q->textCursor();
            if (c.charFormat().isAnchor() && !c.hasSelection()) {
                QTextCharFormat fmt;
                // If we are at block start or end (and at anchor), we just set the "default" format
                if (!c.atBlockEnd() && !c.atBlockStart() && !c.hasSelection()) {
                    QTextCursor probe = c;
                    // Otherwise, if the next character is not a link, we just grab it's format
                    probe.movePosition(QTextCursor::NextCharacter);
                    if (!probe.charFormat().isAnchor()) {
                        fmt = probe.charFormat();
                    }
                }
                c.setCharFormat(fmt);
                q->setTextCursor(c);
            }
        });
    }

    ~RichTextBrowserPrivate()
    {
    }

    RichTextBrowser *const q;
    TextCustomEditor::TextMessageIndicator *const textIndicator;
    QTextDocumentFragment originalDoc;
#if HAVE_KTEXTADDONS_KIO_SUPPORT
    KIO::KUriFilterSearchProviderActions *const webshortcutMenuManager;
#endif
    RichTextBrowser::SupportFeatures supportFeatures;
    QColor mReadOnlyBackgroundColor;
    int mInitialFontSize;
    bool customPalette = false;
};

RichTextBrowser::RichTextBrowser(QWidget *parent)
    : QTextBrowser(parent)
    , d(new RichTextBrowserPrivate(this))
{
    setAcceptRichText(true);
    KCursor::setAutoHideCursor(this, true, false);
    d->mInitialFontSize = font().pointSize();
    regenerateColorScheme();
}

RichTextBrowser::~RichTextBrowser() = default;

void RichTextBrowser::regenerateColorScheme()
{
    d->mReadOnlyBackgroundColor = KColorScheme(QPalette::Disabled, KColorScheme::View).background().color();
    updateReadOnlyColor();
}

void RichTextBrowser::setDefaultFontSize(int val)
{
    d->mInitialFontSize = val;
    slotZoomReset();
}

void RichTextBrowser::slotDisplayMessageIndicator(const QString &message)
{
    d->textIndicator->display(message);
}

void RichTextBrowser::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *popup = mousePopupMenu(event->pos());
    if (popup) {
        popup->exec(event->globalPos());
        delete popup;
    }
}

QMenu *RichTextBrowser::mousePopupMenu(QPoint pos)
{
    QMenu *popup = createStandardContextMenu();
    if (popup) {
        const bool emptyDocument = document()->isEmpty();
        if (!isReadOnly()) {
            const QList<QAction *> actionList = popup->actions();
            enum { UndoAct, RedoAct, CutAct, CopyAct, PasteAct, ClearAct, SelectAllAct, NCountActs };
            QAction *separatorAction = nullptr;
            const int idx = actionList.indexOf(actionList[SelectAllAct]) + 1;
            if (idx < actionList.count()) {
                separatorAction = actionList.at(idx);
            }
            if (separatorAction) {
                QAction *clearAllAction = KStandardAction::clear(this, &RichTextBrowser::slotUndoableClear, popup);
                if (emptyDocument) {
                    clearAllAction->setEnabled(false);
                }
                popup->insertAction(separatorAction, clearAllAction);
            }
        }
        if (searchSupport()) {
            popup->addSeparator();
            QAction *findAction = KStandardAction::find(this, &RichTextBrowser::findText, popup);
            popup->addAction(findAction);
            if (emptyDocument) {
                findAction->setEnabled(false);
            }
        } else {
            popup->addSeparator();
        }

#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
        if (!emptyDocument) {
            QAction *speakAction = popup->addAction(i18n("Speak Text"));
            speakAction->setIcon(QIcon::fromTheme(QStringLiteral("preferences-desktop-text-to-speech")));
            connect(speakAction, &QAction::triggered, this, &RichTextBrowser::slotSpeakText);
        }
#endif
#if HAVE_KTEXTADDONS_KIO_SUPPORT
        if (webShortcutSupport() && textCursor().hasSelection()) {
            popup->addSeparator();
            const QString selectedText = textCursor().selectedText();
            d->webshortcutMenuManager->setSelectedText(selectedText);
            d->webshortcutMenuManager->addWebShortcutsToMenu(popup);
        }
#endif
        addExtraMenuEntry(popup, pos);
        return popup;
    }
    return nullptr;
}

void RichTextBrowser::slotSpeakText()
{
    QString text;
    if (textCursor().hasSelection()) {
        text = textCursor().selectedText();
    } else {
        text = toPlainText();
    }
    Q_EMIT say(text);
}

void RichTextBrowser::setWebShortcutSupport(bool b)
{
#if HAVE_KTEXTADDONS_KIO_SUPPORT
    if (b) {
        d->supportFeatures |= AllowWebShortcut;
    } else {
        d->supportFeatures = (d->supportFeatures & ~AllowWebShortcut);
    }
#else
    Q_UNUSED(b);
#endif
}

bool RichTextBrowser::webShortcutSupport() const
{
#if HAVE_KTEXTADDONS_KIO_SUPPORT
    return d->supportFeatures & AllowWebShortcut;
#else
    return false;
#endif
}

void RichTextBrowser::setSearchSupport(bool b)
{
    if (b) {
        d->supportFeatures |= Search;
    } else {
        d->supportFeatures = (d->supportFeatures & ~Search);
    }
}

bool RichTextBrowser::searchSupport() const
{
    return d->supportFeatures & Search;
}

void RichTextBrowser::setTextToSpeechSupport(bool b)
{
    if (b) {
        d->supportFeatures |= TextToSpeech;
    } else {
        d->supportFeatures = (d->supportFeatures & ~TextToSpeech);
    }
}

bool RichTextBrowser::textToSpeechSupport() const
{
    return d->supportFeatures & TextToSpeech;
}

void RichTextBrowser::addExtraMenuEntry(QMenu *menu, QPoint pos)
{
    Q_UNUSED(menu)
    Q_UNUSED(pos)
}

void RichTextBrowser::slotUndoableClear()
{
    QTextCursor cursor = textCursor();
    cursor.beginEditBlock();
    cursor.movePosition(QTextCursor::Start);
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.endEditBlock();
}

void RichTextBrowser::updateReadOnlyColor()
{
    if (isReadOnly()) {
        QPalette p = palette();
        p.setColor(QPalette::Base, d->mReadOnlyBackgroundColor);
        p.setColor(QPalette::Window, d->mReadOnlyBackgroundColor);
        setPalette(p);
    }
}

static void richTextDeleteWord(QTextCursor cursor, QTextCursor::MoveOperation op)
{
    cursor.clearSelection();
    cursor.movePosition(op, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
}

void RichTextBrowser::deleteWordBack()
{
    richTextDeleteWord(textCursor(), QTextCursor::PreviousWord);
}

void RichTextBrowser::deleteWordForward()
{
    richTextDeleteWord(textCursor(), QTextCursor::WordRight);
}

bool RichTextBrowser::event(QEvent *ev)
{
    if (ev->type() == QEvent::ShortcutOverride) {
        auto e = static_cast<QKeyEvent *>(ev);
        if (overrideShortcut(e)) {
            e->accept();
            return true;
        }
    } else if (ev->type() == QEvent::ApplicationPaletteChange) {
        regenerateColorScheme();
    }
    return QTextEdit::event(ev);
}

void RichTextBrowser::wheelEvent(QWheelEvent *event)
{
    if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
        const int angleDeltaY{event->angleDelta().y()};
        if (angleDeltaY > 0) {
            zoomIn();
        } else if (angleDeltaY < 0) {
            zoomOut();
        }
        event->accept();
        return;
    }
    QTextEdit::wheelEvent(event);
}

bool RichTextBrowser::handleShortcut(QKeyEvent *event)
{
    const int key = event->key() | event->modifiers();

    if (KStandardShortcut::copy().contains(key)) {
        copy();
        return true;
    } else if (KStandardShortcut::paste().contains(key)) {
        paste();
        return true;
    } else if (KStandardShortcut::cut().contains(key)) {
        cut();
        return true;
    } else if (KStandardShortcut::undo().contains(key)) {
        if (!isReadOnly()) {
            undo();
        }
        return true;
    } else if (KStandardShortcut::redo().contains(key)) {
        if (!isReadOnly()) {
            redo();
        }
        return true;
    } else if (KStandardShortcut::deleteWordBack().contains(key)) {
        if (!isReadOnly()) {
            deleteWordBack();
        }
        return true;
    } else if (KStandardShortcut::deleteWordForward().contains(key)) {
        if (!isReadOnly()) {
            deleteWordForward();
        }
        return true;
    } else if (KStandardShortcut::backwardWord().contains(key)) {
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::PreviousWord);
        setTextCursor(cursor);
        return true;
    } else if (KStandardShortcut::forwardWord().contains(key)) {
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::NextWord);
        setTextCursor(cursor);
        return true;
    } else if (KStandardShortcut::next().contains(key)) {
        QTextCursor cursor = textCursor();
        bool moved = false;
        qreal lastY = cursorRect(cursor).bottom();
        qreal distance = 0;
        do {
            qreal y = cursorRect(cursor).bottom();
            distance += qAbs(y - lastY);
            lastY = y;
            moved = cursor.movePosition(QTextCursor::Down);
        } while (moved && distance < viewport()->height());

        if (moved) {
            cursor.movePosition(QTextCursor::Up);
            verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepAdd);
        }
        setTextCursor(cursor);
        return true;
    } else if (KStandardShortcut::prior().contains(key)) {
        QTextCursor cursor = textCursor();
        bool moved = false;
        qreal lastY = cursorRect(cursor).bottom();
        qreal distance = 0;
        do {
            qreal y = cursorRect(cursor).bottom();
            distance += qAbs(y - lastY);
            lastY = y;
            moved = cursor.movePosition(QTextCursor::Up);
        } while (moved && distance < viewport()->height());

        if (moved) {
            cursor.movePosition(QTextCursor::Down);
            verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepSub);
        }
        setTextCursor(cursor);
        return true;
    } else if (KStandardShortcut::begin().contains(key)) {
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::Start);
        setTextCursor(cursor);
        return true;
    } else if (KStandardShortcut::end().contains(key)) {
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::End);
        setTextCursor(cursor);
        return true;
    } else if (KStandardShortcut::beginningOfLine().contains(key)) {
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::StartOfLine);
        setTextCursor(cursor);
        return true;
    } else if (KStandardShortcut::endOfLine().contains(key)) {
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::EndOfLine);
        setTextCursor(cursor);
        return true;
    } else if (searchSupport() && KStandardShortcut::find().contains(key)) {
        Q_EMIT findText();
        return true;
    } else if (KStandardShortcut::pasteSelection().contains(key)) {
        QString text = QApplication::clipboard()->text(QClipboard::Selection);
        if (!text.isEmpty()) {
            insertPlainText(text); // TODO: check if this is html? (MiB)
        }
        return true;
    } else if (event == QKeySequence::DeleteEndOfLine) {
        QTextCursor cursor = textCursor();
        QTextBlock block = cursor.block();
        if (cursor.position() == block.position() + block.length() - 2) {
            cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
        } else {
            cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        }
        cursor.removeSelectedText();
        setTextCursor(cursor);
        return true;
    }

    return false;
}

bool RichTextBrowser::overrideShortcut(QKeyEvent *event)
{
    const int key = event->key() | event->modifiers();

    if (KStandardShortcut::copy().contains(key)) {
        return true;
    } else if (KStandardShortcut::paste().contains(key)) {
        return true;
    } else if (KStandardShortcut::cut().contains(key)) {
        return true;
    } else if (KStandardShortcut::undo().contains(key)) {
        return true;
    } else if (KStandardShortcut::redo().contains(key)) {
        return true;
    } else if (KStandardShortcut::deleteWordBack().contains(key)) {
        return true;
    } else if (KStandardShortcut::deleteWordForward().contains(key)) {
        return true;
    } else if (KStandardShortcut::backwardWord().contains(key)) {
        return true;
    } else if (KStandardShortcut::forwardWord().contains(key)) {
        return true;
    } else if (KStandardShortcut::next().contains(key)) {
        return true;
    } else if (KStandardShortcut::prior().contains(key)) {
        return true;
    } else if (KStandardShortcut::begin().contains(key)) {
        return true;
    } else if (KStandardShortcut::end().contains(key)) {
        return true;
    } else if (KStandardShortcut::beginningOfLine().contains(key)) {
        return true;
    } else if (KStandardShortcut::endOfLine().contains(key)) {
        return true;
    } else if (KStandardShortcut::pasteSelection().contains(key)) {
        return true;
    } else if (searchSupport() && KStandardShortcut::find().contains(key)) {
        return true;
    } else if (searchSupport() && KStandardShortcut::findNext().contains(key)) {
        return true;
    } else if (event->matches(QKeySequence::SelectAll)) { // currently missing in QTextEdit
        return true;
    } else if (event == QKeySequence::DeleteEndOfLine) {
        return true;
    }
    return false;
}

void RichTextBrowser::keyPressEvent(QKeyEvent *event)
{
    const bool isControlClicked = event->modifiers() & Qt::ControlModifier;
    const bool isShiftClicked = event->modifiers() & Qt::ShiftModifier;
    if (handleShortcut(event)) {
        event->accept();
    } else if (event->key() == Qt::Key_Up && isControlClicked && isShiftClicked) {
        moveLineUpDown(true);
        event->accept();
    } else if (event->key() == Qt::Key_Down && isControlClicked && isShiftClicked) {
        moveLineUpDown(false);
        event->accept();
    } else if (event->key() == Qt::Key_Up && isControlClicked) {
        moveCursorBeginUpDown(true);
        event->accept();
    } else if (event->key() == Qt::Key_Down && isControlClicked) {
        moveCursorBeginUpDown(false);
        event->accept();
    } else {
        QTextEdit::keyPressEvent(event);
    }
}

int RichTextBrowser::zoomFactor() const
{
    int pourcentage = 100;
    const QFont f = font();
    if (d->mInitialFontSize != f.pointSize()) {
        pourcentage = (f.pointSize() * 100) / d->mInitialFontSize;
    }
    return pourcentage;
}

void RichTextBrowser::slotZoomReset()
{
    QFont f = font();
    if (d->mInitialFontSize != f.pointSize()) {
        f.setPointSize(d->mInitialFontSize);
        setFont(f);
    }
}

void RichTextBrowser::moveCursorBeginUpDown(bool moveUp)
{
    QTextCursor cursor = textCursor();
    QTextCursor move = cursor;
    move.beginEditBlock();
    cursor.clearSelection();
    move.movePosition(QTextCursor::StartOfBlock);
    move.movePosition(moveUp ? QTextCursor::PreviousBlock : QTextCursor::NextBlock);
    move.endEditBlock();
    setTextCursor(move);
}

void RichTextBrowser::moveLineUpDown(bool moveUp)
{
    QTextCursor cursor = textCursor();
    QTextCursor move = cursor;
    move.beginEditBlock();

    const bool hasSelection = cursor.hasSelection();

    if (hasSelection) {
        move.setPosition(cursor.selectionStart());
        move.movePosition(QTextCursor::StartOfBlock);
        move.setPosition(cursor.selectionEnd(), QTextCursor::KeepAnchor);
        move.movePosition(move.atBlockStart() ? QTextCursor::Left : QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    } else {
        move.movePosition(QTextCursor::StartOfBlock);
        move.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    }
    const QString text = move.selectedText();

    move.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
    move.removeSelectedText();

    if (moveUp) {
        move.movePosition(QTextCursor::PreviousBlock);
        move.insertBlock();
        move.movePosition(QTextCursor::Left);
    } else {
        move.movePosition(QTextCursor::EndOfBlock);
        if (move.atBlockStart()) { // empty block
            move.movePosition(QTextCursor::NextBlock);
            move.insertBlock();
            move.movePosition(QTextCursor::Left);
        } else {
            move.insertBlock();
        }
    }

    int start = move.position();
    move.clearSelection();
    move.insertText(text);
    int end = move.position();

    if (hasSelection) {
        move.setPosition(end);
        move.setPosition(start, QTextCursor::KeepAnchor);
    } else {
        move.setPosition(start);
    }
    move.endEditBlock();

    setTextCursor(move);
}

#include "moc_richtextbrowser.cpp"
