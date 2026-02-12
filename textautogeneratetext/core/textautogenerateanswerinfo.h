/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QList>
#include <QSharedData>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateAnswerInfo
 * \brief The TextAutoGenerateAnswerInfo class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateAnswerInfo
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAnswerInfo : public QSharedData
{
public:
    /*!
     * Constructs a new TextAutoGenerateAnswerInfo object.
     */
    TextAutoGenerateAnswerInfo();
    /*!
     * Destroys the TextAutoGenerateAnswerInfo object.
     */
    ~TextAutoGenerateAnswerInfo();
    /*!
     * Constructs a copy of the TextAutoGenerateAnswerInfo object from another object.
     * \param other The TextAutoGenerateAnswerInfo object to copy from
     */
    explicit TextAutoGenerateAnswerInfo(const TextAutoGenerateAnswerInfo &other);

    /*!
     * Returns the name of the model.
     * \return The model name as a QString
     */
    [[nodiscard]] QString modelName() const;
    /*!
     * Sets the name of the model.
     * \param newModelName The model name to set
     */
    void setModelName(const QString &newModelName);

    /*!
     * Returns the name of the engine.
     * \return The engine name as a QString
     */
    [[nodiscard]] QString engineName() const;
    /*!
     * Sets the name of the engine.
     * \param newEngineName The engine name to set
     */
    void setEngineName(const QString &newEngineName);

    /*!
     * Returns the name of the instance.
     * \return The instance name as a QString
     */
    [[nodiscard]] QString instanceName() const;
    /*!
     * Sets the name of the instance.
     * \param newInstanceName The instance name to set
     */
    void setInstanceName(const QString &newInstanceName);

    /*!
     * Compares this TextAutoGenerateAnswerInfo with another for equality.
     * \param other The TextAutoGenerateAnswerInfo to compare with
     * \return true if both objects are equal, false otherwise
     */
    [[nodiscard]] bool operator==(const TextAutoGenerateAnswerInfo &other) const;

    /*!
     * Returns whether the answer info is valid.
     * \return true if the object is valid, false otherwise
     */
    [[nodiscard]] bool isValid() const;

    /*!
     * Serializes the given TextAutoGenerateAnswerInfo object.
     * \param translation The TextAutoGenerateAnswerInfo to serialize
     * \param o Reference to a QJsonObject where the data will be written
     */
    static void serialize(const TextAutoGenerateAnswerInfo &translation, QJsonObject &o);
    /*!
     * Deserializes a TextAutoGenerateAnswerInfo object from JSON.
     * \param o The JSON object to deserialize from
     * \return A pointer to the deserialized TextAutoGenerateAnswerInfo
     */
    [[nodiscard]] static TextAutoGenerateAnswerInfo *deserialize(const QJsonObject &o);

    /*!
     * Returns the list of tools.
     * \return A list of tool names as QByteArray
     */
    [[nodiscard]] QList<QByteArray> tools() const;
    /*!
     * Sets the list of tools.
     * \param newTools The tools to set
     */
    void setTools(const QList<QByteArray> &newTools);

private:
    QList<QByteArray> mTools;
    QString mModelName;
    QString mEngineName;
    QString mInstanceName;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAnswerInfo &t);
