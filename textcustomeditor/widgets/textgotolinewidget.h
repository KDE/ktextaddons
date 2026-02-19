/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"
#include <QWidget>

namespace TextCustomEditor
{
class TextGoToLineWidgetPrivate;
/*!
 * \class TextCustomEditor::TextGoToLineWidget
 * \inmodule TextCustomEditor
 * \inheaderfile TextCustomEditor/TextGoToLineWidget
 *
 * \brief The TextGoToLineWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT TextGoToLineWidget : public QWidget
{
    Q_OBJECT
public:
    /*! Constructs a new TextGoToLineWidget. */
    explicit TextGoToLineWidget(QWidget *parent = nullptr);
    /*! Destroys the widget. */
    ~TextGoToLineWidget() override;

    /*! Opens the dialog to enter a line number to go to. */
    void goToLine();

    /*! Sets the maximum line count for validation. */
    void setMaximumLineCount(int max);
Q_SIGNALS:
    /*! Emitted when the user wants to move to a specific line. */
    void moveToLine(int);
    /*! Emitted when the user wants to hide the go-to-line widget. */
    void hideGotoLine();

protected:
    /*! Handles events. */
    bool event(QEvent *e) override;
    /*! Handles the show event. */
    void showEvent(QShowEvent *e) override;
    /*! Filters events for the parent widget. */
    bool eventFilter(QObject *obj, QEvent *event) override;

public:
    /*! Called when the block count of the text document changes. */
    void slotBlockCountChanged(int numberBlockCount);

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotCloseBar();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotGoToLine();
    std::unique_ptr<TextGoToLineWidgetPrivate> const d;
};
}
