/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

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
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply::Response readResponse() const override;

private:
    TEXTAUTOGENERATEGENERICNETWORK_NO_EXPORT void accumulateStreamedToken(const QJsonDocument &tok);

    // Streamed tokens are folded into the response as they arrive, so that readResponse() stays O(1)
    // instead of re-parsing every token received so far each time contentAdded() is emitted.
    TextAutoGenerateText::TextAutoGenerateReply::Response mStreamedResponse;
};
