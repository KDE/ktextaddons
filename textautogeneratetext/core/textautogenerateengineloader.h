/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "core/textautogeneratetextclient.h"
#include "textautogeneratetext_export.h"
#include <QObject>
#include <memory>
namespace TextAutoGenerateText
{
class TextAutoGenerateEngineLoaderPrivate;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateEngineLoader
 * \brief The TextAutoGenerateEngineLoader class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateEngineLoader
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateEngineLoader : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for TextAutoGenerateEngineLoader
     * \param parent The parent object
     */
    explicit TextAutoGenerateEngineLoader(QObject *parent = nullptr);
    /*!
     * \brief Destructor for TextAutoGenerateEngineLoader
     */
    ~TextAutoGenerateEngineLoader() override;

    /*!
     * \brief Searches for a text auto-generate client by name
     * \param clientName The name of the client to search for
     * \return Pointer to the TextAutoGenerateTextClient, or nullptr if not found
     */
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextClient *searchTextAutoGenerateTextClient(const QString &clientName);

    /*!
     * \brief Checks if an engine is available
     * \return True if an engine is available, false otherwise
     */
    [[nodiscard]] bool hasEngine() const;

    /*!
     * \brief Loads the text auto-generate plugins
     */
    void loadPlugins();

    /*!
     * \brief Returns the list of supported servers
     * \return List of supported server information
     */
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> supportedServers() const;

Q_SIGNALS:
    /*!
     * \brief Emitted when a plugin loading fails
     */
    void loadingPluginFailed();
    /*!
     * \brief Emitted when no plugins are found
     */
    void noPluginsFound();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void loadPlugin(const QString &pluginPath);
    std::unique_ptr<TextAutoGenerateEngineLoaderPrivate> const d;
};
}
