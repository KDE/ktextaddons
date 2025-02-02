/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

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
/**
 * @brief The RichTextEditor class
 * @author Laurent Montel <montel@kde.org>
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
    explicit RichTextEditor(QWidget *parent = nullptr);
    ~RichTextEditor() override;
    enum SupportFeature {
        None = 0,
        Search = 1,
        SpellChecking = 2,
        TextToSpeech = 4,
        AllowTab = 8,
        AllowWebShortcut = 16,
        Emoji = 32,
    };
    Q_DECLARE_FLAGS(SupportFeatures, SupportFeature)

    void setSearchSupport(bool b);
    [[nodiscard]] bool searchSupport() const;

    [[nodiscard]] bool spellCheckingSupport() const;
    void setSpellCheckingSupport(bool check);

    void setSpellCheckingConfigFileName(const QString &_fileName);

    [[nodiscard]] bool checkSpellingEnabled() const;
    void setCheckSpellingEnabled(bool check);

    void setSpellCheckingLanguage(const QString &_language);
    [[nodiscard]] const QString &spellCheckingLanguage() const;

    virtual void setReadOnly(bool readOnly);
    virtual void createHighlighter();

    [[nodiscard]] bool textToSpeechSupport() const;
    void setTextToSpeechSupport(bool b);
    [[nodiscard]] Sonnet::Highlighter *highlighter() const;

    [[nodiscard]] bool activateLanguageMenu() const;
    void setActivateLanguageMenu(bool activate);

    void setAllowTabSupport(bool b);
    [[nodiscard]] bool allowTabSupport() const;

    void setShowAutoCorrectButton(bool b);
    [[nodiscard]] bool showAutoCorrectButton() const;

    void forceSpellChecking();
    [[nodiscard]] QString spellCheckingConfigFileName() const;

    void setWebShortcutSupport(bool b);
    [[nodiscard]] bool webShortcutSupport() const;

    void addIgnoreWords(const QStringList &lst);

    // Reimplement it in subclass
    virtual void forceAutoCorrection(bool selectedText = false);

    void setDefaultFontSize(int val);
    [[nodiscard]] int zoomFactor() const;
    void setEmojiSupport(bool b);
    [[nodiscard]] bool emojiSupport() const;

public Q_SLOTS:
    void slotDisplayMessageIndicator(const QString &message);
    void slotSpeakText();
    void slotCheckSpelling();
    void slotZoomReset();

protected:
    virtual void addExtraMenuEntry(QMenu *menu, QPoint pos);
    void contextMenuEvent(QContextMenuEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    [[nodiscard]] bool event(QEvent *ev) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *e) override;

    QMenu *mousePopupMenu(QPoint pos);
    virtual Sonnet::SpellCheckDecorator *createSpellCheckDecorator();
    void setHighlighter(Sonnet::Highlighter *_highLighter);

    virtual void updateHighLighter();
    virtual void clearDecorator();

Q_SIGNALS:
    void say(const QString &text);
    void findText();
    void replaceText();
    void spellCheckerAutoCorrect(const QString &currentWord, const QString &autoCorrectWord);
    void checkSpellingChanged(bool);
    void languageChanged(const QString &);
    void spellCheckStatus(const QString &);
    void spellCheckingFinished();
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
