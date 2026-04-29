/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QList>
#include <QWidget>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolClient;
}
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;

private:
    QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolClient *> mListClient;
};
