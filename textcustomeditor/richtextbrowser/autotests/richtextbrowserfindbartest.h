/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class RichTextBrowserFindBarTest : public QObject
{
    Q_OBJECT
public:
    explicit RichTextBrowserFindBarTest(QObject *parent = nullptr);
    ~RichTextBrowserFindBarTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldSearchText_data();
    void shouldSearchText();
};
