/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"
#include <QTextBrowser>

class QContextMenuEvent;
class QMenu;
namespace TextCustomEditor
{
/*!
 * \class TextCustomEditor::RichTextBrowser
 * \inmodule TextCustomEditor
 * \inheaderfile TextCustomEditor/RichTextBrowser
 *
 * \brief The RichTextBrowser class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT RichTextBrowser : public QTextBrowser
{
    Q_OBJECT
    Q_PROPERTY(bool searchSupport READ searchSupport WRITE setSearchSupport)
    Q_PROPERTY(bool textToSpeechSupport READ textToSpeechSupport WRITE setTextToSpeechSupport)
    Q_PROPERTY(bool webShortcutSupport READ webShortcutSupport WRITE setWebShortcutSupport)
public:
    /*! Constructs a new RichTextBrowser. */
    explicit RichTextBrowser(QWidget *parent = nullptr);
    /*! Destroys the browser. */
    ~RichTextBrowser() override;
    enum SupportFeature {
        None = 0,
        Search = 1,
        TextToSpeech = 4,
        AllowWebShortcut = 16,
    };
    Q_DECLARE_FLAGS(SupportFeatures, SupportFeature)

    /*! Sets whether to support text search functionality. */
    void setSearchSupport(bool b);
    /*! Returns whether text search is supported. */
    [[nodiscard]] bool searchSupport() const;

    /*! Returns whether text-to-speech is supported. */
    [[nodiscard]] bool textToSpeechSupport() const;
    /*! Sets whether to support text-to-speech. */
    void setTextToSpeechSupport(bool b);

    /*! Sets whether to support web shortcuts. */
    void setWebShortcutSupport(bool b);
    /*! Returns whether web shortcut support is enabled. */
    [[nodiscard]] bool webShortcutSupport() const;

    /*! Sets the default font size. */
    void setDefaultFontSize(int val);
    /*! Returns the current zoom factor. */
    [[nodiscard]] int zoomFactor() const;

public Q_SLOTS:
    /*! Displays a message to the user. */
    void slotDisplayMessageIndicator(const QString &message);
    /*! Speaks the selected text. */
    void slotSpeakText();
    /*! Resets the zoom level to the default. */
    void slotZoomReset();

protected:
    /*! Adds extra menu entries at the given position. Can be overridden by subclasses. */
    virtual void addExtraMenuEntry(QMenu *menu, QPoint pos);
    /*! Handles context menu events. */
    void contextMenuEvent(QContextMenuEvent *event) override;
    /*! Handles general events. */
    bool event(QEvent *ev) override;
    /*! Handles key press events. */
    void keyPressEvent(QKeyEvent *event) override;
    /*! Handles mouse wheel events for zoom. */
    void wheelEvent(QWheelEvent *e) override;

    /*!
     */
    QMenu *mousePopupMenu(QPoint pos);

Q_SIGNALS:
    /*!
     */
    void say(const QString &text);
    /*!
     */
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
