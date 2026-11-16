/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QObject>

class LoadDialogSizeUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit LoadDialogSizeUtilsTest(QObject *parent = nullptr);

private Q_SLOTS:
    void shouldNotStoreSizeWhenDialogNeverShown();
    void shouldNotStoreSizeWhenWindowCreatedButNeverShown();
    void shouldUseDefaultSizeWhenNoStoredSize();
    void shouldStoreSizeWhenDestroyedWhileVisible();
    void shouldStoreSizeWhenAccepted();
    void shouldStoreSizeWhenClosed();
    void shouldNotReloadSizeOnSecondShow();
    void shouldManageKPageDialog();
    void shouldPositionAsQDialog();
};
