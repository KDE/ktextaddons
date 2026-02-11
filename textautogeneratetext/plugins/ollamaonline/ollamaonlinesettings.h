/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "ollamacommonsettings.h"
#include "textautogenerateollamaonline_export.h"

#include <QString>
#include <QUrl>
class QDebug;
class TEXTAUTOGENERATEOLLAMAONLINE_EXPORT OllamaOnlineSettings : public OllamaCommonSettings
{
public:
    OllamaOnlineSettings();
    ~OllamaOnlineSettings();

    [[nodiscard]] QUrl serverUrl() const;
    void setServerUrl(const QUrl &newServerUrl);

private:
    QUrl mServerUrl;
};
TEXTAUTOGENERATEOLLAMAONLINE_EXPORT QDebug operator<<(QDebug d, const OllamaOnlineSettings &t);
