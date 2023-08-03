/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatormodel.h"

TranslatorModel::TranslatorModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TranslatorModel::~TranslatorModel() = default;
