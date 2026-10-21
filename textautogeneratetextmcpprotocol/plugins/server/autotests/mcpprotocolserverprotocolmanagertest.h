/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolServerProtocolManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolServerProtocolManagerTest(QObject *parent = nullptr);
    ~McpProtocolServerProtocolManagerTest() override = default;

private Q_SLOTS:
    void shouldUseDefaultServerInfo();
    void shouldKeepServerInfo();
    void shouldAnnouncePromptsAndResourcesWhenRegistered();
    void shouldNotAnnouncePromptsAndResourcesByDefault();
    void shouldListAndGetPrompt();
    void shouldReturnErrorForInvalidPromptRequest();
    void shouldListAndReadResource();
    void shouldReturnErrorForInvalidResourceRequest();
    void shouldPaginatePromptsAndResources();
    void shouldNotifyListChanged();
    void shouldCompletePromptArgument();
    void shouldReturnErrorForInvalidCompletionRequest();
    void shouldSendLogMessagesFromLoggingLevel();
    void shouldNotSendClientRequestsWithoutCapabilities();
    void shouldRequestSampling();
    void shouldRequestElicitation();
    void shouldRequestRoots();
};
