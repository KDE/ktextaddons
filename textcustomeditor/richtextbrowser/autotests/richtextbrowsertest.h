/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class RichTextBrowserTest : public QObject
{
    Q_OBJECT
public:
    explicit RichTextBrowserTest(QObject *parent = nullptr);
    ~RichTextBrowserTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldChangeSpellCheckValue();
};
