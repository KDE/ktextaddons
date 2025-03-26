/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "core/textautogeneratetextplugin.h"

class OllamaPlugin : public TextAutogenerateText::TextAutogenerateTextPlugin
{
    Q_OBJECT
public:
    explicit OllamaPlugin(QObject *parent = nullptr);
    ~OllamaPlugin() override;

    [[nodiscard]] bool loadSettings() override;
    void clear() override;
    [[nodiscard]] QString result() override;

    void setPrompt(const QString &text) override;

    [[nodiscard]] bool ready() const;
    void setReady(bool newReady);

    [[nodiscard]] QString currentModel() const;
    void setCurrentModel(const QString &newCurrentModel);

private:
    bool mReady = false;
    QString mCurrentModel;
};
