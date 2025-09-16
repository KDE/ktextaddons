/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QObject>

class TextAutoGenerateToolPluginShowMetaDataDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolPluginShowMetaDataDialogTest(QObject *parent = nullptr);
    ~TextAutoGenerateToolPluginShowMetaDataDialogTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
