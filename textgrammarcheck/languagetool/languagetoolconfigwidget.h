/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \class TextGrammarCheck::LanguageToolConfigWidget
 * \inheaderfile TextGrammarCheck/LanguageToolConfigWidget
 * \inmodule TextGrammarCheck
 * \brief Configuration widget for LanguageTool grammar checker.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT LanguageToolConfigWidget : public QWidget
{
    Q_OBJECT
public:
    /*! Constructs a new LanguageToolConfigWidget. */
    explicit LanguageToolConfigWidget(QWidget *parent = nullptr);
    /*! Destroys the widget. */
    ~LanguageToolConfigWidget() override;
    /*! Loads the current settings from the configuration. */
    void loadSettings();
    /*! Saves the current settings to the configuration. */
    void saveSettings();

Q_SIGNALS:
    /*! Emitted when the user requests to reset values to defaults. */
    void resetValue();

private:
    Q_DISABLE_COPY(LanguageToolConfigWidget)
    TEXTGRAMMARCHECK_NO_EXPORT void updateWidgets(bool enabled);
    TEXTGRAMMARCHECK_NO_EXPORT void slotResetValue();
    QCheckBox *const mUseLocalInstance;
    QLineEdit *const mInstancePath;
    QLabel *const mInstancePathLabel;
    LanguageToolComboBox *const mLanguageToolCombobox;
    LanguageToolUpdateComboBox *const mLanguageToolUpdateCombobox;
};
}
