/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
#include <TextAutoGenerateText/TextAutoGenerateAgent>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextAgentModel
 * \brief The TextAutoGenerateTextAgentModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextAgentModel
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextAgentModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /*!
     * \brief The AgentRoles enum
     */
    enum AgentRoles : uint16_t {
        Name = Qt::UserRole + 1,
        Description,
        Identifier,
        Agent,
    };
    /*!
     * Constructs a new TextAutoGenerateTextAgentModel object.
     * \param parent The parent QObject
     */
    explicit TextAutoGenerateTextAgentModel(QObject *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateTextAgentModel object.
     */
    ~TextAutoGenerateTextAgentModel() override;

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
     * \brief agents
     * \return
     */
    [[nodiscard]] QList<TextAutoGenerateAgent> agents() const;
    /*!
     * \brief setAgents
     * \param newAgents
     */
    void setAgents(const QList<TextAutoGenerateAgent> &newAgents);

    /*!
     * \brief addAgent
     * \param newAgent
     */
    void addAgent(const TextAutoGenerateAgent &newAgent);

    /*!
     * \brief removeAgent
     * \param identifier
     */
    void removeAgent(const QByteArray &identifier);

    /*!
     * \brief updateAgent
     * \param agent
     */
    void updateAgent(const TextAutoGenerateAgent &agent);

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT int indexFromIdentifier(const QByteArray &identifier) const;
    QList<TextAutoGenerateAgent> mAgents;
};
}
