/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "plugincommonsettings.h"
#include "textautogeneratellamacpp_export.h"
#include <QString>
#include <QUrl>
using namespace Qt::StringLiterals;
class QDebug;
class KConfigGroup;
class TEXTAUTOGENERATELLAMACPP_EXPORT LLamaCppSettings : public PluginCommonSettings
{
    Q_GADGET
public:
    LLamaCppSettings();
    virtual ~LLamaCppSettings();

    void load(const KConfigGroup &config) override;
    void save(KConfigGroup &config) override;

    [[nodiscard]] bool operator==(const LLamaCppSettings &other) const;
};
TEXTAUTOGENERATELLAMACPP_EXPORT QDebug operator<<(QDebug d, const LLamaCppSettings &t);
