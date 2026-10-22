/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mcpprotocolwidgets_private_export.h"
#include <QListView>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpRegistryServerModel;
class McpRegistryServerInfo;
}
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT McpRegistryServerListView : public QListView
{
    Q_OBJECT
public:
    explicit McpRegistryServerListView(QWidget *parent = nullptr);
    ~McpRegistryServerListView() override;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpRegistryServerModel *registryServerModel() const;

Q_SIGNALS:
    void serverSelected(const TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo &info);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotCurrentChanged(const QModelIndex &index);
    TextAutoGenerateTextMcpProtocolCore::McpRegistryServerModel *const mModel;
};
}
