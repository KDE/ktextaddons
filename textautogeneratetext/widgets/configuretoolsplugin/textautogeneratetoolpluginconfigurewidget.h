/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
class QLabel;
namespace TextAutoGenerateText
{
class TextAutoGenerateTextToolPlugin;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateToolPluginConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolPluginConfigureWidget(TextAutoGenerateTextToolPlugin *plugin, QWidget *parent = nullptr);
    ~TextAutoGenerateToolPluginConfigureWidget() override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void generateArguments(TextAutoGenerateTextToolPlugin *plugin);
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QLabel *createLabel(const QString &label);
    QLabel *const mDescriptionLabel;
    QLabel *const mArgumentsLabel;
};

}
