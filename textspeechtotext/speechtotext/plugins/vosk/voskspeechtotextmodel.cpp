/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextmodel.h"

VoskSpeechToTextModel::VoskSpeechToTextModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

VoskSpeechToTextModel::~VoskSpeechToTextModel() = default;

#include "moc_voskspeechtotextmodel.cpp"
