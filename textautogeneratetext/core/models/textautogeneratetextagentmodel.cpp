/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextagentmodel.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextAgentModel::TextAutoGenerateTextAgentModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateTextAgentModel::~TextAutoGenerateTextAgentModel() = default;

int TextAutoGenerateTextAgentModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mAgents.count();
}

QVariant TextAutoGenerateTextAgentModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (row < 0 || row >= mAgents.count()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Invalid index:" << row;
        return {};
    }
    const auto &item = mAgents[row];
    switch (role) {
    case Qt::DisplayRole:
    case Name:
        return item.name();
    case Description:
        return item.description();
    case Identifier:
        return item.identifier();
    case Agent:
        return QVariant::fromValue(item);
    default:
        break;
    }
    return {};
}

QList<TextAutoGenerateAgent> TextAutoGenerateTextAgentModel::agents() const
{
    return mAgents;
}

void TextAutoGenerateTextAgentModel::setAgents(const QList<TextAutoGenerateAgent> &newAgents)
{
    beginResetModel();
    mAgents = newAgents;
    endResetModel();
}

int TextAutoGenerateTextAgentModel::indexFromIdentifier(const QByteArray &identifier) const
{
    if (identifier.isEmpty()) {
        return -1;
    }
    const auto matchesIdentifier = [&](const TextAutoGenerateAgent &agent) {
        return agent.identifier() == identifier;
    };
    const auto it = std::find_if(mAgents.constBegin(), mAgents.constEnd(), matchesIdentifier);
    if (it == mAgents.constEnd()) {
        return -1;
    }
    return std::distance(mAgents.constBegin(), it);
}

void TextAutoGenerateTextAgentModel::updateAgent(const TextAutoGenerateAgent &agent)
{
    const int i = indexFromIdentifier(agent.identifier());
    if (i == -1) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Unable to find agent with identifier:" << agent.identifier();
        return;
    }
    mAgents[i] = agent;
    const QModelIndex idx = index(i, 0);
    Q_EMIT dataChanged(idx, idx);
}

void TextAutoGenerateTextAgentModel::addAgent(const TextAutoGenerateAgent &newAgent)
{
    beginInsertRows(QModelIndex(), mAgents.count(), mAgents.count());
    mAgents.append(newAgent);
    endInsertRows();
}

void TextAutoGenerateTextAgentModel::removeAgent(const QByteArray &identifier)
{
    const int i = indexFromIdentifier(identifier);
    if (i != -1) {
        beginRemoveRows(QModelIndex(), i, i);
        mAgents.removeAt(i);
        endRemoveRows();
    }
}

#include "moc_textautogeneratetextagentmodel.cpp"
