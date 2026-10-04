/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QToolButton;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateToolsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolsWidget(TextAutoGenerateText::TextAutoGenerateManager *manager = nullptr, QWidget *parent = nullptr);
    ~TextAutoGenerateToolsWidget() override;

    [[nodiscard]] QList<QByteArray> generateListOfActiveTools() const;

    void setActivatedTools(const QList<QByteArray> &lst);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void disableTools();
    TEXTAUTOGENERATETEXT_NO_EXPORT void createMcpServerButtons();
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateMcpServerButton(const QByteArray &serverIdentifier);
    QList<QToolButton *> mListButton;
    // One button by MCP server
    QList<QToolButton *> mMcpServerButtons;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
