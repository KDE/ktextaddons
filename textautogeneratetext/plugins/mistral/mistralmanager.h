/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextRequest>
class MistralReply;
class MistralManager : public QObject
{
    Q_OBJECT
public:
    explicit MistralManager(QObject *parent = nullptr);
    ~MistralManager() override;
    void loadModels();

    [[nodiscard]] MistralReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request);
};
