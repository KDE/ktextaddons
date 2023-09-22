/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtextbrowser.h"
#include "textcustomeditor_debug.h"

#include "widgets/textmessageindicator.h"
#include <KConfig>
#include <KConfigGroup>
#include <KCursor>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>
#include <KStandardAction>
#include <KStandardGuiItem>
#include <QActionGroup>
#include <QIcon>

#include "config-textcustomeditor.h"
#include <KIO/KUriFilterSearchProviderActions>
#include <Sonnet/Dialog>
#include <Sonnet/Highlighter>
#include <sonnet/backgroundchecker.h>
#include <sonnet/spellcheckdecorator.h>
#include <sonnet/speller.h>
#ifdef HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
#include <TextEditTextToSpeech/TextToSpeech>
#endif
#include <TextEmoticonsWidgets/EmoticonTextEditAction>

#include <KColorScheme>
#include <QApplication>
#include <QClipboard>
#include <QContextMenuEvent>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDialogButtonBox>
#include <QMenu>
#include <QPushButton>
#include <QScrollBar>
#include <QTextCursor>
#include <QTextDocumentFragment>

using namespace TextCustomEditor;
class Q_DECL_HIDDEN RichTextBrowser::RichTextBrowserPrivate
{
public:
    RichTextBrowserPrivate(RichTextBrowser *qq)
        : q(qq)
        , textIndicator(new TextCustomEditor::TextMessageIndicator(q))
        , webshortcutMenuManager(new KIO::KUriFilterSearchProviderActions(q))
    {
        KConfig sonnetKConfig(QStringLiteral("sonnetrc"));
        KConfigGroup group(&sonnetKConfig, "Spelling");
        checkSpellingEnabled = group.readEntry("checkerEnabledByDefault", false);
        supportFeatures |= RichTextBrowser::Search;
        supportFeatures |= RichTextBrowser::SpellChecking;
        supportFeatures |= RichTextBrowser::TextToSpeech;
        supportFeatures |= RichTextBrowser::AllowTab;
        supportFeatures |= RichTextBrowser::AllowWebShortcut;

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
        delete richTextDecorator;
        delete speller;
    }

    QStringList ignoreSpellCheckingWords;
    RichTextBrowser *const q;
    TextCustomEditor::TextMessageIndicator *const textIndicator;
    QString spellCheckingConfigFileName;
    QString spellCheckingLanguage;
    QTextDocumentFragment originalDoc;
    Sonnet::SpellCheckDecorator *richTextDecorator = nullptr;
    Sonnet::Speller *speller = nullptr;
    KIO::KUriFilterSearchProviderActions *const webshortcutMenuManager;
    RichTextBrowser::SupportFeatures supportFeatures;
    QColor mReadOnlyBackgroundColor;
    int mInitialFontSize;
    bool customPalette = false;
    bool checkSpellingEnabled = false;
    bool activateLanguageMenu = true;
    bool showAutoCorrectionButton = false;
};

