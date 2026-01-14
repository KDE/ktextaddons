/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamaonline_export.h"

#include <QString>
#include <QUrl>
class QDebug;
class TEXTAUTOGENERATEOLLAMAONLINE_EXPORT OllamaOnlineSettings
{
public:
    OllamaOnlineSettings();
    ~OllamaOnlineSettings();

    [[nodiscard]] QString currentModel() const;
    void setCurrentModel(const QString &newCurrentModel);

    [[nodiscard]] QUrl serverUrl() const;
    void setServerUrl(const QUrl &newServerUrl);

    [[nodiscard]] QString displayName() const;
    void setDisplayName(const QString &newName);

private:
    QString mDisplayName;
    QUrl mServerUrl;
    QString mDefaultModelPath;
    QString mCurrentModel;
};
TEXTAUTOGENERATEOLLAMAONLINE_EXPORT QDebug operator<<(QDebug d, const OllamaOnlineSettings &t);
