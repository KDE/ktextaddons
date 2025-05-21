/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextAutoGenerateText/TextAutoGenerateReply>

class MistralReply : public TextAutoGenerateText::TextAutoGenerateReply
{
    Q_OBJECT
public:
    explicit MistralReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent = nullptr);
    ~MistralReply() override;
};
