/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QObject>
#include <memory>
namespace TextAutogenerateText
{
class TextAutogenerateEngineLoaderPrivate;
class TextAutogenerateTextClient;
/**
 * @brief The TextAutogenerateEngineLoader class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateEngineLoader : public QObject
{
    Q_OBJECT
public:
    static TextAutogenerateEngineLoader *self();

    explicit TextAutogenerateEngineLoader(QObject *parent = nullptr);
    ~TextAutogenerateEngineLoader() override;

    [[nodiscard]] TextAutogenerateText::TextAutogenerateTextClient *createTextAutoGenerateTextClient(const QString &clientName);

    [[nodiscard]] bool hasConfigurationDialog(const QString &clientName) const;

    [[nodiscard]] bool showConfigureDialog(const QString &clientName, QWidget *parentWidget);

    [[nodiscard]] QMap<QString, QString> textAutoGenerateTextEngineInfos() const;

    [[nodiscard]] QString fallbackFirstEngine() const;

    [[nodiscard]] bool hasEngine() const;

Q_SIGNALS:
    void loadingPluginFailed();
    void noPluginsFound();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void loadPlugins();
    TEXTAUTOGENERATETEXT_NO_EXPORT void loadPlugin(const QString &pluginPath);
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QString generateDisplayName(TextAutogenerateTextClient *client) const;
    std::unique_ptr<TextAutogenerateEngineLoaderPrivate> const d;
};
}
