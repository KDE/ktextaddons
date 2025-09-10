/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "core/tools/textautogeneratetexttoolplugin.h"
#include <QVariant>
class ExampleTextToolPlugin : public TextAutoGenerateText::TextAutoGenerateTextToolPlugin
{
    Q_OBJECT
public:
    explicit ExampleTextToolPlugin(QObject *parent = nullptr, const QVariantList & = {});
    ~ExampleTextToolPlugin() override;

    [[nodiscard]] QString executeTool() override;
    [[nodiscard]] QString displayName() override;
    [[nodiscard]] QString descriptions() const override;
    [[nodiscard]] QJsonObject metadata() const override;
};
