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
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstanceManager : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstanceManager(QObject *parent = nullptr);
    ~TextAutoGenerateTextInstanceManager() override;

    [[nodiscard]] QList<TextAutoGenerateTextInstance> instances() const;
    void setInstances(const QList<TextAutoGenerateTextInstance> &newInstances);

    void loadInstances();

    void saveInstances();

private:
    QList<TextAutoGenerateTextInstance> mInstances;
};
}
