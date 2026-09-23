/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateprojectsmanager.h"
#include "core/models/textautogenerateprojectsmodel.h"

using namespace TextAutoGenerateText;
TextAutoGenerateProjectsManager::TextAutoGenerateProjectsManager(QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateProjectsModel(new TextAutoGenerateProjectsModel(this))
{
}

TextAutoGenerateProjectsManager::~TextAutoGenerateProjectsManager() = default;

void TextAutoGenerateProjectsManager::setProjects(const QList<TextAutoGenerateProject> &newProjects)
{
    mTextAutoGenerateProjectsModel->setProjects(newProjects);
}

void TextAutoGenerateProjectsManager::addProject(const TextAutoGenerateProject &newProject)
{
    mTextAutoGenerateProjectsModel->addProject(newProject);
}

void TextAutoGenerateProjectsManager::removeProject(const QByteArray &identifier)
{
    mTextAutoGenerateProjectsModel->removeProject(identifier);
}

void TextAutoGenerateProjectsManager::updateProject(const TextAutoGenerateProject &project)
{
    mTextAutoGenerateProjectsModel->updateProject(project);
}

QList<TextAutoGenerateProject> TextAutoGenerateProjectsManager::projects() const
{
    return mTextAutoGenerateProjectsModel->projects();
}

TextAutoGenerateProjectsModel *TextAutoGenerateProjectsManager::textAutoGenerateProjectsModel() const
{
    return mTextAutoGenerateProjectsModel;
}

QString TextAutoGenerateProjectsManager::name(const QByteArray &identifier) const
{
    return mTextAutoGenerateProjectsModel->nameFromIdentifier(identifier);
}

QString TextAutoGenerateProjectsManager::iconName(const QByteArray &identifier) const
{
    return mTextAutoGenerateProjectsModel->iconName(identifier);
}

#include "moc_textautogenerateprojectsmanager.cpp"
