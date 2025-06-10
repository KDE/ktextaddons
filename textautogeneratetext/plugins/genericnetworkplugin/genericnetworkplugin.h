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
class GenericNetworkPlugin : public TextAutoGenerateText::TextAutoGenerateTextPlugin
{
    Q_OBJECT
public:
    explicit GenericNetworkPlugin(QObject *parent = nullptr);
    ~GenericNetworkPlugin() override;

    [[nodiscard]] bool loadSettings() override;
    void clear() override;

    void setPrompt(const QString &text) override;

    [[nodiscard]] QString engineName() const override;
    [[nodiscard]] static QString name();

protected:
    void sendToAssistant(const SendToAssistantInfo &info) override;
    void askToAssistant(const QString &msg) override;
    void cancelRequest(const QByteArray &uuid) override;

private:
    void slotApiKeyRead(QKeychain::Job *baseJob);
};
