/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateAttachmentUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAttachmentUtilsTest(QObject *parent = nullptr);
    ~TextAutoGenerateAttachmentUtilsTest() override = default;
private Q_SLOTS:
    void shouldGenerateAttachmentType();
    void shouldGenerateAttachmentType_data();
    void shouldHaveAttachmentElementInfoDefaultValues();
};
