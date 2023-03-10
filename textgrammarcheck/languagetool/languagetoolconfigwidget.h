/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QWidget>
class QCheckBox;
class QLineEdit;
class QLabel;
namespace TextGrammarCheck
{
class LanguageToolComboBox;
class LanguageToolUpdateComboBox;
class TEXTGRAMMARCHECK_EXPORT LanguageToolConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LanguageToolConfigWidget(QWidget *parent = nullptr);
    ~LanguageToolConfigWidget() override;
    void loadSettings();
    void saveSettings();

Q_SIGNALS:
    void resetValue();

private:
    Q_DISABLE_COPY(LanguageToolConfigWidget)
    void updateWidgets(bool enabled);
    void slotResetValue();
    QCheckBox *const mUseLocalInstance;
    QLineEdit *const mInstancePath;
    QLabel *const mInstancePathLabel;
    LanguageToolComboBox *const mLanguageToolCombobox;
    LanguageToolUpdateComboBox *const mLanguageToolUpdateCombobox;
};
}
