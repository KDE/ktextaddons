/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextInstancesMcpServerWidget
 * \brief The TextAutoGenerateTextInstancesMcpServerWidget class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextInstancesMcpServerWidget
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstancesMcpServerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstancesMcpServerWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateTextInstancesMcpServerWidget() override;
};
}
