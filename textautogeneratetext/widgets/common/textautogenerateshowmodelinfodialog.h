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
     * \brief TextAutoGenerateShowModelInfoDialog
     * \param parent
     */
    explicit TextAutoGenerateShowModelInfoDialog(QWidget *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateShowModelInfoDialog() override;

    /*!
     * \brief setText
     * \param text
     */
    void setText(const QString &text);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TextAutoGenerateShowModelInfoWidget *const mTextAutoGenerateShowModelInfoWidget;
};
}
