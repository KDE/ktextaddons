/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QListView>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateBaseListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateBaseListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateBaseListView() override;

protected:
    void slotCopyMessage(const QModelIndex &index);
    [[nodiscard]] QStyleOptionViewItem listViewOptions() const;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;

    void checkIfAtBottom();
    void maybeScrollToBottom();
    void updateVerticalPageStep();

private:
    bool mAtBottom = true;
};
}
