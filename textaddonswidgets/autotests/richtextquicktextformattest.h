/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include <QObject>

class RichTextQuickTextFormatTest : public QObject
{
    Q_OBJECT
public:
    explicit RichTextQuickTextFormatTest(QObject *parent = nullptr);
    ~RichTextQuickTextFormatTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldReactSignalCall();
};
