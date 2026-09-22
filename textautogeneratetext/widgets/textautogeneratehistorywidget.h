/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLineEdit;
class QToolButton;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateHistoryListView;
class TextAutoGenerateSelectTagsComboBox;
/**
 * @brief The TextAutoGenerateHistoryWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateHistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateHistoryWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateHistoryWidget() override;

Q_SIGNALS:
    void switchToChat(const QByteArray &uuid);

private:
    /*! Refills the tags combo box, keeping the tags which are still known selected. The combo box
     *  is hidden while no tag is defined, as it could then not filter anything. */
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateTags();
    TextAutoGenerateHistoryListView *const mTextAutoGenerateHistoryListView;
    QLineEdit *const mSearchLineEdit;
    TextAutoGenerateSelectTagsComboBox *const mSelectTagsComboBox;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    QToolButton *const mClearTagsButton;
};
}
