/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLineEdit;
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

    // Load agents from manager (changes are discarded)
    void load();
    // Apply changes to manager (it's not saved on disk)
    void save();

Q_SIGNALS:
    void settingsChanged();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAddAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRemoveAgent(const QByteArray &identifier);
    TextAutoGenerateSelectAgentListWidget *const mListWidget;
    TextAutoGenerateTextAgentModel *const mAgentModel;
    TextAutoGenerateManager *const mManager;
    QLineEdit *const mSearchLineEdit;
};
}
