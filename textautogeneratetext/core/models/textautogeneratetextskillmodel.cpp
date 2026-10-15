/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextskillmodel.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextSkillModel::TextAutoGenerateTextSkillModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateTextSkillModel::~TextAutoGenerateTextSkillModel() = default;

int TextAutoGenerateTextSkillModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mSkills.count();
}

QVariant TextAutoGenerateTextSkillModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (row < 0 || row >= mSkills.count()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Invalid index:" << row;
        return {};
    }
    const auto &item = mSkills[row];
    switch (role) {
    case Qt::DisplayRole:
    case Name:
        return item.name();
    case Description:
        return item.description();
    case Instructions:
        return item.instructions();
    case Identifier:
        return item.identifier();
    case Skill:
        return QVariant::fromValue(item);
    default:
        break;
    }
    return {};
}

QList<TextAutoGenerateSkill> TextAutoGenerateTextSkillModel::skills() const
{
    return mSkills;
}

void TextAutoGenerateTextSkillModel::setSkills(const QList<TextAutoGenerateSkill> &newSkills)
{
    beginResetModel();
    mSkills = newSkills;
    endResetModel();
}

int TextAutoGenerateTextSkillModel::indexFromIdentifier(const QByteArray &identifier) const
{
    if (identifier.isEmpty()) {
        return -1;
    }
    const auto matchesIdentifier = [&](const TextAutoGenerateSkill &skill) {
        return skill.identifier() == identifier;
    };
    const auto it = std::find_if(mSkills.constBegin(), mSkills.constEnd(), matchesIdentifier);
    if (it == mSkills.constEnd()) {
        return -1;
    }
    return std::distance(mSkills.constBegin(), it);
}

void TextAutoGenerateTextSkillModel::updateSkill(const TextAutoGenerateSkill &skill)
{
    const int i = indexFromIdentifier(skill.identifier());
    if (i == -1) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Unable to find skill with identifier:" << skill.identifier();
        return;
    }
    mSkills[i] = skill;
    const QModelIndex idx = index(i, 0);
    Q_EMIT dataChanged(idx, idx);
}

void TextAutoGenerateTextSkillModel::addSkill(const TextAutoGenerateSkill &newSkill)
{
    beginInsertRows(QModelIndex(), mSkills.count(), mSkills.count());
    mSkills.append(newSkill);
    endInsertRows();
}

void TextAutoGenerateTextSkillModel::removeSkill(const QByteArray &identifier)
{
    const int i = indexFromIdentifier(identifier);
    if (i != -1) {
        beginRemoveRows(QModelIndex(), i, i);
        mSkills.removeAt(i);
        endRemoveRows();
    }
}

#include "moc_textautogeneratetextskillmodel.cpp"
