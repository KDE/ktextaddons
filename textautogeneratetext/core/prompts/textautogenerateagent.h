/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetextcore_export.h"
#include <QString>
class QDebug;
class KConfigGroup;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateAgent
 * \brief The TextAutoGenerateAgent class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateAgent
 */
class TEXTAUTOGENERATETEXTCORE_EXPORT TextAutoGenerateAgent
{
public:
    /*!
     * \brief TextAutoGenerateAgent
     */
    TextAutoGenerateAgent();

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
     * \brief identifier
     * \return
     */
    [[nodiscard]] QByteArray identifier() const;
    /*!
     * \brief setIdentifier
     * \param newIdentifier
     */
    void setIdentifier(const QByteArray &newIdentifier);

    /*!
     * \brief isValid
     * \return
     */
    [[nodiscard]] bool isValid() const;

    /*!
     * \brief operator ==
     * \param other
     * \return
     */
    [[nodiscard]] bool operator==(const TextAutoGenerateAgent &other) const;

    /*!
     * \brief save
     * \param grp
     */
    void save(KConfigGroup &grp) const;

    /*!
     * \brief load
     * \param grp
     */
    void load(const KConfigGroup &grp);

    /*!
     * \brief createUniqueIdentifier
     */
    void createUniqueIdentifier();

    /*!
     * \brief iconName
     * \return
     */
    [[nodiscard]] QString iconName() const;
    /*!
     * \brief setIconName
     * \param newIconName
     */
    void setIconName(const QString &newIconName);

private:
    QString mName;
    QString mDescription;
    QByteArray mIdentifier;
    QString mIconName;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateAgent, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAgent &t);
