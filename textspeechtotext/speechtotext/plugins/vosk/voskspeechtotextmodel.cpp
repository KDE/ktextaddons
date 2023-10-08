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

int VoskSpeechToTextModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mSpeechToTextInfo.count();
}

QVariant VoskSpeechToTextModel::data(const QModelIndex &index, int role) const
{
    // TODO
    return {};
}

void VoskSpeechToTextModel::clear()
{
    // TODO
}

#include "moc_voskspeechtotextmodel.cpp"
