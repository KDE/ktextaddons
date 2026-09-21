/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QObject>
namespace TextAutoGenerateText
{
class TextAutoGenerateTagsModel;
class TextAutoGenerateTag;
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

private:
    TextAutoGenerateTagsModel *const mTextAutoGenerateTagsModel;
};
}
