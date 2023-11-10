/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QComboBox>
namespace TextGrammarCheck
{
class LanguageInfo;
class TEXTGRAMMARCHECK_EXPORT LanguageToolComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit LanguageToolComboBox(QWidget *parent = nullptr);
    ~LanguageToolComboBox() override;

    void setLanguage(const QString &str);
    [[nodiscard]] QString language() const;

    void fillComboBox(const QVector<LanguageInfo> &info);

private:
    TEXTGRAMMARCHECK_NO_EXPORT void fillComboBox();
    Q_DISABLE_COPY(LanguageToolComboBox)
};
}
