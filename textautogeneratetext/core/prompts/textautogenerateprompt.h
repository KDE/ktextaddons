/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetextcore_export.h"
#include <QObject>
class KConfigGroup;
class QDebug;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGeneratePrompt
 * \brief The TextAutoGeneratePrompt class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGeneratePrompt
 */
class TEXTAUTOGENERATETEXTCORE_EXPORT TextAutoGeneratePrompt
{
    Q_GADGET
public:
    enum class Category : uint8_t {
        Unknown,
        Travel,
        Code,
        Misc,
    };
    Q_ENUM(Category)

    /*!
     * \brief TextAutoGeneratePrompt
     */
    TextAutoGeneratePrompt();

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] QString text() const;
    /*!
     */
    void setText(const QString &newText);

    /*!
     */
    [[nodiscard]] QString description() const;
    /*!
     */
    void setDescription(const QString &newDescription);

    /*!
     */
    [[nodiscard]] bool enabled() const;
    /*!
     */
    void setEnabled(bool newEnabled);

    /*!
     */
    [[nodiscard]] Category category() const;
    /*!
     */
    void setCategory(Category newCategory);

    /*!
     * \brief convertCategoryToString
     * \param c
     * \return
     */
    [[nodiscard]] static QString convertCategoryToString(Category c);
    /*!
     * \brief convertStringToCategory
     * \param str
     * \return
     */
    [[nodiscard]] static Category convertStringToCategory(const QString &str);

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
     * \brief save
     * \param config
     */
    void save(KConfigGroup &grp) const;

    /*!
     * \brief load
     * \param config
     */
    void load(const KConfigGroup &grp);

    /*!
     * \brief commandCompletion
     * \return
     */
    [[nodiscard]] QString commandCompletion() const;
    /*!
     * \brief setCommandCompletion
     * \param newCommandCompletion
     */
    void setCommandCompletion(const QString &newCommandCompletion);

    /*!
     * \brief operator ==
     * \param other
     * \return
     */
    [[nodiscard]] bool operator==(const TextAutoGeneratePrompt &other) const;

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
    Category mCategory = Category::Unknown;
    QString mName;
    QString mText;
    QString mDescription;
    QString mCommandCompletion;
    QByteArray mIdentifier;
    QString mIconName;
    bool mEnabled = true;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGeneratePrompt, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGeneratePrompt &t);
