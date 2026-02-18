/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextInstancesManagerWidget;
class TextAutoGenerateManager;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextInstancesManagerDialog
 * \brief The TextAutoGenerateTextInstancesManagerDialog class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextInstancesManagerDialog
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstancesManagerDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for TextAutoGenerateTextInstancesManagerDialog
     * \param manager The TextAutoGenerateManager instance
     * \param parent The parent widget
     */
    explicit TextAutoGenerateTextInstancesManagerDialog(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    /*!
     * \brief Destructor for TextAutoGenerateTextInstancesManagerDialog
     */
    ~TextAutoGenerateTextInstancesManagerDialog() override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAccept();
    TextAutoGenerateTextInstancesManagerWidget *const mTextAutoGenerateTextInstancesManagerWidget;
};
}
