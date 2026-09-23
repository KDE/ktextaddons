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
 * \class TextAutoGenerateText::TextAutoGenerateProject
 * \brief The TextAutoGenerateProject class
 *
 * A project groups chats in a folder of the history, as a chat belongs to at most one project.
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateProject
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateProject
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateProject
{
public:
    /*!
     * \brief TextAutoGenerateProject
     */
    TextAutoGenerateProject();

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
     * Compares this TextAutoGenerateProject with another object for equality.
     * \param other The TextAutoGenerateProject object to compare with
     * \return true if both objects are equal, false otherwise
     */
    [[nodiscard]] bool operator==(const TextAutoGenerateProject &other) const;

    /*!
     * Serializes the given TextAutoGenerateProject object.
     * \param project The TextAutoGenerateProject object to serialize
     * \param toBinary true to serialize to binary format, false for JSON format
     * \return The serialized data as a QByteArray
     */
    static QByteArray serialize(const TextAutoGenerateProject &project, bool toBinary = true);
    /*!
     * Deserializes a TextAutoGenerateProject object from JSON.
     * \param source The JSON object to deserialize from
     * \return The deserialized TextAutoGenerateProject object
     */
    [[nodiscard]] static TextAutoGenerateProject deserialize(const QJsonObject &source);

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
    QByteArray mIdentifier;
    QString mIconName;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateProject, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateProject &t);
