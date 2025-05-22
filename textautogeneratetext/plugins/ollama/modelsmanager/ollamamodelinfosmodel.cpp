/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfosmodel.h"

OllamaModelInfosModel::OllamaModelInfosModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

OllamaModelInfosModel::~OllamaModelInfosModel() = default;

QList<OllamaModelInfo> OllamaModelInfosModel::modelInfos() const
{
    return mModelInfos;
}

void OllamaModelInfosModel::setModelInfos(const QList<OllamaModelInfo> &newModelInfos)
{
    mModelInfos = newModelInfos;
}

#include "moc_ollamamodelinfosmodel.cpp"
