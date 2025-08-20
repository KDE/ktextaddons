/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
#include <TextAutoGenerateText/TextAutoGenerateTextClient>
namespace TextAutoGenerateText
{
class TextAutoGenerateAddInstanceWidget;
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateAddInstanceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAddInstanceDialog(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateAddInstanceDialog() override;

    [[nodiscard]] TextAutoGenerateTextClient::SupportedServer selectedInstanceType() const;
    [[nodiscard]] QString instanceName() const;
    void setInstanceDisplayNames(const QStringList &lst);

private:
    TextAutoGenerateAddInstanceWidget *const mTextAutoGenerateAddInstanceWidget;
};
}
