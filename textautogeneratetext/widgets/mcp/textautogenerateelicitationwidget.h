/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QVBoxLayout;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolElicitRequest;
}
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateElicitationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateElicitationWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateElicitationWidget() override;
    void setRequest(const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest &request);

private:
    QVBoxLayout *const mMainLayout;
};
}
