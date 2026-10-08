/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextUtilsBlockCMarkSupportTest : public QObject
{
    Q_OBJECT
public:
    explicit TextUtilsBlockCMarkSupportTest(QObject *parent = nullptr);
    ~TextUtilsBlockCMarkSupportTest() override = default;

private Q_SLOTS:
    void shouldConvertTextAroundLinks();
    void shouldConvertTextAroundLinks_data();
};
