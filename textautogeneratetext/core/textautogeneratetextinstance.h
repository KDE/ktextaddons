/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"

#include <KConfigGroup>
class QDebug;
namespace TextAutoGenerateText
{
class TextAutoGenerateTextPlugin;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextInstance
 * \brief The TextAutoGenerateTextInstance class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextInstance
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstance
{
public:
    /*!
     * Constructs a new TextAutoGenerateTextInstance object.
     */
    TextAutoGenerateTextInstance();
    /*!
     * Destroys the TextAutoGenerateTextInstance object.
     */
    ~TextAutoGenerateTextInstance();

    /*!
     * Returns the display name of the instance.
     * \return The display name as a QString
     */
    [[nodiscard]] QString displayName() const;

    /*!
     * Returns the name of the plugin.
     * \return The plugin name as a QString
     */
    [[nodiscard]] QString pluginName() const;
    /*!
     * Sets the name of the plugin.
     * \param newPluginName The plugin name to set
     */
    void setPluginName(const QString &newPluginName);

    /*!
     * Returns whether the instance is valid.
     * \return true if the instance is valid, false otherwise
     */
    [[nodiscard]] bool isValid() const;

    /*!
     * Returns the unique identifier of the instance.
     * \return The instance UUID as a QByteArray
     */
    [[nodiscard]] QByteArray instanceUuid() const;
    /*!
     * Sets the unique identifier of the instance.
     * \param newInstanceUuid The UUID to set
     */
    void setInstanceUuid(const QByteArray &newInstanceUuid);

    /*!
     * Returns the identifier of the plugin.
     * \return The plugin identifier as a QString
     */
    [[nodiscard]] QString pluginIdentifier() const;
    /*!
     * Sets the identifier of the plugin.
     * \param newPluginIdentifier The plugin identifier to set
     */
    void setPluginIdentifier(const QString &newPluginIdentifier);

    /*!
     * Loads the instance settings from a configuration group.
     * \param config The KConfigGroup to load from
     */
    void load(const KConfigGroup &config);
    /*!
     * Saves the instance settings to a configuration group.
     * \param config The KConfigGroup to save to
     */
    void save(KConfigGroup &config);

    /*!
     * Returns the name of the currently selected model.
     * \return The model name as a QString
     */
    [[nodiscard]] QString currentModel() const;

    /*!
     * Returns the plugin instance.
     * \return A pointer to the TextAutoGenerateTextPlugin
     */
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextPlugin *plugin() const;
    /*!
     * Sets the plugin instance.
     * \param newPlugin The plugin to set
     */
    void setPlugin(TextAutoGenerateText::TextAutoGenerateTextPlugin *newPlugin);

    /*!
     * Returns whether the instance is enabled.
     * \return true if the instance is enabled, false otherwise
     */
    [[nodiscard]] bool enabled() const;
    /*!
     * Sets whether the instance is enabled.
     * \param newEnabled true to enable, false to disable
     */
    void setEnabled(bool newEnabled);

private:
    QString mPluginName;
    QString mPluginIdentifier;
    QByteArray mInstanceUuid;
    TextAutoGenerateText::TextAutoGenerateTextPlugin *mPlugin = nullptr;
    bool mEnabled = true;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextInstance, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextInstance &t);
