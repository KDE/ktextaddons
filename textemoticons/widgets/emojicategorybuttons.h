/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonswidgets_private_export.h"
#include <QWidget>
class QHBoxLayout;
class QButtonGroup;
namespace TextEmoticonsCore
{
class EmoticonCategory;
}
namespace TextEmoticonsWidgets
{
class TEXTEMOTICONSWIDGETS_TESTS_EXPORT EmojiCategoryButtons : public QWidget
{
    Q_OBJECT
public:
    explicit EmojiCategoryButtons(QWidget *parent = nullptr);
    ~EmojiCategoryButtons() override;

    void setCategories(const QList<TextEmoticonsCore::EmoticonCategory> &categories, bool hasCustomSupport);

    [[nodiscard]] bool wasLoaded() const;

Q_SIGNALS:
    void categorySelected(const QString &category);

protected:
    void wheelEvent(QWheelEvent *e) override;

private:
    TEXTEMOTICONSWIDGETS_NO_EXPORT void addButton(const QString &name, const QString &category, const QString &toolTip);
    QHBoxLayout *const mMainLayout;
    QButtonGroup *const mButtonGroup;
    bool mWasLoaded = false;
};
}
