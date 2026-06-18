/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "plugincommonsettings.h"
#include "textautogeneratelmstudio_export.h"
#include <QString>
#include <QUrl>
using namespace Qt::StringLiterals;
class QDebug;
class KConfigGroup;
class TEXTAUTOGENERATELMSTUDIO_EXPORT LMStudioSettings : public PluginCommonSettings
{
    Q_GADGET
public:
    LMStudioSettings();
    ~LMStudioSettings();

    void load(const KConfigGroup &config);
    void save(KConfigGroup &config);

    [[nodiscard]] QUrl serverUrl() const;
    void setServerUrl(const QUrl &newServerUrl);

    [[nodiscard]] QUrl defaultServerUrl() const;
    [[nodiscard]] bool defaultThoughtProcessing() const;

    [[nodiscard]] bool operator==(const LMStudioSettings &other) const;

private:
    QUrl mServerUrl = QUrl(u"http://127.0.0.1:1234"_s);
};
TEXTAUTOGENERATELMSTUDIO_EXPORT QDebug operator<<(QDebug d, const LMStudioSettings &t);
