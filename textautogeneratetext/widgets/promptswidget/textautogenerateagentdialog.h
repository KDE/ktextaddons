/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateAgentWidget;
class TextAutoGenerateAgent;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateAgentDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAgentDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateAgentDialog() override;

    void setAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent);
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateAgent agent() const;

private:
    TextAutoGenerateAgentWidget *const mAgentWidget;
};
}
