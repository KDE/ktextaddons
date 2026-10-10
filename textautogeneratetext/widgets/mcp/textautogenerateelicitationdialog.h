/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

#include "textautogeneratetext_private_export.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitResult>

namespace TextAutoGenerateText
{
class TextAutoGenerateElicitationWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateElicitationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateElicitationDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateElicitationDialog() override;

    void setServerName(const QString &serverName);

    /*!
     * Answer of user: Accept, Decline or Cancel (dialog closed)
     */
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult elicitResult() const;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAccepted();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotDeclined();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRejected();
    TextAutoGenerateElicitationWidget *const mTextAutoGenerateElicitationWidget;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action mAction = TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Cancel;
};
}
