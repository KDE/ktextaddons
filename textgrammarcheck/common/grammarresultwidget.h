/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "grammarerror.h"
#include "textgrammarcheck_export.h"
#include <QWidget>
class QHBoxLayout;
namespace TextGrammarCheck
{
class GrammarAction;
class GrammarResultTextEdit;
/*!
 * \class TextGrammarCheck::GrammarResultWidget
 * \inheaderfile TextGrammarCheck/GrammarResultWidget
 * \inmodule TextGrammarCheck
 * \brief Base widget for displaying grammar check results.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT GrammarResultWidget : public QWidget
{
    Q_OBJECT
public:
    /*! Constructs a new GrammarResultWidget. */
    explicit GrammarResultWidget(QWidget *parent = nullptr);
    /*! Destroys the widget. */
    ~GrammarResultWidget() override;
    /*! Sets the text to be checked. */
    void setText(const QString &str);
    /*! Checks the grammar of the text. This is implemented by subclasses. */
    virtual void checkGrammar() = 0;
    /*! Applies the grammar checking results to display the errors. */
    void applyGrammarResult(const QVector<TextGrammarCheck::GrammarError> &infos);
Q_SIGNALS:
    /*! Emitted when the user wants to replace text with a suggestion. */
    void replaceText(const TextGrammarCheck::GrammarAction &act);
    /*! Emitted when the user wants to check the text again. */
    void checkAgain();
    /*! Emitted when the user wants to close the checker. */
    void closeChecker();
    /*! Emitted when the user wants to configure grammar checking settings. */
    void configure();

protected:
    /*! Adds extra widgets to the result display. Can be overridden by subclasses. */
    virtual void addExtraWidget();
    GrammarResultTextEdit *const mResult;
    QHBoxLayout *mExtraWidgetLayout = nullptr;

private:
    Q_DISABLE_COPY(GrammarResultWidget)
};
}
