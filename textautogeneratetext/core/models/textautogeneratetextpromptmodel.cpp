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
    const int row = index.row();
    if (row < 0 || row >= mPrompt.count()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Invalid index:" << row;
        return {};
    }
    const auto &prompt = mPrompt[row];
    switch (role) {
    case Qt::DisplayRole:
    case Name:
        return prompt.name();
    case Description:
        return prompt.description();
    case PromptText:
        return prompt.text();
    case Enabled:
        return prompt.enabled();
    case Category:
        return QVariant::fromValue(prompt.category());
    default:
        break;
    }
    return {};
}

QList<TextAutoGeneratePrompt> TextAutoGenerateTextPromptModel::prompt() const
{
    return mPrompt;
}

void TextAutoGenerateTextPromptModel::setPrompt(const QList<TextAutoGeneratePrompt> &newPrompt)
{
    beginResetModel();
    mPrompt = newPrompt;
    endResetModel();
}

#include "moc_textautogeneratetextpromptmodel.cpp"
