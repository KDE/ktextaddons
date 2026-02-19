/*
   SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"

#include <QPlainTextEdit>

namespace Sonnet
{
class Highlighter;
class SpellCheckDecorator;
}
namespace TextCustomEditor
{
/*!
 * \class TextCustomEditor::PlainTextEditor
 * \inmodule TextCustomEditor
 * \inheaderfile TextCustomEditor/PlainTextEditor
 *
 * \brief The PlainTextEditor class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT PlainTextEditor : public QPlainTextEdit
{
    Q_OBJECT
    Q_PROPERTY(bool searchSupport READ searchSupport WRITE setSearchSupport NOTIFY searchSupportChanged)
    Q_PROPERTY(bool spellCheckingSupport READ spellCheckingSupport WRITE setSpellCheckingSupport)
    Q_PROPERTY(bool textToSpeechSupport READ textToSpeechSupport WRITE setTextToSpeechSupport)
    Q_PROPERTY(bool webShortcutSupport READ webShortcutSupport WRITE setWebShortcutSupport)
    Q_PROPERTY(bool emojiSupport READ emojiSupport WRITE setEmojiSupport)
public:
    /*! Constructs a new PlainTextEditor. */
    explicit PlainTextEditor(QWidget *parent = nullptr);
    /*! Destroys the editor. */
    ~PlainTextEditor() override;

    enum SupportFeature {
        None = 0,
        Search = 1,
        SpellChecking = 2,
        TextToSpeech = 4,
        AllowWebShortcut = 8,
        Emoji = 16,
    };
    Q_DECLARE_FLAGS(SupportFeatures, SupportFeature)

    /*!
     */
    void setSearchSupport(bool b);
    /*! Returns whether text search is supported. */
    [[nodiscard]] bool searchSupport() const;

    /*! Returns whether spell checking is supported. */
    [[nodiscard]] bool spellCheckingSupport() const;
    /*! Sets whether to support spell checking. */
    void setSpellCheckingSupport(bool check);

    /*! Sets whether the editor is read-only. */
    virtual void setReadOnly(bool readOnly);

    /*! Sets whether to support text-to-speech. */
    void setTextToSpeechSupport(bool b);
    /*! Returns whether text-to-speech is supported. */
    [[nodiscard]] bool textToSpeechSupport() const;

    /*! Sets whether to support web shortcuts. */
    void setWebShortcutSupport(bool b);
    /*! Returns whether web shortcut support is enabled. */
    [[nodiscard]] bool webShortcutSupport() const;

    /*! Creates the syntax highlighter for the editor. */
    virtual void createHighlighter();

    /*! Adds words to the spell checker's ignore list. */
    void addIgnoreWords(const QStringList &lst);
    /*! Returns whether the language menu is activated. */
    [[nodiscard]] bool activateLanguageMenu() const;
    /*! Sets whether to activate the language menu. */
    void setActivateLanguageMenu(bool activate);
    /*! Returns the syntax highlighter instance. */
    [[nodiscard]] Sonnet::Highlighter *highlighter() const;
    /*! Returns whether spell checking is currently enabled. */
    [[nodiscard]] bool checkSpellingEnabled() const;
    /*! Sets whether spell checking should be enabled. */
    void setCheckSpellingEnabled(bool check);
    /*! Sets the configuration file name for spell checking. */
    void setSpellCheckingConfigFileName(const QString &_fileName);
    /*! Returns the spell checking configuration file name. */
    [[nodiscard]] QString spellCheckingConfigFileName() const;
    /*! Returns the language used for spell checking. */
    [[nodiscard]] const QString &spellCheckingLanguage() const;
    /*! Sets the language to use for spell checking. */
    void setSpellCheckingLanguage(const QString &_language);
    /*! Sets whether to support emoji. */
    void setEmojiSupport(bool b);
    /*! Returns whether emoji support is enabled. */
    [[nodiscard]] bool emojiSupport() const;

public Q_SLOTS:
    /*! Displays a message to the user. */
    void slotDisplayMessageIndicator(const QString &message);
    /*! Checks the spelling of the document. */
    void slotCheckSpelling();
    /*! Speaks the selected text. */
    void slotSpeakText();
    /*! Resets the zoom level to the default. */
    void slotZoomReset();

protected:
    /*! Adds extra menu entries at the given position. Can be overridden by subclasses. */
    virtual void addExtraMenuEntry(QMenu *menu, QPoint pos);
    /*! Handles context menu events. */
    void contextMenuEvent(QContextMenuEvent *event) override;
    /*!
     */
    [[nodiscard]] bool event(QEvent *ev) override;
    /*! Handles key press events. */
    void keyPressEvent(QKeyEvent *event) override;
    /*! Checks whether a shortcut should be overridden. */
    [[nodiscard]] bool overrideShortcut(QKeyEvent *event);
    /*! Handles keyboard shortcuts. */
    [[nodiscard]] bool handleShortcut(QKeyEvent *event);
    /*! Handles mouse wheel events for zoom. */
    void wheelEvent(QWheelEvent *event) override;
    /*! Creates the spell check decorator for the editor. */
    virtual Sonnet::SpellCheckDecorator *createSpellCheckDecorator();
    /*! Sets the syntax highlighter for the editor. */
    void setHighlighter(Sonnet::Highlighter *_highLighter);
    /*! Handles focus-in events. */
    void focusInEvent(QFocusEvent *event) override;
    /*! Updates the syntax highlighter. */
    virtual void updateHighLighter();
    /*! Clears the spell check decorator. */
    virtual void clearDecorator();

Q_SIGNALS:
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
    /*! Emitted to speak text. */
    void say(const QString &text);
    /*! Emitted when search support is enabled or disabled. */
    void searchSupportChanged();

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotUndoableClear();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotSpellCheckerMisspelling(const QString &text, int pos);
    TEXTCUSTOMEDITOR_NO_EXPORT void slotSpellCheckerCorrected(const QString &, int, const QString &);
    TEXTCUSTOMEDITOR_NO_EXPORT void slotSpellCheckerAutoCorrect(const QString &, const QString &);
    TEXTCUSTOMEDITOR_NO_EXPORT void slotSpellCheckerCanceled();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotSpellCheckerFinished();

    TEXTCUSTOMEDITOR_NO_EXPORT void slotLanguageSelected();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotToggleAutoSpellCheck();
    TEXTCUSTOMEDITOR_NO_EXPORT void addIgnoreWordsToHighLighter();
    TEXTCUSTOMEDITOR_NO_EXPORT void deleteWordBack();
    TEXTCUSTOMEDITOR_NO_EXPORT void deleteWordForward();
    TEXTCUSTOMEDITOR_NO_EXPORT void highlightWord(int length, int pos);
    TEXTCUSTOMEDITOR_NO_EXPORT void deleteEndOfLine();
    TEXTCUSTOMEDITOR_NO_EXPORT void moveLineUpDown(bool moveUp);
    TEXTCUSTOMEDITOR_NO_EXPORT void moveCursorBeginUpDown(bool moveUp);
    TEXTCUSTOMEDITOR_NO_EXPORT void regenerateColorScheme();
    TEXTCUSTOMEDITOR_NO_EXPORT void updateReadOnlyColor();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotInsertEmoticon(const QString &str);
    class PlainTextEditorPrivate;
    std::unique_ptr<PlainTextEditorPrivate> const d;
};
}
