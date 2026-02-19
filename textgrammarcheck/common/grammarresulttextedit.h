/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "grammarerror.h"
#include "textgrammarcheck_export.h"
#include <QTextEdit>
namespace TextGrammarCheck
{
class GrammarAction;
/*!
 * \class TextGrammarCheck::GrammarResultTextEdit
 * \inheaderfile TextGrammarCheck/GrammarResultTextEdit
 * \inmodule TextGrammarCheck
 * \brief Text editor for displaying and handling grammar check results.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT GrammarResultTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    /*! Constructs a new GrammarResultTextEdit. */
    explicit GrammarResultTextEdit(QWidget *parent = nullptr);
    /*! Destroys the text editor. */
    ~GrammarResultTextEdit() override;

    /*! Applies the grammar checking results to display the errors. */
    void applyGrammarResult(const QVector<GrammarError> &infos);

protected:
    /*! Handles context menu events to display correction suggestions. */
    void contextMenuEvent(QContextMenuEvent *event) override;

    /*! Paints the widget and highlights grammar errors. */
    void paintEvent(QPaintEvent *event) override;

    /*! Handles events such as hovering over errors. */
    bool event(QEvent *ev) override;
Q_SIGNALS:
    /*! Emitted when the user wants to replace text with a suggestion. */
    void replaceText(const TextGrammarCheck::GrammarAction &act);
    /*! Emitted when the user wants to check the text again. */
    void checkAgain();
    /*! Emitted when the user wants to close the checker. */
    void closeChecker();
    /*! Emitted when the user wants to configure grammar checking settings. */
    void configure();

private:
    Q_DISABLE_COPY(GrammarResultTextEdit)
    TEXTGRAMMARCHECK_NO_EXPORT void slotReplaceWord(const TextGrammarCheck::GrammarAction &act, const QString &replacementWord);
    TEXTGRAMMARCHECK_NO_EXPORT void slotOpenGrammarUrlInfo(const QString &url);
    TEXTGRAMMARCHECK_NO_EXPORT void generalPaletteChanged();
    QColor mTextColor;
    QColor mNegativeTextColor;
};
}
