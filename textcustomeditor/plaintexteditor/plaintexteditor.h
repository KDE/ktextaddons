/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

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
/**
 * @brief The PlainTextEditor class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT PlainTextEditor : public QPlainTextEdit
{
    Q_OBJECT
    Q_PROPERTY(bool searchSupport READ searchSupport WRITE setSearchSupport)
    Q_PROPERTY(bool spellCheckingSupport READ spellCheckingSupport WRITE setSpellCheckingSupport)
    Q_PROPERTY(bool textToSpeechSupport READ textToSpeechSupport WRITE setTextToSpeechSupport)
    Q_PROPERTY(bool webShortcutSupport READ webShortcutSupport WRITE setWebShortcutSupport)
    Q_PROPERTY(bool emojiSupport READ emojiSupport WRITE setEmojiSupport)
public:
    explicit PlainTextEditor(QWidget *parent = nullptr);
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

    void setSearchSupport(bool b);
    [[nodiscard]] bool searchSupport() const;

    [[nodiscard]] bool spellCheckingSupport() const;
    void setSpellCheckingSupport(bool check);

    virtual void setReadOnly(bool readOnly);

    void setTextToSpeechSupport(bool b);
    [[nodiscard]] bool textToSpeechSupport() const;

    void setWebShortcutSupport(bool b);
    [[nodiscard]] bool webShortcutSupport() const;

    virtual void createHighlighter();

    void addIgnoreWords(const QStringList &lst);
    [[nodiscard]] bool activateLanguageMenu() const;
    void setActivateLanguageMenu(bool activate);
    [[nodiscard]] Sonnet::Highlighter *highlighter() const;
    [[nodiscard]] bool checkSpellingEnabled() const;
    void setCheckSpellingEnabled(bool check);
    void setSpellCheckingConfigFileName(const QString &_fileName);
    [[nodiscard]] QString spellCheckingConfigFileName() const;
    [[nodiscard]] const QString &spellCheckingLanguage() const;
    void setSpellCheckingLanguage(const QString &_language);

    void setEmojiSupport(bool b);
    [[nodiscard]] bool emojiSupport() const;

public Q_SLOTS:
    void slotDisplayMessageIndicator(const QString &message);
    void slotCheckSpelling();
    void slotSpeakText();
    void slotZoomReset();

protected:
    virtual void addExtraMenuEntry(QMenu *menu, QPoint pos);
    void contextMenuEvent(QContextMenuEvent *event) override;
    [[nodiscard]] bool event(QEvent *ev) override;
    void keyPressEvent(QKeyEvent *event) override;
    [[nodiscard]] bool overrideShortcut(QKeyEvent *event);
    [[nodiscard]] bool handleShortcut(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event) override;

    virtual Sonnet::SpellCheckDecorator *createSpellCheckDecorator();
    void setHighlighter(Sonnet::Highlighter *_highLighter);
    void focusInEvent(QFocusEvent *event) override;
    virtual void updateHighLighter();
    virtual void clearDecorator();

Q_SIGNALS:
    void findText();
    void replaceText();
    void spellCheckerAutoCorrect(const QString &currentWord, const QString &autoCorrectWord);
    void checkSpellingChanged(bool);
    void languageChanged(const QString &);
    void spellCheckStatus(const QString &);
    void say(const QString &text);

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
