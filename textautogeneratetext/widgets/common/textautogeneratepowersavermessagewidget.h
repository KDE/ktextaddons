/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <KMessageWidget>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGeneratePowerSaverMessageWidget
 * \brief The TextAutoGeneratePowerSaverMessageWidget class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGeneratePowerSaverMessageWidget
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGeneratePowerSaverMessageWidget : public KMessageWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for TextAutoGeneratePowerSaverMessageWidget
     * \param parent The parent widget
     */
    explicit TextAutoGeneratePowerSaverMessageWidget(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for TextAutoGeneratePowerSaverMessageWidget
     */
    ~TextAutoGeneratePowerSaverMessageWidget() override;
};
}
