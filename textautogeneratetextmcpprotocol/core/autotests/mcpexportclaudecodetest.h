/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpExportClaudeCodeTest : public QObject
{
    Q_OBJECT
public:
    explicit McpExportClaudeCodeTest(QObject *parent = nullptr);
    ~McpExportClaudeCodeTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldNotExportInvalidServer();
    void shouldExportStdioServer();
    void shouldExportStdioServerWithoutArguments();
    void shouldNotExportStdioServerWithInvalidArguments();
    void shouldExportSseServer();
    void shouldExportStreamableHttpServer();
    void shouldNotExportAuthToken();
    void shouldMergeWithExistingFile();
    void shouldNotOverwriteInvalidJsonFile();
};
