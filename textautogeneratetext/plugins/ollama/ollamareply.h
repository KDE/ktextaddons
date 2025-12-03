// SPDX-FileCopyrightText: 2023 Loren Burkholder <computersemiexpert@outlook.com>
// SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
// SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
// Based on Alpaka code
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "textautogenerateollama_export.h"
#include <QJsonDocument>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateTextReplyInfo>

class QNetworkReply;

/**
 * @brief The OllamaReply class represents a reply from an LLM.
 *
 * If you want to stream a reply as it is written in real time, connect to contentAdded() and use readResponse() to retrieve
 * the new content. If you prefer to wait for the entire reply before displaying anything, connect to finished(), which will
 * only be emitted once the reply is complete.
 */
class TEXTAUTOGENERATEOLLAMA_EXPORT OllamaReply : public TextAutoGenerateText::TextAutoGenerateReply
{
    Q_OBJECT

public:
    explicit OllamaReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent = nullptr);
    ~OllamaReply() override;

    /**
     * @brief Get the current response content.
     *
     * This function returns what it has received of the response so far. Therefore, until finished() is emitted, this
     * function may return different values. However, once finished() is emitted, the content is guaranteed to remain
     * constant.
     *
     * @return The content that has been returned so far.
     */
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply::Response readResponse() const override;

private:
    [[nodiscard]] TEXTAUTOGENERATEOLLAMA_NO_EXPORT TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo
    parseDownLoadInfo(const QJsonDocument &doc) const;
    bool mDownloadError = false;
};
