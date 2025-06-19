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
class OllamaPlugin : public TextAutoGenerateText::TextAutoGenerateTextPlugin
{
    Q_OBJECT
public:
    explicit OllamaPlugin(OllamaManager *manager, QObject *parent = nullptr);
    ~OllamaPlugin() override;

    [[nodiscard]] bool loadSettings() override;
    void clear() override;

    void setPrompt(const QString &text) override;

    [[nodiscard]] QString engineName() const override;

    [[nodiscard]] static QString name();

    void showConfigureDialog(QWidget *parentWidget) override;

    void load(const KConfigGroup &config) override;
    void save() override;

protected:
    void sendToAssistant(const SendToAssistantInfo &info) override;
    void cancelRequest(const QByteArray &uuid) override;
    void askToAssistant(const QString &msg) override;

private:
    QMultiHash<OllamaReply *, QPair<QByteArray, QMetaObject::Connection>> mConnections;
    OllamaManager *const mManager;
};
