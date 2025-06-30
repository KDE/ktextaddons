/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratebaselistview.h"
#include "textautogeneratetext_private_export.h"
#include <TextAutoGenerateText/TextAutoGenerateSearchMessage>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateSearchMessagesModel;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchListView : public TextAutoGenerateBaseListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateSearchListView() override;

    void setSearchMessages(const QList<TextAutoGenerateSearchMessage> &msgs);

protected:
    void paintEvent(QPaintEvent *event) override;
    [[nodiscard]] bool event(QEvent *ev) override;

    [[nodiscard]] QString originalMessage(const QModelIndex &index) const override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotGoToMessage(const QString &link);
    TEXTAUTOGENERATETEXT_NO_EXPORT void generalPaletteChanged();
    QColor mTextColor;
    TextAutoGenerateSearchMessagesModel *const mModel;
};
}
