/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
#include <QObject>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextPlugin;
class TextAutoGenerateManager;
class TextAutoGenerateTextInstance;
/**
 * @brief The TextAutoGenerateTextClient class
 * @author Laurent Montel <montel@kde.org>
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

    explicit TextAutoGenerateTextClient(QObject *parent = nullptr);
    ~TextAutoGenerateTextClient() override;

    /**
     * @returns the name of the implementing class.
     */
    [[nodiscard]] virtual QString name() const = 0;

    [[nodiscard]] virtual QString translatedName() const = 0;

    [[nodiscard]] virtual TextAutoGenerateTextPlugin *createTextAutoGeneratePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                   TextAutoGenerateText::TextAutoGenerateTextInstance *instance) = 0;

    [[nodiscard]] virtual QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> supportedServers() const = 0;

Q_SIGNALS:
    void configureChanged();
};
}
Q_DECLARE_INTERFACE(TextAutoGenerateText::TextAutoGenerateTextClient, "org.kde.textautogeneratetext.client")
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer, Q_RELOCATABLE_TYPE);
Q_DECLARE_METATYPE(TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer)
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer &t);
