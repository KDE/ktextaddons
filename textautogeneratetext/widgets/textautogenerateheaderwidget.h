/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGenerateTextPlugin>
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

    void setModelList(const QList<TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier> &lst);
    [[nodiscard]] QString currentModel() const;
    void slotCloseQuickSearchRequested();
Q_SIGNALS:
    void addNewChat();
    void changeFavoriteRequested(bool f);
    void searchText(bool checked);
    void addNewEphemeralChat();
    void saveInDataseRequested();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotCurrentChatIdChanged();
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateEngineName(const QString &engineName);
    QLabel *const mEngineName;
    QToolButton *const mNewChat;
    QToolButton *const mNewEphemeralChat;
    QToolButton *const mFavorite;
    QToolButton *const mSearch;
    QToolButton *const mSaveQuickAskButton;
    TextAutoGenerateTextModelComboBox *const mModelComboBox;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
