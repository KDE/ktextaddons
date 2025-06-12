/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QComboBox>
#include <TextAutoGenerateText/TextAutoGenerateTextClient>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextInstanceComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstanceComboBox(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateTextInstanceComboBox() override;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer selectedInstanceType() const;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void fillEngine();
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
