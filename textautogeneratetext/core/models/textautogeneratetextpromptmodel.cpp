/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextpromptmodel.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextPromptModel::TextAutoGenerateTextPromptModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateTextPromptModel::~TextAutoGenerateTextPromptModel() = default;

int TextAutoGenerateTextPromptModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mPrompt.count();
}

QVariant TextAutoGenerateTextPromptModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mPrompt.count()) {
        return {};
    }
    const auto &instance = mPrompt[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    default:
        break;
    }
    return {};
}

#include "moc_textautogeneratetextpromptmodel.cpp"
