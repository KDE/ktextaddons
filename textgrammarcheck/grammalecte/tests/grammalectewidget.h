/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "common/grammaraction.h"
#include "grammalecte/grammalectegenerateconfigoptionjob.h"
#include <QWidget>
namespace TextGrammarCheck
{
class GrammalecteResultWidget;
}
class QTextEdit;
class GrammalecteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GrammalecteWidget(QWidget *parent = nullptr);
    ~GrammalecteWidget() override;

private:
    void slotReplaceText(const TextGrammarCheck::GrammarAction &act);
    void slotCheckGrammar();
    void slotGetSettings();
    void slotGetSettingsFinished(const QVector<TextGrammarCheck::GrammalecteGenerateConfigOptionJob::Option> &result);
    void slotResultFinished(const QString &result);
    void slotConfigure();
    QTextEdit *mInput = nullptr;
    TextGrammarCheck::GrammalecteResultWidget *const mResultWidget;
};
