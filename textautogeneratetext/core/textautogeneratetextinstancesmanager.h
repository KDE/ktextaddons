/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextInstance>
class KConfig;
namespace TextAutoGenerateText
{
class TextAutoGenerateTextInstanceModel;
class TextAutoGenerateEngineLoader;
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstancesManager : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstancesManager(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent = nullptr);
    ~TextAutoGenerateTextInstancesManager() override;

    [[nodiscard]] QList<TextAutoGenerateTextInstance *> instances() const;
    void setInstances(const QList<TextAutoGenerateTextInstance *> &newInstances);

    void deleteInstance(const QByteArray &uuid);
    void addInstance(TextAutoGenerateTextInstance *instance);

    void loadInstances();

    void saveInstances();

    [[nodiscard]] TextAutoGenerateTextInstanceModel *textAutoGenerateTextInstanceModel() const;

    [[nodiscard]] bool isCurrentInstance(const QByteArray &instanceUuid) const;

    [[nodiscard]] QByteArray currentInstance() const;
    void setCurrentinstance(const QByteArray &newCurrentinstance);

    [[nodiscard]] TextAutoGenerateEngineLoader *textAutoGenerateEngineLoader() const;

    [[nodiscard]] QString configFileName() const;
    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] TextAutoGenerateTextPlugin *textAutoGeneratePlugin() const;

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QStringList groupList(KConfig *config) const;
    TextAutoGenerateTextInstanceModel *const mTextAutoGenerateTextInstanceModel;
    TextAutoGenerateEngineLoader *const mTextAutoGenerateEngineLoader;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    KConfig *const mConfig;
};
}
