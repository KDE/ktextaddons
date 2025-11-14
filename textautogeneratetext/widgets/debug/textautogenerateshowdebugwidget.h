/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateJsonPlainTextEditWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateShowDebugWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateShowDebugWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateShowDebugWidget() override;

    void setPlainText(const QString &text);

private:
    TextAutoGenerateJsonPlainTextEditWidget *const mJsonPlainTextEditWidget;
};
}
