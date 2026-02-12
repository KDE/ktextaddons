/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "ollamacommonsettings.h"
#include "textautogenerateollamacloud_export.h"

#include <QString>
class TEXTAUTOGENERATEOLLAMACLOUD_EXPORT OllamaCloudSettings : public OllamaCommonSettings
{
public:
    OllamaCloudSettings();
    ~OllamaCloudSettings() override;

    void load(const KConfigGroup &config) override;
    void save(KConfigGroup &config) override;
};
