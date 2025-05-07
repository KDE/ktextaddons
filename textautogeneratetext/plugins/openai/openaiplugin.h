/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <core/textautogeneratetextplugin.h>

class OpenAIPlugin : public TextAutogenerateText::TextAutogenerateTextPlugin
{
    Q_OBJECT
public:
    explicit OpenAIPlugin(QObject *parent = nullptr);
    ~OpenAIPlugin() override;

    [[nodiscard]] bool loadSettings() override;
    void clear() override;

    void setPrompt(const QString &text) override;

    [[nodiscard]] QString engineName() const override;
    [[nodiscard]] static QString name();

protected:
    void sendToLLM(const QString &message, const QByteArray &uuid) override;
    void cancelRequest(const QByteArray &uuid) override;
};
