/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpImportClaudeCodeTest : public QObject
{
    Q_OBJECT
public:
    explicit McpImportClaudeCodeTest(QObject *parent = nullptr);
    ~McpImportClaudeCodeTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldNotImportMissingFile();
    void shouldNotImportInvalidJson();
    void shouldNotImportFileWithoutServers();
    void shouldImportStdioServer();
    void shouldImportUrlServers();
    void shouldSkipInvalidServers();
    void shouldImportExportedServer();
};
