/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QColor>
#include <QString>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTag
 * \brief The TextAutoGenerateTag class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateTag
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTag
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTag
{
public:
    /*!
     * \brief TextAutoGenerateTag
     */
    TextAutoGenerateTag();

    /*!
     * \brief name
     * \return
     */
    [[nodiscard]] QString name() const;
    /*!
     * \brief setName
     * \param newName
     */
    void setName(const QString &newName);

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
     * \brief color
     * \return
     */
    [[nodiscard]] QColor color() const;
    /*!
     * \brief setColor
     * \param newColor
     */
    void setColor(const QColor &newColor);

    /*!
     * Compares this TextAutoGenerateTag with another object for equality.
     * \param other The TextAutoGenerateTag object to compare with
     * \return true if both objects are equal, false otherwise
     */
    [[nodiscard]] bool operator==(const TextAutoGenerateTag &other) const;

    /*!
     * Serializes the given TextAutoGenerateTag object.
     * \param tag The TextAutoGenerateTag object to serialize
     * \param toBinary true to serialize to binary format, false for JSON format
     * \return The serialized data as a QByteArray
     */
    static QByteArray serialize(const TextAutoGenerateTag &tag, bool toBinary = true);
    /*!
     * Deserializes a TextAutoGenerateTag object from JSON.
     * \param source The JSON object to deserialize from
     * \return The deserialized TextAutoGenerateTag object
     */
    [[nodiscard]] static TextAutoGenerateTag deserialize(const QJsonObject &source);

private:
    QString mName;
    QByteArray mIdentifier;
    QColor mColor;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTag, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTag &t);
