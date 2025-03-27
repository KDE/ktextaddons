/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "ollamarequest.h"

#include <QDebug>
#include <QObject>
class OllamaManager : public QObject
{
    Q_OBJECT
public:
    struct ModelsInfo {
        QStringList models;
        QString errorOccured;
        bool hasError = false;
        bool isReady = false;
    };

    explicit OllamaManager(QObject *parent = nullptr);
    ~OllamaManager() override;
    void loadModels();
    void getCompletion(const OllamaRequest &request);

    static OllamaManager *self();

Q_SIGNALS:
    void modelsLoadDone(const ModelsInfo &models);

private:
    QMetaObject::Connection mOllamaCheckConnect;
};
Q_DECLARE_TYPEINFO(OllamaManager::ModelsInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const OllamaManager::ModelsInfo &t);
