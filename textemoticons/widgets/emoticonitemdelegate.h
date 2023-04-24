/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textemoticonswidgets_private_export.h"
#include <QStyledItemDelegate>
namespace TextEmoticonsWidgets
{
class TEXTEMOTICONSWIDGETS_TESTS_EXPORT EmoticonItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit EmoticonItemDelegate(QObject *parent = nullptr);
    ~EmoticonItemDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
}
