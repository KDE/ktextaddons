/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "grammalecteresultjob.h"
#include "textgrammarcheck_export.h"
#include <TextGrammarCheck/GrammarResultWidget>
namespace TextGrammarCheck
{
class GrammalecteResultJob;
/*!
 * \class TextGrammarCheck::GrammalecteResultWidget
 * \inheaderfile TextGrammarCheck/GrammalecteResultWidget
 * \inmodule TextGrammarCheck
 * \brief Widget displaying Grammalecte grammar check results.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT GrammalecteResultWidget : public GrammarResultWidget
{
    Q_OBJECT
public:
    /*! Constructs a new GrammalecteResultWidget. */
    explicit GrammalecteResultWidget(QWidget *parent = nullptr);
    /*! Destroys the widget. */
    ~GrammalecteResultWidget() override;
    /*! Checks the grammar of the text. */
    void checkGrammar() override;

private:
    TEXTGRAMMARCHECK_NO_EXPORT void slotCheckGrammarFinished(const QString &result);
    TEXTGRAMMARCHECK_NO_EXPORT void slotError(GrammalecteResultJob::ErrorType error);
};
}
