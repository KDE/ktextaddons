/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateplugincommon_export.h"
#include <QObject>
#include <QString>

class TEXTAUTOGENERATEPLUGINCOMMON_EXPORT PluginCommonSaveLoadPassword : public QObject
{
    Q_OBJECT
public:
    explicit PluginCommonSaveLoadPassword(QObject *parent);
    ~PluginCommonSaveLoadPassword() override;

    void writePassword(const QString &passwordServiceName, const QByteArray &instanceUuid, const QString &apiKey);
    void loadApiKey(const QString &passwordServiceName, const QByteArray &instanceUuid);
    void removeApiKey(const QString &passwordServiceName, const QByteArray &instanceUuid);
Q_SIGNALS:
    void loadApiKeyDone(const QString &data);
};
