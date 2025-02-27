/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
#include <memory>
namespace TextAutogenerateText
{
class TextAutogenerateEnginePluginPrivate;
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateEnginePlugin : public QObject
{
    Q_OBJECT
public:
    explicit TextAutogenerateEnginePlugin(QObject *parent = nullptr);
    ~TextAutogenerateEnginePlugin() override;

private:
    std::unique_ptr<TextAutogenerateEnginePluginPrivate> const d;
};
}
