/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratemistral_export.h"
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>
#include <TextAutoGenerateText/TextAutoGenerateTextRequest>
class MistralReply;
class TEXTAUTOGENERATEMISTRAL_EXPORT MistralManager : public TextAutoGenerateText::TextAutoGenerateManagerBase
{
    Q_OBJECT
public:
    explicit MistralManager(QObject *parent = nullptr);
    ~MistralManager() override;
    void loadModels() override;

    [[nodiscard]] MistralReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request);

    [[nodiscard]] QString apiKey() const;
    void setApiKey(const QString &newApiKey);

private:
    QString mApiKey;
};
