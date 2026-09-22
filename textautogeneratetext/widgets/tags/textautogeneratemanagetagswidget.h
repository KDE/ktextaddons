/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGenerateTag>
class QListView;
class QModelIndex;
class QToolButton;
namespace TextAutoGenerateText
{
class TextAutoGenerateTagsModel;
/**
 * @brief The TextAutoGenerateManageTagsWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateManageTagsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateManageTagsWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateManageTagsWidget() override;

    /*! Fills the widget with \a tags. The widget works on a copy: tags() returns the edited list. */
    void setTags(const QList<TextAutoGenerateText::TextAutoGenerateTag> &tags);
    /*! Returns the edited tags. */
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTag> tags() const;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAddTag();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotModifyTag();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRemoveTag();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotModifyTag(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateButtons();
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateText::TextAutoGenerateTag tagFromIndex(const QModelIndex &index) const;
    QListView *const mTagsListView;
    TextAutoGenerateTagsModel *const mTagsModel;
    QToolButton *const mAddButton;
    QToolButton *const mModifyButton;
    QToolButton *const mRemoveButton;
};
}