RichTextBrowser::RichTextBrowser(QWidget *parent)
    : QTextEdit(parent)
    , d(new RichTextBrowserPrivate(this))
{
    setAcceptRichText(true);
    KCursor::setAutoHideCursor(this, true, false);
    setSpellCheckingConfigFileName(QString());
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

Sonnet::Highlighter *RichTextBrowser::highlighter() const
{
    if (d->richTextDecorator) {
        return d->richTextDecorator->highlighter();
    } else {
        return nullptr;
    }
}

bool RichTextBrowser::activateLanguageMenu() const
{
    return d->activateLanguageMenu;
}

void RichTextBrowser::setActivateLanguageMenu(bool activate)
{
    d->activateLanguageMenu = activate;
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
            popup->addSeparator();
            if (!isReadOnly()) {
                QAction *act = KStandardAction::replace(this, &RichTextBrowser::replaceText, popup);
                popup->addAction(act);
                if (emptyDocument) {
                    act->setEnabled(false);
                }
                popup->addSeparator();
            }
        } else {
            popup->addSeparator();
        }

        if (!isReadOnly() && spellCheckingSupport()) {
            if (!d->speller) {
                d->speller = new Sonnet::Speller();
            }
            if (!d->speller->availableBackends().isEmpty()) {
                QAction *spellCheckAction = popup->addAction(QIcon::fromTheme(QStringLiteral("tools-check-spelling")),
                                                             i18n("Check Spelling..."),
                                                             this,
                                                             &RichTextBrowser::slotCheckSpelling);
                if (emptyDocument) {
                    spellCheckAction->setEnabled(false);
                }
                popup->addSeparator();
                QAction *autoSpellCheckAction = popup->addAction(i18n("Auto Spell Check"), this, &RichTextBrowser::slotToggleAutoSpellCheck);
                autoSpellCheckAction->setCheckable(true);
                autoSpellCheckAction->setChecked(checkSpellingEnabled());
                popup->addAction(autoSpellCheckAction);

                if (checkSpellingEnabled() && d->activateLanguageMenu) {
                    auto languagesMenu = new QMenu(i18n("Spell Checking Language"), popup);
                    auto languagesGroup = new QActionGroup(languagesMenu);
                    languagesGroup->setExclusive(true);

                    QString defaultSpellcheckingLanguage = spellCheckingLanguage();
                    if (defaultSpellcheckingLanguage.isEmpty()) {
                        defaultSpellcheckingLanguage = d->speller->defaultLanguage();
                    }

                    QMapIterator<QString, QString> i(d->speller->availableDictionaries());
                    while (i.hasNext()) {
                        i.next();
                        QAction *languageAction = languagesMenu->addAction(i.key());
                        languageAction->setCheckable(true);
                        languageAction->setChecked(defaultSpellcheckingLanguage == i.value());
                        languageAction->setData(i.value());
                        languageAction->setActionGroup(languagesGroup);
                        connect(languageAction, &QAction::triggered, this, &RichTextBrowser::slotLanguageSelected);
                    }
                    popup->addMenu(languagesMenu);
                }
                popup->addSeparator();
            }
        }

        if (allowTabSupport() && !isReadOnly()) {
            QAction *allowTabAction = popup->addAction(i18n("Allow Tabulations"));
            allowTabAction->setCheckable(true);
            allowTabAction->setChecked(!tabChangesFocus());
            connect(allowTabAction, &QAction::triggered, this, &RichTextBrowser::slotAllowTab);
        }
#ifdef HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
        if (!emptyDocument) {
            QAction *speakAction = popup->addAction(i18n("Speak Text"));
            speakAction->setIcon(QIcon::fromTheme(QStringLiteral("preferences-desktop-text-to-speech")));
            connect(speakAction, &QAction::triggered, this, &RichTextBrowser::slotSpeakText);
        }
#endif
        if (webShortcutSupport() && textCursor().hasSelection()) {
            popup->addSeparator();
            const QString selectedText = textCursor().selectedText();
            d->webshortcutMenuManager->setSelectedText(selectedText);
            d->webshortcutMenuManager->addWebShortcutsToMenu(popup);
        }
        if (emojiSupport()) {
            popup->addSeparator();
            auto action = new TextEmoticonsWidgets::EmoticonTextEditAction(this);
            popup->addAction(action);
            connect(action, &TextEmoticonsWidgets::EmoticonTextEditAction::insertEmoticon, this, &RichTextBrowser::slotInsertEmoticon);
        }
        addExtraMenuEntry(popup, pos);
        return popup;
    }
    return nullptr;
}

void RichTextBrowser::slotInsertEmoticon(const QString &str)
{
    insertPlainText(str);
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
    if (b) {
        d->supportFeatures |= AllowWebShortcut;
    } else {
        d->supportFeatures = (d->supportFeatures & ~AllowWebShortcut);
    }
}

bool RichTextBrowser::webShortcutSupport() const
{
    return d->supportFeatures & AllowWebShortcut;
}

void RichTextBrowser::setEmojiSupport(bool b)
{
    if (b) {
        d->supportFeatures |= Emoji;
    } else {
        d->supportFeatures = (d->supportFeatures & ~Emoji);
    }
}

bool RichTextBrowser::emojiSupport() const
{
    return d->supportFeatures & Emoji;
}

void RichTextBrowser::addIgnoreWords(const QStringList &lst)
{
    d->ignoreSpellCheckingWords = lst;
    addIgnoreWordsToHighLighter();
}

