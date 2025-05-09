/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QColor>
#include <QObject>
#include <QPersistentModelIndex>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSelectedMessageBackgroundAnimation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
public:
    explicit TextAutoGenerateSelectedMessageBackgroundAnimation(QObject *parent = nullptr);
    ~TextAutoGenerateSelectedMessageBackgroundAnimation() override;

    [[nodiscard]] QColor backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

    void start();

    [[nodiscard]] QPersistentModelIndex modelIndex() const;
    void setModelIndex(const QPersistentModelIndex &newModelIndex);

Q_SIGNALS:
    void backgroundColorChanged();
    void animationFinished();

private:
    QColor m_backgroundColor;
    QPersistentModelIndex mModelIndex;
};
}
