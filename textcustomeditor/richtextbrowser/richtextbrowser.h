/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"
#include <QTextBrowser>

class QContextMenuEvent;
class QMenu;
namespace TextCustomEditor
{
/**
 * @brief The RichTextBrowser class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT RichTextBrowser : public QTextBrowser
{
    Q_OBJECT
    Q_PROPERTY(bool searchSupport READ searchSupport WRITE setSearchSupport)
    Q_PROPERTY(bool textToSpeechSupport READ textToSpeechSupport WRITE setTextToSpeechSupport)
    Q_PROPERTY(bool webShortcutSupport READ webShortcutSupport WRITE setWebShortcutSupport)
public:
    explicit RichTextBrowser(QWidget *parent = nullptr);
    ~RichTextBrowser() override;
    enum SupportFeature {
        None = 0,
        Search = 1,
        TextToSpeech = 4,
        AllowWebShortcut = 16,
    };
    Q_DECLARE_FLAGS(SupportFeatures, SupportFeature)

    void setSearchSupport(bool b);
    [[nodiscard]] bool searchSupport() const;

    [[nodiscard]] bool textToSpeechSupport() const;
    void setTextToSpeechSupport(bool b);

    void setWebShortcutSupport(bool b);
    [[nodiscard]] bool webShortcutSupport() const;

    void setDefaultFontSize(int val);
    [[nodiscard]] int zoomFactor() const;

public Q_SLOTS:
    void slotDisplayMessageIndicator(const QString &message);
    void slotSpeakText();
    void slotZoomReset();

protected:
    virtual void addExtraMenuEntry(QMenu *menu, QPoint pos);
    void contextMenuEvent(QContextMenuEvent *event) override;
    bool event(QEvent *ev) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *e) override;

    QMenu *mousePopupMenu(QPoint pos);

Q_SIGNALS:
    void say(const QString &text);
    void findText();

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotUndoableClear();

    TEXTCUSTOMEDITOR_NO_EXPORT bool handleShortcut(QKeyEvent *event);
    TEXTCUSTOMEDITOR_NO_EXPORT bool overrideShortcut(QKeyEvent *event);
    TEXTCUSTOMEDITOR_NO_EXPORT void deleteWordBack();
    TEXTCUSTOMEDITOR_NO_EXPORT void deleteWordForward();
    TEXTCUSTOMEDITOR_NO_EXPORT void moveLineUpDown(bool moveUp);
    TEXTCUSTOMEDITOR_NO_EXPORT void moveCursorBeginUpDown(bool moveUp);
    TEXTCUSTOMEDITOR_NO_EXPORT void regenerateColorScheme();
    TEXTCUSTOMEDITOR_NO_EXPORT void updateReadOnlyColor();
    class RichTextBrowserPrivate;
    std::unique_ptr<RichTextBrowserPrivate> const d;
};
}
