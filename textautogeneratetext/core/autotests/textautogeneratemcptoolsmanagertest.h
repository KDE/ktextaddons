/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateMcpToolsManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMcpToolsManagerTest(QObject *parent = nullptr);
    ~TextAutoGenerateMcpToolsManagerTest() override = default;

private Q_SLOTS:
    void shouldSanitizeName();
    void shouldConnectAndListTools();
    void shouldReportErrorForInvalidServer();
    void shouldDisconnectWhenServerIsDisabled();
    void shouldRefreshToolsWhenListChanged();
    void shouldCreateUniqueNames();
    void shouldConvertToolIdentifiers();
    void shouldPrepareServers();
    void shouldPrepareInvalidServer();
    void shouldNotCallCallbackWhenContextIsDeleted();
    void shouldCallCallbackAfterTimeout();
    void shouldAnswerElicitationRequest();
};
