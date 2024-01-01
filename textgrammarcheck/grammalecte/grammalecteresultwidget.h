/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "grammalecteresultjob.h"
#include "textgrammarcheck_export.h"
#include <TextGrammarCheck/GrammarResultWidget>
namespace TextGrammarCheck
{
class GrammalecteResultJob;
class TEXTGRAMMARCHECK_EXPORT GrammalecteResultWidget : public GrammarResultWidget
{
    Q_OBJECT
public:
    explicit GrammalecteResultWidget(QWidget *parent = nullptr);
    ~GrammalecteResultWidget() override;
    void checkGrammar() override;

private:
    TEXTGRAMMARCHECK_NO_EXPORT void slotCheckGrammarFinished(const QString &result);
    TEXTGRAMMARCHECK_NO_EXPORT void slotError(GrammalecteResultJob::ErrorType error);
};
}
