/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtextbrowser.h"

#include <TextAddonsWidgets/TextMessageWidget>

#include <KCursor>
#include <KLocalizedString>
#include <KStandardActions>
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
#include <QContextMenuEvent>
#include <QMenu>
#include <QScrollBar>
#include <QTextCursor>

using namespace Qt::Literals::StringLiterals;
using namespace TextCustomEditor;
class Q_DECL_HIDDEN RichTextBrowser::RichTextBrowserPrivate
{
public:
    explicit RichTextBrowserPrivate(RichTextBrowser *qq)
        : q(qq)
        , textIndicator(new TextAddonsWidgets::TextMessageWidget(q))
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
            if (QTextCursor c = q->textCursor(); c.charFormat().isAnchor() && !c.hasSelection()) {
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

    RichTextBrowser *const q;
    TextAddonsWidgets::TextMessageWidget *const textIndicator;
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
    d->textIndicator->showMessage(message);
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
        if (searchSupport()) {
            popup->addSeparator();
            QAction *findAction = KStandardActions::find(this, &RichTextBrowser::findText, popup);
            popup->addAction(findAction);
            if (emptyDocument) {
                findAction->setEnabled(false);
            }
        } else {
            popup->addSeparator();
        }

#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
        if (d->supportFeatures & TextToSpeech) {
            if (!emptyDocument) {
                QAction *speakAction = popup->addAction(i18n("Speak Text"));
                speakAction->setIcon(QIcon::fromTheme(u"preferences-desktop-text-to-speech"_s));
                connect(speakAction, &QAction::triggered, this, &RichTextBrowser::slotSpeakText);
            }
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

void RichTextBrowser::setWebShortcutSupport([[maybe_unused]] bool b)
{
#if HAVE_KTEXTADDONS_KIO_SUPPORT
    if (b) {
        d->supportFeatures |= AllowWebShortcut;
    } else {
        d->supportFeatures = (d->supportFeatures & ~AllowWebShortcut);
    }
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

void RichTextBrowser::addExtraMenuEntry([[maybe_unused]] QMenu *menu, [[maybe_unused]] QPoint pos)
{
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

bool RichTextBrowser::event(QEvent *ev)
{
    if (ev->type() == QEvent::ShortcutOverride) {
        if (auto e = static_cast<QKeyEvent *>(ev); overrideShortcut(e)) {
            e->accept();
            return true;
        }
    } else if (ev->type() == QEvent::ApplicationPaletteChange) {
        regenerateColorScheme();
    }
    return QTextBrowser::event(ev);
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
    QTextBrowser::wheelEvent(event);
}

bool RichTextBrowser::handleShortcut(QKeyEvent *event)
{
    if (const int key = event->key() | event->modifiers(); KStandardShortcut::copy().contains(key)) {
        copy();
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
            const qreal y = cursorRect(cursor).bottom();
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
            const qreal y = cursorRect(cursor).bottom();
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
    }

    return false;
}

bool RichTextBrowser::overrideShortcut(QKeyEvent *event)
{
    if (const int key = event->key() | event->modifiers(); KStandardShortcut::copy().contains(key)) {
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
    } else if (searchSupport() && KStandardShortcut::find().contains(key)) {
        return true;
    } else if (searchSupport() && KStandardShortcut::findNext().contains(key)) {
        return true;
    } else if (event->matches(QKeySequence::SelectAll)) { // currently missing in QTextEdit
        return true;
    }
    return false;
}

void RichTextBrowser::keyPressEvent(QKeyEvent *event)
{
    const bool isControlClicked = event->modifiers() & Qt::ControlModifier;
    if (handleShortcut(event)) {
        event->accept();
    } else if (event->key() == Qt::Key_Up && isControlClicked) {
        moveCursorBeginUpDown(true);
        event->accept();
    } else if (event->key() == Qt::Key_Down && isControlClicked) {
        moveCursorBeginUpDown(false);
        event->accept();
    } else {
        QTextBrowser::keyPressEvent(event);
    }
}

int RichTextBrowser::zoomFactor() const
{
    int pourcentage = 100;
    if (const QFont f = font(); d->mInitialFontSize != f.pointSize()) {
        pourcentage = (f.pointSize() * 100) / d->mInitialFontSize;
    }
    return pourcentage;
}

void RichTextBrowser::slotZoomReset()
{
    if (QFont f = font(); d->mInitialFontSize != f.pointSize()) {
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

#include "moc_richtextbrowser.cpp"
