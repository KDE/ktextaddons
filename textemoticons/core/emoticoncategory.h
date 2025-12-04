/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonscore_export.h"
#include <QObject>
#include <QString>
class QDebug;
namespace TextEmoticonsCore
{
/**
 * @brief The EmoticonCategory class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT EmoticonCategory
{
    Q_GADGET

    Q_PROPERTY(QString name MEMBER mName CONSTANT)
    Q_PROPERTY(QString category MEMBER mCategory CONSTANT)
    Q_PROPERTY(QString i18nName MEMBER mI18nName CONSTANT)

public:
    EmoticonCategory();
    [[nodiscard]] QString name() const;
    void setName(const QString &name);

    [[nodiscard]] QString category() const;
    void setCategory(const QString &category);

    [[nodiscard]] const QString &i18nName() const;

    void setI18nName(const QString &newI18nName);

    [[nodiscard]] bool operator<(const EmoticonCategory &other) const;

    [[nodiscard]] int order() const;
    void setOrder(int newOrder);

private:
    QString mName;
    QString mCategory;
    QString mI18nName;
    int mOrder = 20;
};
}
Q_DECLARE_METATYPE(TextEmoticonsCore::EmoticonCategory)
Q_DECLARE_TYPEINFO(TextEmoticonsCore::EmoticonCategory, Q_MOVABLE_TYPE);
TEXTEMOTICONSCORE_EXPORT QDebug operator<<(QDebug d, const TextEmoticonsCore::EmoticonCategory &t);
