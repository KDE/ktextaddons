/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamacommonmodelavailableinfo.h"
#include "ollamacommonsettings.h"
#include "textautogenerateollamacommon_export.h"
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>

namespace OllamaCommonModelUtils
{
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QString generateUserPrompt(OllamaCommonSettings::ShareNameType type);
[[nodiscard]] QString description(const QString &modelName);
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QList<OllamaCommonModelAvailableInfo>
extractAvailableModel(const TextAutoGenerateText::TextAutoGenerateManagerBase::ModelsInfo &modelinfo);
};
