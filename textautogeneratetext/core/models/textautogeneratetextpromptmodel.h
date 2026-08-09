/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
#include <TextAutoGenerateText/TextAutoGeneratePrompt>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextPromptModel
 * \brief The TextAutoGenerateTextPromptModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextPromptModel
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextPromptModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PromptRoles : uint16_t {
        Name = Qt::UserRole + 1,
        Description,
        PromptText,
        Enabled,
        Category,
    };
    /*!
     * Constructs a new TextAutoGenerateTextPromptModel object.
     * \param parent The parent QObject
     */
    explicit TextAutoGenerateTextPromptModel(QObject *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateTextPromptModel object.
     */
    ~TextAutoGenerateTextPromptModel() override;

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
     * \brief prompt
     * \return
     */
    [[nodiscard]] QList<TextAutoGeneratePrompt> prompt() const;
    /*!
     * \brief setPrompt
     * \param newPrompt
     */
    void setPrompt(const QList<TextAutoGeneratePrompt> &newPrompt);

    /*!
     * \brief addPrompt
     * \param newPrompt
     */
    void addPrompt(const TextAutoGeneratePrompt &newPrompt);

private:
    QList<TextAutoGeneratePrompt> mPrompt;
};
}
