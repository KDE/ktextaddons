/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTag>
namespace TextAutoGenerateText
{
class TextAutoGenerateTagsModel;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTag
 * \brief The TextAutoGenerateTag class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateTag
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTag
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTagsManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief TextAutoGenerateTagsManager
     * \param parent
     */
    explicit TextAutoGenerateTagsManager(QObject *parent = nullptr);
    /*!
     * \brief ~TextAutoGenerateTagsManager
     */
    ~TextAutoGenerateTagsManager() override;

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
     * \brief tags
     * \return the list of known tags.
     */
    [[nodiscard]] QList<TextAutoGenerateTag> tags() const;

    /*!
     * \brief textAutoGenerateTagsModel
     * \return the model which stores the tags.
     */
    [[nodiscard]] TextAutoGenerateTagsModel *textAutoGenerateTagsModel() const;

    /*!
     * \brief colors
     * \param identifiers
     * \return
     */
    [[nodiscard]] QList<QColor> colors(const QList<QByteArray> &identifiers) const;

private:
    TextAutoGenerateTagsModel *const mTextAutoGenerateTagsModel;
};
}
