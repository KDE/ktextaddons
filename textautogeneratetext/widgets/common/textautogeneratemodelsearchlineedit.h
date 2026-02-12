/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QLineEdit>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit
 * \brief The TextAutoGenerateModelSearchLineEdit class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateModelSearchLineEdit
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateModelSearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateModelSearchLineEdit(QWidget *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateModelSearchLineEdit() override;
};
}
