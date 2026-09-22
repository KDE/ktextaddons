/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateProject>
namespace TextAutoGenerateText
{
class TextAutoGenerateProjectsModel;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateProjectsManager
 * \brief The TextAutoGenerateProjectsManager class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateProject
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateProjectsManager
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateProjectsManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief TextAutoGenerateProjectsManager
     * \param parent
     */
    explicit TextAutoGenerateProjectsManager(QObject *parent = nullptr);
    /*!
     * \brief ~TextAutoGenerateProjectsManager
     */
    ~TextAutoGenerateProjectsManager() override;

    /*!
     * \brief setProjects
     * \param newProjects
     */
    void setProjects(const QList<TextAutoGenerateProject> &newProjects);

    /*!
     * \brief addProject
     * \param newProject
     */
    void addProject(const TextAutoGenerateProject &newProject);

    /*!
     * \brief removeProject
     * \param identifier
     */
    void removeProject(const QByteArray &identifier);

    /*!
     * \brief updateProject Replaces the project which has the same identifier.
     * \param project
     */
    void updateProject(const TextAutoGenerateProject &project);

    /*!
     * \brief projects
     * \return the list of known projects.
     */
    [[nodiscard]] QList<TextAutoGenerateProject> projects() const;

    /*!
     * \brief textAutoGenerateProjectsModel
     * \return the model which stores the projects.
     */
    [[nodiscard]] TextAutoGenerateProjectsModel *textAutoGenerateProjectsModel() const;

    /*!
     * \brief name
     * \param identifier
     * \return the name of the project, or an empty string when it is unknown.
     */
    [[nodiscard]] QString name(const QByteArray &identifier) const;

    /*!
     * \brief color
     * \param identifier
     * \return
     */
    [[nodiscard]] QColor color(const QByteArray &identifier) const;

private:
    TextAutoGenerateProjectsModel *const mTextAutoGenerateProjectsModel;
};
}
