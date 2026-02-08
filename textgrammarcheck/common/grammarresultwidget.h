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
 * \class GrammarResultWidget
 * \inheaderfile TextGrammarCheck/GrammarResultWidget
 * \inmodule TextGrammarCheck
 * \brief Base widget for displaying grammar check results.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT GrammarResultWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     */
    explicit GrammarResultWidget(QWidget *parent = nullptr);
    /*!
     */
    ~GrammarResultWidget() override;
    /*!
     */
    void setText(const QString &str);
    /*!
     */
    virtual void checkGrammar() = 0;
    /*!
     */
    void applyGrammarResult(const QVector<TextGrammarCheck::GrammarError> &infos);
Q_SIGNALS:
    /*!
     */
    void replaceText(const TextGrammarCheck::GrammarAction &act);
    /*!
     */
    void checkAgain();
    /*!
     */
    void closeChecker();
    /*!
     */
    void configure();

protected:
    /*!
     */
    virtual void addExtraWidget();
    GrammarResultTextEdit *const mResult;
    QHBoxLayout *mExtraWidgetLayout = nullptr;

private:
    Q_DISABLE_COPY(GrammarResultWidget)
};
}
