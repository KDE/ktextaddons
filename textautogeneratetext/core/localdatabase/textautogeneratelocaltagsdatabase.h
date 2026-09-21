/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QSqlTableModel>
#include <TextAutoGenerateText/TextAutoGenerateLocalDatabaseAbstract>
#include <TextAutoGenerateText/TextAutoGenerateTag>

namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateLocalTagsDatabase
 * \brief The TextAutoGenerateLocalTagsDatabase class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateLocalTagsDatabase
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateLocalTagsDatabase : public TextAutoGenerateText::TextAutoGenerateLocalDatabaseAbstract
{
public:
    TextAutoGenerateLocalTagsDatabase();
    ~TextAutoGenerateLocalTagsDatabase() override;

    /*! Removes the tag identified by \a tagId from the database. */
    void deleteTag(const QByteArray &tagId);
    /*! Inserts \a tag in the database, or replaces it when it is already stored. */
    void insertOrUpdateTag(const TextAutoGenerateTag &tag);

    /*! Returns all the tags stored in the database. */
    [[nodiscard]] QList<TextAutoGenerateTag> loadTags() const;
    /*! Returns a table model on the TAGS table, or a null pointer when the database doesn't exist yet. */
    [[nodiscard]] std::unique_ptr<QSqlTableModel> createTagsModel() const;

protected:
    [[nodiscard]] QString schemaDataBase() const override;

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT static QString generateQueryStr();
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateTag convertJsonToTag(const QString &json) const;
};
}
