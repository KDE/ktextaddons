/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGenerateTextClient>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextInstanceComboBox;
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateAddInstanceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAddInstanceWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateAddInstanceWidget() override;

    [[nodiscard]] TextAutoGenerateTextClient::SupportedServer selectedInstanceType() const;

private:
    TextAutoGenerateTextInstanceComboBox *const mInstanceComboBox;
};
}
