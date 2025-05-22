/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "ollamamodelinfo.h"

#include <QAbstractListModel>

class OllamaModelInfosModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit OllamaModelInfosModel(QObject *parent = nullptr);
    ~OllamaModelInfosModel() override;

    [[nodiscard]] QList<OllamaModelInfo> modelInfos() const;
    void setModelInfos(const QList<OllamaModelInfo> &newModelInfos);

private:
    QList<OllamaModelInfo> mModelInfos;
};
