/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on translatelocally code
*/

#pragma once
#include "bergamotengineutils.h"
#include "libbergamot_export.h"
#include "translation.h"
#include <QList>
#include <QObject>
#include <QString>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
struct ModelDescription;
struct TranslationInput;

class LIBBERGAMOT_EXPORT BergamotMarianInterface : public QObject
{
    Q_OBJECT
public:
    explicit BergamotMarianInterface(QObject *parent = nullptr);
    ~BergamotMarianInterface() override;

    void translate(const QString &str);
    Q_REQUIRED_RESULT QString model() const;

    void setModel(const QString &pathModelDir, const BergamotEngineUtils::SettingsInfo &settings);

Q_SIGNALS:
    void translationReady(Translation translation);
    void pendingChanged(bool isBusy); // Disables issuing another translation while we are busy.
    void errorText(const QString &message);

private:
    std::unique_ptr<TranslationInput> mPendingInput;
    std::unique_ptr<ModelDescription> mPendingModel;

    std::mutex mMutex;
    std::condition_variable mConditionVariable;

    std::thread mWorke;
    QString mModelString;
    bool mPendingShutdown = false;
};
