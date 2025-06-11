/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerategenericnetwork_export.h"
#include <QObject>

class TEXTAUTOGENERATEGENERICNETWORK_EXPORT GenericNetworkManager : public QObject
{
    Q_OBJECT
public:
    enum class PluginNetworkType : uint8_t {
        Unknown = 0,
        MistralAI,
        OpenAI,
    };
    explicit GenericNetworkManager(QObject *parent = nullptr);
    ~GenericNetworkManager() override;

    [[nodiscard]] PluginNetworkType pluginNetworkType() const;
    void setPluginNetworkType(PluginNetworkType newPluginNetworkType);

private:
    PluginNetworkType mPluginNetworkType = PluginNetworkType::Unknown;
};
