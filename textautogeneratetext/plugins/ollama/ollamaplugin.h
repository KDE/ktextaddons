/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "core/textautogeneratetextplugin.h"

#include "ollamareply.h"

#include <QMultiHash>
#include <QPair>
class OllamaManager;
class OllamaSettings;
class OllamaPlugin : public TextAutoGenerateText::TextAutoGenerateTextPlugin
{
    Q_OBJECT
public:
    explicit OllamaPlugin(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent = nullptr);
    ~OllamaPlugin() override;

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
    void cancelRequest(const QByteArray &uuid) override;
    void askToAssistant(const QString &msg) override;

private:
    QMultiHash<OllamaReply *, QPair<QByteArray, QMetaObject::Connection>> mConnections;
    OllamaSettings *const mOllamaSettings;
    OllamaManager *const mManager;
};
