/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateprojectsmodel.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateProjectsModel::TextAutoGenerateProjectsModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateProjectsModel::~TextAutoGenerateProjectsModel() = default;

int TextAutoGenerateProjectsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mProjects.count();
}

QVariant TextAutoGenerateProjectsModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (row < 0 || row >= mProjects.count()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Invalid index:" << row;
        return {};
    }
    const auto &project = mProjects[row];
    switch (role) {
    case Qt::DisplayRole:
    case Name:
        return project.name();
    case Identifier:
        return project.identifier();
        // TODO add icon
    default:
        break;
    }
    return {};
}

QString TextAutoGenerateProjectsModel::nameFromIdentifier(const QByteArray &identifier) const
{
    if (const int i = indexFromIdentifier(identifier); i != -1) {
        return mProjects.at(i).name();
    }
    return {};
}

QString TextAutoGenerateProjectsModel::iconName(const QByteArray &identifier) const
{
    if (const int i = indexFromIdentifier(identifier); i != -1) {
        return mProjects.at(i).iconName();
    }
    return {};
}

QList<TextAutoGenerateProject> TextAutoGenerateProjectsModel::projects() const
{
    return mProjects;
}

void TextAutoGenerateProjectsModel::setProjects(const QList<TextAutoGenerateProject> &newProjects)
{
    beginResetModel();
    mProjects = newProjects;
    endResetModel();
}

void TextAutoGenerateProjectsModel::addProject(const TextAutoGenerateProject &newProject)
{
    beginInsertRows(QModelIndex(), mProjects.count(), mProjects.count());
    mProjects.append(newProject);
    endInsertRows();
}

void TextAutoGenerateProjectsModel::removeProject(const QByteArray &identifier)
{
    if (const int i = indexFromIdentifier(identifier); i != -1) {
        beginRemoveRows(QModelIndex(), i, i);
        mProjects.removeAt(i);
        endRemoveRows();
    }
}

void TextAutoGenerateProjectsModel::updateProject(const TextAutoGenerateProject &project)
{
    const int i = indexFromIdentifier(project.identifier());
    if (i == -1) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Unable to find project with identifier:" << project.identifier();
        return;
    }
    mProjects[i] = project;
    const QModelIndex idx = index(i, 0);
    Q_EMIT dataChanged(idx, idx);
}

void TextAutoGenerateProjectsModel::clear()
{
    if (mProjects.isEmpty()) {
        return;
    }
    beginResetModel();
    mProjects.clear();
    endResetModel();
}

int TextAutoGenerateProjectsModel::indexFromIdentifier(const QByteArray &identifier) const
{
    if (identifier.isEmpty()) {
        return -1;
    }
    const auto matchesIdentifier = [&](const TextAutoGenerateProject &project) {
        return project.identifier() == identifier;
    };
    const auto projectIt = std::find_if(mProjects.constBegin(), mProjects.constEnd(), matchesIdentifier);
    if (projectIt == mProjects.constEnd()) {
        return -1;
    }
    return std::distance(mProjects.constBegin(), projectIt);
}

#include "moc_textautogenerateprojectsmodel.cpp"
