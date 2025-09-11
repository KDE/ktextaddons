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
    explicit TextAutoGenerateToolPluginConfigureWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateToolPluginConfigureWidget() override;

    void initialize(TextAutoGenerateTextToolPlugin *plugin);

private:
    QLabel *const mDescriptionLabel;
};

}
