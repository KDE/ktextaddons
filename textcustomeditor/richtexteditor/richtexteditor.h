/*
   SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"
#include <QTextEdit>

class QContextMenuEvent;
class QMenu;
namespace Sonnet
{
class Highlighter;
class SpellCheckDecorator;
}
namespace TextCustomEditor
{
/*!
 * \class TextCustomEditor::RichTextEditor
 * \inmodule TextCustomEditor
 * \inheaderfile TextCustomEditor/RichTextEditor
 *
 * \brief The RichTextEditor class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT RichTextEditor : public QTextEdit
{
    Q_OBJECT
    Q_PROPERTY(bool searchSupport READ searchSupport WRITE setSearchSupport)
    Q_PROPERTY(bool spellCheckingSupport READ spellCheckingSupport WRITE setSpellCheckingSupport)
    Q_PROPERTY(bool textToSpeechSupport READ textToSpeechSupport WRITE setTextToSpeechSupport)
    Q_PROPERTY(bool activateLanguageMenu READ activateLanguageMenu WRITE setActivateLanguageMenu)
    Q_PROPERTY(bool tabSupport READ allowTabSupport WRITE setAllowTabSupport)
    Q_PROPERTY(bool webShortcutSupport READ webShortcutSupport WRITE setWebShortcutSupport)
    Q_PROPERTY(bool emojiSupport READ emojiSupport WRITE setEmojiSupport)
public:
    /*! Constructs a new RichTextEditor. */
    explicit RichTextEditor(QWidget *parent = nullptr);
    /*! Destroys the editor. */
    ~RichTextEditor() override;
    enum SupportFeature {
        None = 0,
        Search = 1,
        SpellChecking = 2,
        TextToSpeech = 4,
        AllowTab = 8,
        AllowWebShortcut = 16,
        Emoji = 32,
        QuickTextFormat = 64,
    };
    Q_DECLARE_FLAGS(SupportFeatures, SupportFeature)

    /*! Sets whether to support text search functionality. */
    void setSearchSupport(bool b);
    /*! Returns whether text search is supported. */
    [[nodiscard]] bool searchSupport() const;

    /*! Returns whether spell checking is supported. */
    [[nodiscard]] bool spellCheckingSupport() const;
    /*! Sets whether to support spell checking. */
    void setSpellCheckingSupport(bool check);

    /*! Sets the configuration file name for spell checking. */
    void setSpellCheckingConfigFileName(const QString &_fileName);

    /*! Returns whether spell checking is currently enabled. */
    [[nodiscard]] bool checkSpellingEnabled() const;
    /*! Sets whether spell checking should be enabled. */
    void setCheckSpellingEnabled(bool check);

    /*! Sets the language to use for spell checking. */
    void setSpellCheckingLanguage(const QString &_language);
    /*! Returns the language used for spell checking. */
    [[nodiscard]] const QString &spellCheckingLanguage() const;

    /*! Sets whether the editor is read-only. */
    virtual void setReadOnly(bool readOnly);
    /*! Creates the syntax highlighter for the editor. */
    virtual void createHighlighter();

    /*! Returns whether text-to-speech is supported. */
    [[nodiscard]] bool textToSpeechSupport() const;
    /*! Sets whether to support text-to-speech. */
    void setTextToSpeechSupport(bool b);
    /*! Returns the syntax highlighter instance. */
    [[nodiscard]] Sonnet::Highlighter *highlighter() const;

    /*! Returns whether the language menu is activated. */
    [[nodiscard]] bool activateLanguageMenu() const;
    /*! Sets whether to activate the language menu. */
    void setActivateLanguageMenu(bool activate);

    /*! Sets whether tab key should insert tab characters. */
    void setAllowTabSupport(bool b);
    /*! Returns whether tab support is enabled. */
    [[nodiscard]] bool allowTabSupport() const;

    /*! Sets whether to show the auto-correct button. */
    void setShowAutoCorrectButton(bool b);
    /*! Returns whether the auto-correct button is shown. */
    [[nodiscard]] bool showAutoCorrectButton() const;

    /*! Forces a spell check of the entire document. */
    void forceSpellChecking();
    /*! Returns the spell checking configuration file name. */
    [[nodiscard]] QString spellCheckingConfigFileName() const;

    /*! Sets whether to support web shortcuts. */
    void setWebShortcutSupport(bool b);
    /*! Returns whether web shortcut support is enabled. */
    [[nodiscard]] bool webShortcutSupport() const;

    /*! Adds words to the spell checker's ignore list. */
    void addIgnoreWords(const QStringList &lst);

    // Reimplement it in subclass
    virtual void forceAutoCorrection(bool selectedText = false);

    /*!
     */
    void setDefaultFontSize(int val);
    /*!
     */
    [[nodiscard]] int zoomFactor() const;
    /*!
     */
    void setEmojiSupport(bool b);
    /*!
     */
    [[nodiscard]] bool emojiSupport() const;

    /*!
     */
    [[nodiscard]] bool quickTextFormat() const;
    /*!
     */
    void setQuickTextFormat(bool b);
