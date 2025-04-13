/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
namespace TextAutogenerateText
{
class TextAutogenerateTextPlugin;
/**
 * @brief The TextAutogenerateTextClient class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateTextClient : public QObject
{
    Q_OBJECT
public:
    enum class EngineType : uint8_t {
        Local,
        Network,
    };

    // Add more status
    enum class Status : uint8_t {
        Unknown,
        Broken,
    };

    explicit TextAutogenerateTextClient(QObject *parent = nullptr);
    ~TextAutogenerateTextClient() override;

    /**
     * @returns the name of the implementing class.
     */
    [[nodiscard]] virtual QString name() const = 0;

    [[nodiscard]] virtual QString translatedName() const = 0;

    [[nodiscard]] virtual QString webSite() const = 0;

    virtual TextAutogenerateTextPlugin *createTextAutogeneratePlugin() = 0;

    [[nodiscard]] virtual bool hasConfigurationDialog() const;

    [[nodiscard]] virtual bool showConfigureDialog(QWidget *parentWidget);

    [[nodiscard]] virtual TextAutogenerateText::TextAutogenerateTextClient::EngineType engineType() const = 0;

    [[nodiscard]] static QString convertEngineType(TextAutogenerateText::TextAutogenerateTextClient::EngineType type);

    [[nodiscard]] virtual QString modelName() const = 0;

Q_SIGNALS:
    void configureChanged();
};
}
Q_DECLARE_INTERFACE(TextAutogenerateText::TextAutogenerateTextClient, "org.kde.textautogeneratetext.client")
