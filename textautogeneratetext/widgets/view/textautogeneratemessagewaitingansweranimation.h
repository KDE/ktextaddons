/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"

#include <QDebug>
#include <QObject>
#include <QPersistentModelIndex>
class QSequentialAnimationGroup;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateMessageWaitingAnswerAnimation : public QObject
{
    Q_OBJECT
public:
    struct ScaleAndOpacity {
        qreal scale = 0.0;
        qreal opacity = 0.0;
    };

    explicit TextAutoGenerateMessageWaitingAnswerAnimation(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent = nullptr);
    ~TextAutoGenerateMessageWaitingAnswerAnimation() override;

    [[nodiscard]] QPersistentModelIndex modelIndex() const;
    void setModelIndex(const QPersistentModelIndex &newModelIndex);

    void start();

    [[nodiscard]] ScaleAndOpacity value(int i) const;

    [[nodiscard]] int count() const;
    [[nodiscard]] QList<ScaleAndOpacity> scaleOpacities() const;

    void stopAndDelete();
Q_SIGNALS:
    void valueChanged();
    void waitingAnswerDone(const QModelIndex &index);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void createAnimations();
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QSequentialAnimationGroup *createAnimation(int index, int duration);
    QList<ScaleAndOpacity> mScaleOpacities;
    QPersistentModelIndex mModelIndex;
    QSequentialAnimationGroup *mSequencials = nullptr;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateMessageWaitingAnswerAnimation::ScaleAndOpacity, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateMessageWaitingAnswerAnimation::ScaleAndOpacity &t);