public Q_SLOTS:
    /*! Displays a message to the user. */
    void slotDisplayMessageIndicator(const QString &message);
    /*! Speaks the selected text. */
    void slotSpeakText();
    /*! Checks the spelling of the document. */
    void slotCheckSpelling();
    /*! Resets the zoom level to the default. */
    void slotZoomReset();

protected:
    /*!
     */
    virtual void addExtraMenuEntry(QMenu *menu, QPoint pos);
    /*! Handles context menu events. */
    void contextMenuEvent(QContextMenuEvent *event) override;
    /*! Handles focus-in events. */
    void focusInEvent(QFocusEvent *event) override;
    /*! Handles general events. */
    [[nodiscard]] bool event(QEvent *ev) override;
    /*! Handles key press events. */
    void keyPressEvent(QKeyEvent *event) override;
    /*! Handles mouse wheel events for zoom. */
    void wheelEvent(QWheelEvent *e) override;

    /*! Returns the context menu for the given position. */
    QMenu *mousePopupMenu(QPoint pos);
    /*! Creates the spell check decorator for the editor. */
    virtual Sonnet::SpellCheckDecorator *createSpellCheckDecorator();
    /*! Sets the syntax highlighter for the editor. */
    void setHighlighter(Sonnet::Highlighter *_highLighter);

    /*! Updates the syntax highlighter. */
    virtual void updateHighLighter();
    /*! Clears the spell check decorator. */
    virtual void clearDecorator();

Q_SIGNALS:
    /*! Emitted to speak the given text. */
    void say(const QString &text);
    /*! Emitted when the user wants to search for text. */
    void findText();
    /*! Emitted when the user wants to open the replace dialog. */
    void replaceText();
    /*! Emitted when auto-correction is applied. */
    void spellCheckerAutoCorrect(const QString &currentWord, const QString &autoCorrectWord);
    /*! Emitted when spell checking is enabled or disabled. */
    void checkSpellingChanged(bool);
    /*! Emitted when the spell checking language changes. */
    void languageChanged(const QString &);
    /*! Emitted to display spell checking status. */
    void spellCheckStatus(const QString &);
    /*! Emitted when spell checking is finished. */
    void spellCheckingFinished();
    /*! Emitted when spell checking is canceled. */
    void spellCheckingCanceled();

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotUndoableClear();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotSpellCheckerMisspelling(const QString &text, int pos);
    TEXTCUSTOMEDITOR_NO_EXPORT void slotSpellCheckerCorrected(const QString &, int, const QString &);
    TEXTCUSTOMEDITOR_NO_EXPORT void slotSpellCheckerAutoCorrect(const QString &, const QString &);
    TEXTCUSTOMEDITOR_NO_EXPORT void slotSpellCheckerCanceled();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotSpellCheckerFinished();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotToggleAutoSpellCheck();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotLanguageSelected();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotAllowTab();

    TEXTCUSTOMEDITOR_NO_EXPORT void addIgnoreWordsToHighLighter();
    TEXTCUSTOMEDITOR_NO_EXPORT bool handleShortcut(QKeyEvent *event);
    TEXTCUSTOMEDITOR_NO_EXPORT bool overrideShortcut(QKeyEvent *event);
    TEXTCUSTOMEDITOR_NO_EXPORT void deleteWordBack();
    TEXTCUSTOMEDITOR_NO_EXPORT void deleteWordForward();
    TEXTCUSTOMEDITOR_NO_EXPORT void highlightWord(int length, int pos);
    TEXTCUSTOMEDITOR_NO_EXPORT void checkSpelling(bool force);
    TEXTCUSTOMEDITOR_NO_EXPORT void moveLineUpDown(bool moveUp);
    TEXTCUSTOMEDITOR_NO_EXPORT void moveCursorBeginUpDown(bool moveUp);
    TEXTCUSTOMEDITOR_NO_EXPORT void regenerateColorScheme();
    TEXTCUSTOMEDITOR_NO_EXPORT void updateReadOnlyColor();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotInsertEmoticon(const QString &str);
    class RichTextEditorPrivate;
    std::unique_ptr<RichTextEditorPrivate> const d;
};
}
