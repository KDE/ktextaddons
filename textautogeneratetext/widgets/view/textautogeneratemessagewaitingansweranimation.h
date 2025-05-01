/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"

#include <QObject>
#include <QPersistentModelIndex>
namespace TextAutogenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateMessageWaitingAnswerAnimation : public QObject
{
    Q_OBJECT
public:
    struct ScaleAndOpacity {
        qreal scale = 0.0;
        qreal opacity = 0.0;
    };

    explicit TextAutogenerateMessageWaitingAnswerAnimation(QObject *parent = nullptr);
    ~TextAutogenerateMessageWaitingAnswerAnimation() override;

    [[nodiscard]] QPersistentModelIndex modelIndex() const;
    void setModelIndex(const QPersistentModelIndex &newModelIndex);

    void start();

    [[nodiscard]] ScaleAndOpacity value(int i) const;

Q_SIGNALS:
    void valueChanged();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void createAnimations();
    TEXTAUTOGENERATETEXT_NO_EXPORT void createAnimation(int index, int duration);
    QList<ScaleAndOpacity> mScaleOpacities;
    QPersistentModelIndex mModelIndex;
};
}
