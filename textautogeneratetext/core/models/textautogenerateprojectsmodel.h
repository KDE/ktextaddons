/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
#include <TextAutoGenerateText/TextAutoGenerateProject>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateProjectsModel
 * \brief The TextAutoGenerateProjectsModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateProjectsModel
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateProjectsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /*!
     * \brief The ProjectRoles enum
     */
    enum ProjectRoles : uint16_t {
        Name = Qt::UserRole + 1,
        Identifier,
        /*! The project color, or an invalid QVariant when the project has no color yet. Also exposed
         *  as Qt::DecorationRole, so that a plain view paints a color swatch without a delegate. */
        Color,
    };
    /*!
     * Constructs a new TextAutoGenerateProjectsModel object.
     * \param parent The parent QObject
     */
    explicit TextAutoGenerateProjectsModel(QObject *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateProjectsModel object.
     */
    ~TextAutoGenerateProjectsModel() override;

    /*!
     * Returns the number of rows in the model.
     * \return The row count
     */
    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;

    /*!
     * Returns the data at the given index for the specified role.
     * \param index The model index
     * \param role The data role
     * \return The data value
     */
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    /*!
     * \brief projects
     * \return
     */
    [[nodiscard]] QList<TextAutoGenerateProject> projects() const;

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
     * \brief clear Removes all projects.
     */
    void clear();

    /*!
     * \brief nameFromIdentifier
     * \param identifier
     * \return the name of the project, or an empty string when it is unknown.
     */
    [[nodiscard]] QString nameFromIdentifier(const QByteArray &identifier) const;

    /*!
     * \brief colorFromIdentifier
     * \param identifier
     * \return
     */
    [[nodiscard]] QColor colorFromIdentifier(const QByteArray &identifier) const;

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT int indexFromIdentifier(const QByteArray &identifier) const;
    QList<TextAutoGenerateProject> mProjects;
};
}
