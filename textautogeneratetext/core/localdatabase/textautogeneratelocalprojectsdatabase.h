/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QSqlTableModel>
#include <TextAutoGenerateText/TextAutoGenerateLocalDatabaseAbstract>
#include <TextAutoGenerateText/TextAutoGenerateProject>

namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateLocalProjectsDatabase
 * \brief The TextAutoGenerateLocalProjectsDatabase class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateLocalProjectsDatabase
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateLocalProjectsDatabase : public TextAutoGenerateText::TextAutoGenerateLocalDatabaseAbstract
{
public:
    TextAutoGenerateLocalProjectsDatabase();
    ~TextAutoGenerateLocalProjectsDatabase() override;

    /*! Removes the project identified by \a projectId from the database. */
    void deleteProject(const QByteArray &projectId);
    /*! Inserts \a project in the database, or replaces it when it is already stored. */
    void insertOrUpdateProject(const TextAutoGenerateProject &project);

    /*! Returns all the projects stored in the database. */
    [[nodiscard]] QList<TextAutoGenerateProject> loadProjects() const;
    /*! Returns a table model on the PROJECTS table, or a null pointer when the database doesn't exist yet. */
    [[nodiscard]] std::unique_ptr<QSqlTableModel> createProjectsModel() const;

protected:
    [[nodiscard]] QString schemaDataBase() const override;

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT static QString generateQueryStr();
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateProject convertJsonToProject(const QString &json) const;
};
}
