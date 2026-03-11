/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QObject>
#include <QUrl>

namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextMcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextMcpServer(QObject *parent = nullptr);
    ~TextAutoGenerateTextMcpServer() override;
    [[nodiscard]] QUrl serverUrl() const;
    void setServerUrl(const QUrl &newServerUrl);

private:
    QUrl mServerUrl;
};
}
