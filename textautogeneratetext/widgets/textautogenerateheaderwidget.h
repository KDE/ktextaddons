/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLabel;
class QToolButton;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateTextModelComboBox;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateHeaderWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateHeaderWidget() override;
    void updateEngineName(const QString &engineName);

    void setModelList(const QStringList &lst);
    [[nodiscard]] QString currentModel() const;
Q_SIGNALS:
    void configChanged();
    void addNewChat();
    void changeFavoriteRequested(bool f);
    void searchText();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotCurrentChatIdChanged();
    QLabel *const mEngineName;
    QToolButton *const mNewChat;
    QToolButton *const mFavorite;
    QToolButton *const mSearch;
    TextAutoGenerateTextModelComboBox *const mModelComboBox;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
