/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
class QDebug;
#include <QObject>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextPlugin;
class TextAutoGenerateManager;
class TextAutoGenerateTextInstance;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextClient
 * \brief The TextAutoGenerateTextClient class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextClient
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextClient : public QObject
{
    Q_OBJECT
public:
    // Add more status
    enum class Status : uint8_t {
        Unknown,
        Broken,
    };
    struct SupportedServer {
        QString localizedName;
        QString identifier;
        QString pluginName;
        [[nodiscard]] bool isValid() const;
    };

    /*!
     * Constructs a new TextAutoGenerateTextClient object.
     * \param parent The parent QObject
     */
    explicit TextAutoGenerateTextClient(QObject *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateTextClient object.
     */
    ~TextAutoGenerateTextClient() override;

    /*!
     * Returns the name of the implementing class.
     */
    [[nodiscard]] virtual QString name() const = 0;

    /*!
     * Returns the translated name of the implementing client.
     * \return The localized client name
     */
    [[nodiscard]] virtual QString translatedName() const = 0;

    /*!
     * Creates a TextAutoGeneratePlugin for the given manager and instance.
     * \param manager The TextAutoGenerateManager instance
     * \param instance The TextAutoGenerateTextInstance configuration
     * \return A pointer to the created TextAutoGenerateTextPlugin
     */
    [[nodiscard]] virtual TextAutoGenerateTextPlugin *createTextAutoGeneratePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                   TextAutoGenerateText::TextAutoGenerateTextInstance *instance) = 0;

    /*!
     * Returns the list of servers supported by this client.
     * \return A list of SupportedServer structures
     */
    [[nodiscard]] virtual QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> supportedServers() const = 0;

Q_SIGNALS:
    /*!
     * Emitted when the client configuration changes.
     */
    void configureChanged();
};
}
Q_DECLARE_INTERFACE(TextAutoGenerateText::TextAutoGenerateTextClient, "org.kde.textautogeneratetext.client")
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer, Q_RELOCATABLE_TYPE);
Q_DECLARE_METATYPE(TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer)
/*!
 * \relates TextAutoGenerateTextClient::SupportedServer
 * Outputs the supported server information to a debug stream.
 * \param d The debug stream
 * \param t The SupportedServer structure
 * \return The debug stream
 */
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer &t);
