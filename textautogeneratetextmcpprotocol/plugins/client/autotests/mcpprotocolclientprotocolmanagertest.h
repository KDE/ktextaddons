/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolClientProtocolManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolClientProtocolManagerTest(QObject *parent = nullptr);
    ~McpProtocolClientProtocolManagerTest() override = default;

private Q_SLOTS:
    void shouldInitializeAndListTools();
    void shouldAnnounceElicitationCapability();
    void shouldAnswerServerRequests();
    void shouldAnswerElicitationRequest();
    void shouldRejectDuplicatedElicitationId();
    void shouldAnnounceUrlElicitationCapability();
    void shouldAnswerUrlElicitationRequest();
    void shouldAnnounceRootsCapability();
    void shouldAnswerRootsList();
    void shouldNotifyRootsListChanged();
    void shouldAnnounceSamplingCapability();
    void shouldAnswerSamplingRequest();
    void shouldRejectUnsupportedProtocolVersion();
    void shouldCancelRequestWhenTimeoutExpired();
    void shouldNotTimeoutWhileElicitationIsPending();
    void shouldCancelRequest();
    void shouldRestartAfterStop();
    void shouldCallTool();
    void shouldNotCallToolWhenServerDoesNotSupportTools();
    void shouldGetPrompt();
    void shouldNotGetPromptWhenServerDoesNotSupportPrompts();
    void shouldReadResource();
    void shouldNotReadResourceWhenServerDoesNotSupportResources();
    void shouldFetchAllPages();
    void shouldStopPaginationWhenCursorDoesNotChange();
    void shouldFetchPageWithEmptyCursor();
    void shouldReturnErrorOfPage();
    void shouldEmitListChangedSignals();
    void shouldLogMessages();
    void shouldSubscribeResource();
    void shouldNotSubscribeWhenServerDoesNotSupportSubscription();
    void shouldEmitLoggingMessage();
    void shouldEmitProgress();
    void shouldComplete();
    void shouldSetLoggingLevel();
    void shouldNotCompleteOrSetLevelWhenServerDoesNotSupportIt();
};