void RichTextBrowser::forceAutoCorrection(bool selectedText)
{
    Q_UNUSED(selectedText)
    // Nothing here
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

void RichTextBrowser::setAllowTabSupport(bool b)
{
    if (b) {
        d->supportFeatures |= AllowTab;
    } else {
        d->supportFeatures = (d->supportFeatures & ~AllowTab);
    }
}

bool RichTextBrowser::allowTabSupport() const
{
    return d->supportFeatures & AllowTab;
}

void RichTextBrowser::setShowAutoCorrectButton(bool b)
{
    d->showAutoCorrectionButton = b;
}

bool RichTextBrowser::showAutoCorrectButton() const
{
    return d->showAutoCorrectionButton;
}

bool RichTextBrowser::spellCheckingSupport() const
{
    return d->supportFeatures & SpellChecking;
}

void RichTextBrowser::setSpellCheckingSupport(bool check)
{
    if (check) {
        d->supportFeatures |= SpellChecking;
    } else {
        d->supportFeatures = (d->supportFeatures & ~SpellChecking);
    }
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

void RichTextBrowser::slotAllowTab()
{
    setTabChangesFocus(!tabChangesFocus());
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

void RichTextBrowser::setReadOnly(bool readOnly)
{
    if (!readOnly && hasFocus() && checkSpellingEnabled() && !d->richTextDecorator) {
        createHighlighter();
    }

    if (readOnly == isReadOnly()) {
        return;
    }

    if (readOnly) {
        clearDecorator();
        d->customPalette = testAttribute(Qt::WA_SetPalette);
        updateReadOnlyColor();
    } else {
        if (d->customPalette && testAttribute(Qt::WA_SetPalette)) {
            QPalette p = palette();
            QColor color = p.color(QPalette::Normal, QPalette::Base);
            p.setColor(QPalette::Base, color);
            p.setColor(QPalette::Window, color);
            setPalette(p);
        } else {
            setPalette(QPalette());
        }
    }

    QTextEdit::setReadOnly(readOnly);
}

void RichTextBrowser::checkSpelling(bool force)
{
    if (document()->isEmpty()) {
        slotDisplayMessageIndicator(i18n("Nothing to spell check."));
        if (force) {
            Q_EMIT spellCheckingFinished();
        }
        return;
    }
    auto backgroundSpellCheck = new Sonnet::BackgroundChecker;
    if (backgroundSpellCheck->speller().availableBackends().isEmpty()) {
        if (force) {
            const int answer = KMessageBox::questionTwoActions(this,
                                                               i18n("No backend available for spell checking. Do you want to send the email anyways?"),
                                                               QString(),
                                                               KGuiItem(i18nc("@action:button", "Send"), QStringLiteral("mail-send")),
                                                               KStandardGuiItem::cancel());
            if (answer == KMessageBox::ButtonCode::PrimaryAction) {
                Q_EMIT spellCheckingFinished();
            }
        } else {
            slotDisplayMessageIndicator(i18n("No backend available for spell checking."));
        }
        delete backgroundSpellCheck;
        return;
    }
    if (!d->spellCheckingLanguage.isEmpty()) {
        backgroundSpellCheck->changeLanguage(d->spellCheckingLanguage);
    }
    if (!d->ignoreSpellCheckingWords.isEmpty()) {
        for (const QString &word : std::as_const(d->ignoreSpellCheckingWords)) {
            backgroundSpellCheck->speller().addToSession(word);
        }
    }
    auto spellDialog = new Sonnet::Dialog(backgroundSpellCheck, force ? this : nullptr);
    auto buttonBox = spellDialog->findChild<QDialogButtonBox *>();
    if (buttonBox) {
        auto skipButton = new QPushButton(i18n("Skip"));
        buttonBox->addButton(skipButton, QDialogButtonBox::ActionRole);
        connect(skipButton, &QPushButton::clicked, spellDialog, &Sonnet::Dialog::close);
        if (force) {
            connect(skipButton, &QPushButton::clicked, this, &RichTextBrowser::spellCheckingFinished);
        }
    } else {
        qCWarning(TEXTCUSTOMEDITOR_LOG) << " Impossible to find qdialogbuttonbox";
    }
    backgroundSpellCheck->setParent(spellDialog);
    spellDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    spellDialog->activeAutoCorrect(d->showAutoCorrectionButton);
    connect(spellDialog, &Sonnet::Dialog::replace, this, &RichTextBrowser::slotSpellCheckerCorrected);
    connect(spellDialog, &Sonnet::Dialog::misspelling, this, &RichTextBrowser::slotSpellCheckerMisspelling);
    connect(spellDialog, &Sonnet::Dialog::autoCorrect, this, &RichTextBrowser::slotSpellCheckerAutoCorrect);
    connect(spellDialog, &Sonnet::Dialog::spellCheckDone, this, &RichTextBrowser::slotSpellCheckerFinished);
    connect(spellDialog, &Sonnet::Dialog::cancel, this, &RichTextBrowser::slotSpellCheckerCanceled);
    connect(spellDialog, &Sonnet::Dialog::spellCheckStatus, this, &RichTextBrowser::spellCheckStatus);
    connect(spellDialog, &Sonnet::Dialog::languageChanged, this, &RichTextBrowser::languageChanged);
    if (force) {
        connect(spellDialog, &Sonnet::Dialog::spellCheckDone, this, &RichTextBrowser::spellCheckingFinished);
        connect(spellDialog, &Sonnet::Dialog::cancel, this, &RichTextBrowser::spellCheckingCanceled);
    }
    d->originalDoc = QTextDocumentFragment(document());
    spellDialog->setBuffer(toPlainText());
    spellDialog->show();
}

void RichTextBrowser::slotCheckSpelling()
{
    checkSpelling(false);
}

void RichTextBrowser::forceSpellChecking()
{
    checkSpelling(true);
}

void RichTextBrowser::slotSpellCheckerCanceled()
{
    QTextDocument *doc = document();
    doc->clear();
    QTextCursor cursor(doc);
    cursor.insertFragment(d->originalDoc);
    slotSpellCheckerFinished();
}

void RichTextBrowser::slotSpellCheckerAutoCorrect(const QString &currentWord, const QString &autoCorrectWord)
{
    Q_EMIT spellCheckerAutoCorrect(currentWord, autoCorrectWord);
}

void RichTextBrowser::slotSpellCheckerMisspelling(const QString &text, int pos)
{
    highlightWord(text.length(), pos);
}

void RichTextBrowser::slotSpellCheckerCorrected(const QString &oldWord, int pos, const QString &newWord)
{
    if (oldWord != newWord) {
        QTextCursor cursor(document());
        cursor.setPosition(pos);
        cursor.setPosition(pos + oldWord.length(), QTextCursor::KeepAnchor);
        cursor.insertText(newWord);
    }
}

void RichTextBrowser::slotSpellCheckerFinished()
{
    QTextCursor cursor(document());
    cursor.clearSelection();
    setTextCursor(cursor);
    if (highlighter()) {
        highlighter()->rehighlight();
    }
}

void RichTextBrowser::highlightWord(int length, int pos)
{
    QTextCursor cursor(document());
    cursor.setPosition(pos);
    cursor.setPosition(pos + length, QTextCursor::KeepAnchor);
    setTextCursor(cursor);
    ensureCursorVisible();
}

void RichTextBrowser::createHighlighter()
{
    auto highlighter = new Sonnet::Highlighter(this);
    highlighter->setCurrentLanguage(spellCheckingLanguage());
    setHighlighter(highlighter);
}

Sonnet::SpellCheckDecorator *RichTextBrowser::createSpellCheckDecorator()
{
    return new Sonnet::SpellCheckDecorator(this);
}

void RichTextBrowser::addIgnoreWordsToHighLighter()
{
    if (d->ignoreSpellCheckingWords.isEmpty()) {
        return;
    }
    if (d->richTextDecorator) {
        Sonnet::Highlighter *_highlighter = d->richTextDecorator->highlighter();
        for (const QString &word : std::as_const(d->ignoreSpellCheckingWords)) {
            _highlighter->ignoreWord(word);
        }
    }
}

void RichTextBrowser::setHighlighter(Sonnet::Highlighter *_highLighter)
{
    Sonnet::SpellCheckDecorator *decorator = createSpellCheckDecorator();
    delete decorator->highlighter();
    decorator->setHighlighter(_highLighter);

    d->richTextDecorator = decorator;
    addIgnoreWordsToHighLighter();
}

void RichTextBrowser::focusInEvent(QFocusEvent *event)
{
    if (d->checkSpellingEnabled && !isReadOnly() && !d->richTextDecorator && spellCheckingSupport()) {
        createHighlighter();
    }

    QTextEdit::focusInEvent(event);
}

void RichTextBrowser::setSpellCheckingConfigFileName(const QString &_fileName)
{
    d->spellCheckingConfigFileName = _fileName;
    KSharedConfig::Ptr config = KSharedConfig::openConfig(d->spellCheckingConfigFileName);
    if (config->hasGroup("Spelling")) {
        KConfigGroup group(config, "Spelling");
        d->checkSpellingEnabled = group.readEntry("checkerEnabledByDefault", false);
        d->spellCheckingLanguage = group.readEntry("Language", QString());
    }
    setCheckSpellingEnabled(checkSpellingEnabled());

    if (!d->spellCheckingLanguage.isEmpty() && highlighter()) {
        highlighter()->setCurrentLanguage(d->spellCheckingLanguage);
        highlighter()->rehighlight();
    }
}

QString RichTextBrowser::spellCheckingConfigFileName() const
{
    return d->spellCheckingConfigFileName;
}

bool RichTextBrowser::checkSpellingEnabled() const
{
    return d->checkSpellingEnabled;
}

void RichTextBrowser::setCheckSpellingEnabled(bool check)
{
    if (check == d->checkSpellingEnabled) {
        return;
    }
    d->checkSpellingEnabled = check;
    Q_EMIT checkSpellingChanged(check);
    // From the above statement we know that if we're turning checking
    // on that we need to create a new highlighter and if we're turning it
    // off we should remove the old one.

    if (check) {
        if (hasFocus()) {
            if (!d->richTextDecorator) {
                createHighlighter();
            }
            if (!d->spellCheckingLanguage.isEmpty()) {
                setSpellCheckingLanguage(spellCheckingLanguage());
            }
        }
    } else {
        clearDecorator();
    }
    updateHighLighter();
}

void RichTextBrowser::updateHighLighter()
{
}

void RichTextBrowser::clearDecorator()
{
    delete d->richTextDecorator;
    d->richTextDecorator = nullptr;
}

const QString &RichTextBrowser::spellCheckingLanguage() const
{
    return d->spellCheckingLanguage;
}

void RichTextBrowser::setSpellCheckingLanguage(const QString &_language)
{
    if (highlighter()) {
        highlighter()->setCurrentLanguage(_language);
    }

    if (_language != d->spellCheckingLanguage) {
        d->spellCheckingLanguage = _language;
        KSharedConfig::Ptr config = KSharedConfig::openConfig(d->spellCheckingConfigFileName);
        KConfigGroup group(config, "Spelling");
        group.writeEntry("Language", d->spellCheckingLanguage);

        Q_EMIT languageChanged(_language);
    }
}

void RichTextBrowser::slotToggleAutoSpellCheck()
{
    setCheckSpellingEnabled(!checkSpellingEnabled());
    KSharedConfig::Ptr config = KSharedConfig::openConfig(d->spellCheckingConfigFileName);
    KConfigGroup group(config, "Spelling");
    group.writeEntry("checkerEnabledByDefault", d->checkSpellingEnabled);
}

void RichTextBrowser::slotLanguageSelected()
{
    auto languageAction = static_cast<QAction *>(QObject::sender());
    setSpellCheckingLanguage(languageAction->data().toString());
}

static void deleteWord(QTextCursor cursor, QTextCursor::MoveOperation op)
{
    cursor.clearSelection();
    cursor.movePosition(op, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
}

void RichTextBrowser::deleteWordBack()
{
    deleteWord(textCursor(), QTextCursor::PreviousWord);
}

void RichTextBrowser::deleteWordForward()
{
    deleteWord(textCursor(), QTextCursor::WordRight);
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
    } else if (searchSupport() && KStandardShortcut::replace().contains(key)) {
        if (!isReadOnly()) {
            Q_EMIT replaceText();
        }
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
    } else if (searchSupport() && KStandardShortcut::replace().contains(key)) {
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

#include "moc_richtexteditor.cpp"
