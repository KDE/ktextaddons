/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratellamacpp_export.h"
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>

class TEXTAUTOGENERATELLAMACPP_EXPORT LLamaCppManager : public TextAutoGenerateText::TextAutoGenerateManagerBase
{
public:
    explicit LLamaCppManager(QObject *parent = nullptr);
    ~LLamaCppManager() override;

    void loadModels() override;
    TextAutoGenerateText::TextAutoGenerateReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;
    TextAutoGenerateText::TextAutoGenerateReply *getResponses(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;
};
