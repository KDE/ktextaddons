/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

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
/**
 * @brief The TextAutoGenerateEngineLoader class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateEngineLoader : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateEngineLoader(QObject *parent = nullptr);
    ~TextAutoGenerateEngineLoader() override;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextClient *searchTextAutoGenerateTextClient(const QString &clientName);

    [[nodiscard]] bool showConfigureDialog(const QString &clientName, QWidget *parentWidget);

    [[nodiscard]] QMap<QString, QString> textAutoGenerateTextEngineInfos() const;

    [[nodiscard]] QString fallbackFirstEngine() const;

    [[nodiscard]] bool hasEngine() const;

    void loadPlugins();

    [[nodiscard]] QString generateDisplayName(TextAutoGenerateTextClient *client) const;

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> supportedServers() const;

Q_SIGNALS:
    void loadingPluginFailed();
    void noPluginsFound();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void loadPlugin(const QString &pluginPath);
    std::unique_ptr<TextAutoGenerateEngineLoaderPrivate> const d;
};
}
