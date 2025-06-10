/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextInstance>

namespace TextAutoGenerateText
{
class TextAutoGenerateTextInstanceModel;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstancesManager : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstancesManager(QObject *parent = nullptr);
    ~TextAutoGenerateTextInstancesManager() override;

    [[nodiscard]] QList<TextAutoGenerateTextInstance> instances() const;
    void setInstances(const QList<TextAutoGenerateTextInstance> &newInstances);

    void deleteInstance(const QByteArray &uuid);
    void addInstance(const TextAutoGenerateTextInstance &instance);

    void loadInstances();

    void saveInstances();

    [[nodiscard]] TextAutoGenerateTextInstanceModel *textAutoGenerateTextInstanceModel() const;

private:
    TextAutoGenerateTextInstanceModel *const mTextAutoGenerateTextInstanceModel;
};
}
