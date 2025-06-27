/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerategenericnetwork_export.h"
#include <TextAutoGenerateText/TextAutoGenerateReply>

class TEXTAUTOGENERATEGENERICNETWORK_EXPORT GenericNetworkReply : public TextAutoGenerateText::TextAutoGenerateReply
{
    Q_OBJECT
public:
    explicit GenericNetworkReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent = nullptr);
    ~GenericNetworkReply() override;
    [[nodiscard]] QString readResponse() const override;
};
