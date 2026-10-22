/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mcpprotocolwidgets_private_export.h"
#include <QWidget>
class QTextBrowser;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpRegistryServerInfo;
}
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT McpRegistryServerInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit McpRegistryServerInfoWidget(QWidget *parent = nullptr);
    ~McpRegistryServerInfoWidget() override;

    void setServerInfo(const TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo &info);

    [[nodiscard]] static QString generateHtml(const TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo &info);

private:
    QTextBrowser *const mTextBrowser;
};
}
