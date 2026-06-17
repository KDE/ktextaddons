/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogenerateplugincommon_export.h"
#include <QString>
#include <QUrl>
class TEXTAUTOGENERATEPLUGINCOMMON_EXPORT PluginCommonSettings
{
    Q_GADGET
public:
    enum class ShareNameType : uint8_t {
        DoNotShare = 0,
        UserName,
        FullName,
    };
    Q_ENUM(ShareNameType)

    PluginCommonSettings();
    ~PluginCommonSettings();

    [[nodiscard]] PluginCommonSettings::ShareNameType shareNameType() const;
    void setShareNameType(const PluginCommonSettings::ShareNameType &newShareNameType);
    [[nodiscard]] ShareNameType defaultShareNameType() const;

    [[nodiscard]] static PluginCommonSettings::ShareNameType convertShareNameTypeFromString(const QString &str);
    [[nodiscard]] static QString convertShareNameTypeToString(PluginCommonSettings::ShareNameType type);

    [[nodiscard]] bool thoughtProcessing() const;
    void setThoughtProcessing(bool newThoughtProcessing);

    [[nodiscard]] QString displayName() const;
    void setDisplayName(const QString &newName);

    [[nodiscard]] QString currentModel() const;
    void setCurrentModel(const QString &newCurrentModel);

protected:
    PluginCommonSettings::ShareNameType mShareNameType = ShareNameType::DoNotShare;
    QString mDisplayName;
    QString mCurrentModel;
    bool mThoughtProcessing = false;
};
