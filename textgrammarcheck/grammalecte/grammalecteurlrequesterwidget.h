/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheckprivate_export.h"
#include <QWidget>
class QLineEdit;
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_TESTS_EXPORT GrammalecteUrlRequesterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GrammalecteUrlRequesterWidget(QWidget *parent = nullptr);
    ~GrammalecteUrlRequesterWidget() override;

    void setPath(const QString &path);
    [[nodiscard]] QString path() const;

    void setPlaceholderText(const QString &text);

private:
    QLineEdit *const mLineEdit;
};
}
