/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamacloud_export.h"

#include <QString>
#include <QUrl>
class QDebug;
class TEXTAUTOGENERATEOLLAMACLOUD_EXPORT OllamaCloudSettings
{
public:
    OllamaCloudSettings();
    ~OllamaCloudSettings();

    [[nodiscard]] QString currentModel() const;
    void setCurrentModel(const QString &newCurrentModel);

    [[nodiscard]] QString displayName() const;
    void setDisplayName(const QString &newName);

private:
    QString mDisplayName;
    QString mDefaultModelPath;
    QString mCurrentModel;
};
TEXTAUTOGENERATEOLLAMACLOUD_EXPORT QDebug operator<<(QDebug d, const OllamaCloudSettings &t);
