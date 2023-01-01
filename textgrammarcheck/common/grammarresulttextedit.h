/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "grammarerror.h"
#include "textgrammarcheck_export.h"
#include <QTextEdit>
namespace TextGrammarCheck
{
class GrammarAction;
class TEXTGRAMMARCHECK_EXPORT GrammarResultTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit GrammarResultTextEdit(QWidget *parent = nullptr);
    ~GrammarResultTextEdit() override;

    void applyGrammarResult(const QVector<GrammarError> &infos);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    bool event(QEvent *ev) override;
Q_SIGNALS:
    void replaceText(const TextGrammarCheck::GrammarAction &act);
    void checkAgain();
    void closeChecker();
    void configure();

private:
    Q_DISABLE_COPY(GrammarResultTextEdit)
    void slotReplaceWord(const TextGrammarCheck::GrammarAction &act, const QString &replacementWord);
    void slotOpenGrammarUrlInfo(const QString &url);
    void generalPaletteChanged();
    QColor mTextColor;
    QColor mNegativeTextColor;
};
}
