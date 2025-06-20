/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextAutoGenerateText/TextAutoGenerateTextPlugin>
namespace QKeychain
{
class Job;
}
class GenericNetworkManager;
class GenericNetworkPlugin : public TextAutoGenerateText::TextAutoGenerateTextPlugin
{
    Q_OBJECT
public:
    explicit GenericNetworkPlugin(const QString &serverIdentifier, TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent = nullptr);
    ~GenericNetworkPlugin() override;

    void clear() override;

    void setPrompt(const QString &text) override;

    [[nodiscard]] QString engineName() const override;
    [[nodiscard]] static QString name();
    [[nodiscard]] QString translatedPluginName() const override;

    void showConfigureDialog(QWidget *parentWidget) override;

    void load(const KConfigGroup &config) override;
    void save(KConfigGroup &config) override;

    [[nodiscard]] QStringList models() const override;

protected:
    void sendToAssistant(const SendToAssistantInfo &info) override;
    void askToAssistant(const QString &msg) override;
    void cancelRequest(const QByteArray &uuid) override;

private:
    void slotApiKeyRead(QKeychain::Job *baseJob);
    GenericNetworkManager *const mGenericManager;
};
