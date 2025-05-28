/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateopenai_export.h"
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>
#include <TextAutoGenerateText/TextAutoGenerateTextRequest>
class OpenAIReply;
class TEXTAUTOGENERATEOPENAI_EXPORT OpenAIManager : public TextAutoGenerateText::TextAutoGenerateManagerBase
{
    Q_OBJECT
public:
    explicit OpenAIManager(QObject *parent = nullptr);
    ~OpenAIManager() override;
    void loadModels() override;

    [[nodiscard]] OpenAIReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request);

    [[nodiscard]] QString apiKey() const;
    void setApiKey(const QString &newApiKey);

private:
    QString mApiKey;
};
