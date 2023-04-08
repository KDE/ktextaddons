/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

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
class TEXTEMOTICONSWIDGETS_TESTS_EXPORT EmoticonCategoryButtons : public QWidget
{
    Q_OBJECT
public:
    explicit EmoticonCategoryButtons(QWidget *parent = nullptr);
    ~EmoticonCategoryButtons() override;

    void setCategories(const QList<TextEmoticonsCore::EmoticonCategory> &categories);

Q_SIGNALS:
    void categorySelected(const QString &category);

private:
    void addButton(const QString &name, const QString &category);
    QHBoxLayout *mMainLayout = nullptr;
    QButtonGroup *const mButtonGroup;
};
}
