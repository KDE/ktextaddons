/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateShowModelInfoWidget;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateShowModelInfoDialog
 * \brief The TextAutoGenerateShowModelInfoDialog class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateShowModelInfoDialog
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateShowModelInfoDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for TextAutoGenerateShowModelInfoDialog
     * \param parent The parent widget
     */
    explicit TextAutoGenerateShowModelInfoDialog(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for TextAutoGenerateShowModelInfoDialog
     */
    ~TextAutoGenerateShowModelInfoDialog() override;

    /*!
     * \brief Sets the text to display in the model info dialog
     * \param text The text to display
     */
    void setText(const QString &text);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TextAutoGenerateShowModelInfoWidget *const mTextAutoGenerateShowModelInfoWidget;
};
}
