/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
#include <memory>
namespace TextAutoGenerateText
{
class TextAutogenerateEnginePluginPrivate;
/**
 * @brief The TextAutogenerateEnginePlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateEnginePlugin : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateEnginePlugin(QObject *parent = nullptr);
    ~TextAutoGenerateEnginePlugin() override;

private:
    std::unique_ptr<TextAutogenerateEnginePluginPrivate> const d;
};
}
