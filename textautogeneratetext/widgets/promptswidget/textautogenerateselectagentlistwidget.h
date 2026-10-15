/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_private_export.h"
#include <QListView>
namespace TextAutoGenerateText
{
class TextAutoGenerateAgent;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSelectAgentListWidget : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectAgentListWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateSelectAgentListWidget() override;

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

Q_SIGNALS:
    void addAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent);
    void removeAgent(const QByteArray &identifier);
    void editAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditAgent(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAddAgent();
};
}
