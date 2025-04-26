/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "core/textautogeneratetextplugin.h"

#include "ollamareply.h"

#include <QMultiHash>

class OllamaPlugin : public TextAutogenerateText::TextAutogenerateTextPlugin
{
    Q_OBJECT
public:
    explicit OllamaPlugin(QObject *parent = nullptr);
    ~OllamaPlugin() override;

    [[nodiscard]] bool loadSettings() override;
    void clear() override;

    void setPrompt(const QString &text) override;

    [[nodiscard]] QString currentModel() const;
    void setCurrentModel(const QString &newCurrentModel);

protected:
    void sendToLLM(const QString &message, const QByteArray &uuid) override;
    void stop() override;

private:
    QString mCurrentModel;
    QMultiHash<OllamaReply *, QMetaObject::Connection> mConnections;
};
