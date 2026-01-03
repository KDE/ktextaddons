/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
/*!
 * \brief The TextAutoGenerateShowModelInfoDialog class
 * \author Laurent Montel <montel@kde.org>
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
};
}
