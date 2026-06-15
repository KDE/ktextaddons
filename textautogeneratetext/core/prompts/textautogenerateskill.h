/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
class QDebig;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateSkill
 * \brief The TextAutoGenerateSkill class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateSkill
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateSkill
{
public:
    /*!
     * \brief TextAutoGenerateSkill
     */
    TextAutoGenerateSkill();
    /*!
     * \brief TextAutoGenerateSkill
     */
    ~TextAutoGenerateSkill();

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] QString description() const;
    /*!
     */
    void setDescription(const QString &newDescription);

    /*!
     */
    [[nodiscard]] QString instructions() const;
    /*!
     */
    void setInstructions(const QString &newInstructions);

private:
    QString mName;
    QString mDescription;
    QString mInstructions;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateSkill, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateSkill &t);
