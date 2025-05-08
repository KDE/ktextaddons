/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
namespace TextAutogenerateText
{
class TextAutoGenerateTextPlugin;
/**
 * @brief The TextAutogenerateTextClient class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextClient : public QObject
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

    explicit TextAutoGenerateTextClient(QObject *parent = nullptr);
    ~TextAutoGenerateTextClient() override;

    /**
     * @returns the name of the implementing class.
     */
    [[nodiscard]] virtual QString name() const = 0;

    [[nodiscard]] virtual QString translatedName() const = 0;

    [[nodiscard]] virtual QString webSite() const = 0;

    virtual TextAutoGenerateTextPlugin *createTextAutogeneratePlugin() = 0;

    [[nodiscard]] virtual bool hasConfigurationDialog() const;

    [[nodiscard]] virtual bool showConfigureDialog(QWidget *parentWidget);

    [[nodiscard]] virtual TextAutogenerateText::TextAutoGenerateTextClient::EngineType engineType() const = 0;

    [[nodiscard]] static QString convertEngineType(TextAutogenerateText::TextAutoGenerateTextClient::EngineType type);

    [[nodiscard]] virtual QString modelName() const = 0;

Q_SIGNALS:
    void configureChanged();
};
}
Q_DECLARE_INTERFACE(TextAutogenerateText::TextAutoGenerateTextClient, "org.kde.textautogeneratetext.client")
