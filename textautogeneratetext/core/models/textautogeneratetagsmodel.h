/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
#include <TextAutoGenerateText/TextAutoGenerateTag>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTagsModel
 * \brief The TextAutoGenerateTagsModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTagsModel
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTagsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /*!
     * \brief The TagRoles enum
     */
    enum TagRoles : uint16_t {
        Name = Qt::UserRole + 1,
        Identifier,
        Color,
    };
    /*!
     * Constructs a new TextAutoGenerateTagsModel object.
     * \param parent The parent QObject
     */
    explicit TextAutoGenerateTagsModel(QObject *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateTagsModel object.
     */
    ~TextAutoGenerateTagsModel() override;

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
     * \brief tags
     * \return
     */
    [[nodiscard]] QList<TextAutoGenerateTag> tags() const;

    /*!
     * \brief setTags
     * \param newTags
     */
    void setTags(const QList<TextAutoGenerateTag> &newTags);

    /*!
     * \brief addTag
     * \param newTag
     */
    void addTag(const TextAutoGenerateTag &newTag);

    /*!
     * \brief removeTag
     * \param identifier
     */
    void removeTag(const QByteArray &identifier);

    /*!
     * \brief updateTag Replaces the tag which has the same identifier.
     * \param tag
     */
    void updateTag(const TextAutoGenerateTag &tag);

    /*!
     * \brief clear Removes all tags.
     */
    void clear();

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT int indexFromIdentifier(const QByteArray &identifier) const;
    QList<TextAutoGenerateTag> mTags;
};
}
