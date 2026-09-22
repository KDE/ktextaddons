/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QComboBox>
#include <TextAutoGenerateText/TextAutoGenerateTag>
class QStandardItemModel;
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateSelectTagsComboBox class
 *
 * A non editable combo box which shows the known tags and lets several of them be checked, so that
 * the selection can be used as a filter.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSelectTagsComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectTagsComboBox(QWidget *parent = nullptr);
    ~TextAutoGenerateSelectTagsComboBox() override;

    /*! Fills the combo box with \a tags. The selection is cleared. */
    void setTags(const QList<TextAutoGenerateText::TextAutoGenerateTag> &tags);

    /*! Returns the identifiers of the checked tags. */
    [[nodiscard]] QList<QByteArray> selectedTags() const;
    /*! Checks the tags listed in \a identifiers, unchecks the others. */
    void setSelectedTags(const QList<QByteArray> &identifiers);

Q_SIGNALS:
    void selectedTagsChanged(const QList<QByteArray> &identifiers);

protected:
    [[nodiscard]] bool eventFilter(QObject *watched, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void toggleItem(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateDisplayText();
    QStandardItemModel *const mTagsModel;
    bool mUpdatingSelection = false;
};
}
