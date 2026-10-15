/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
#include <TextAutoGenerateText/TextAutoGenerateSkill>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextSkillModel
 * \brief The TextAutoGenerateTextSkillModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextSkillModel
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextSkillModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /*!
     * \brief The SkillRoles enum
     */
    enum SkillRoles : uint16_t {
        Name = Qt::UserRole + 1,
        Description,
        Instructions,
        Identifier,
        Skill,
    };
    /*!
     * Constructs a new TextAutoGenerateTextSkillModel object.
     * \param parent The parent QObject
     */
    explicit TextAutoGenerateTextSkillModel(QObject *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateTextSkillModel object.
     */
    ~TextAutoGenerateTextSkillModel() override;

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
     * \brief skills
     * \return
     */
    [[nodiscard]] QList<TextAutoGenerateSkill> skills() const;
    /*!
     * \brief setSkills
     * \param newSkills
     */
    void setSkills(const QList<TextAutoGenerateSkill> &newSkills);

    /*!
     * \brief addSkill
     * \param newSkill
     */
    void addSkill(const TextAutoGenerateSkill &newSkill);

    /*!
     * \brief removeSkill
     * \param identifier
     */
    void removeSkill(const QByteArray &identifier);

    /*!
     * \brief updateSkill
     * \param skill
     */
    void updateSkill(const TextAutoGenerateSkill &skill);

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT int indexFromIdentifier(const QByteArray &identifier) const;
    QList<TextAutoGenerateSkill> mSkills;
};
}
