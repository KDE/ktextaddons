/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateAgent;
class TextAutoGenerateTextAgentModel;
class TextAutoGenerateSelectAgentListWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSelectAgentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectAgentWidget(TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateSelectAgentWidget() override;

    [[nodiscard]] QList<TextAutoGenerateAgent> agents() const;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAddAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRemoveAgent(const QByteArray &identifier);
    TextAutoGenerateSelectAgentListWidget *const mListWidget;
    TextAutoGenerateTextAgentModel *const mAgentModel;
};
}
