/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QComboBox>
namespace TextGrammarCheck
{
class LanguageInfo;
/*!
 * \class TextGrammarCheck::LanguageToolComboBox
 * \inheaderfile TextGrammarCheck/LanguageToolComboBox
 * \inmodule TextGrammarCheck
 * \brief ComboBox widget for selecting LanguageTool language.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT LanguageToolComboBox : public QComboBox
{
    Q_OBJECT
public:
    /*! Constructs a new LanguageToolComboBox. */
    explicit LanguageToolComboBox(QWidget *parent = nullptr);
    /*! Destroys the combo box. */
    ~LanguageToolComboBox() override;

    /*! Sets the currently selected language. */
    void setLanguage(const QString &str);
    /*! Returns the currently selected language. */
    [[nodiscard]] QString language() const;

    /*! Populates the combo box with the available languages. */
    void fillComboBox(const QVector<LanguageInfo> &info);

private:
    TEXTGRAMMARCHECK_NO_EXPORT void fillComboBox();
    Q_DISABLE_COPY(LanguageToolComboBox)
};
}
