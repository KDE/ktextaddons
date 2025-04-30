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
    explicit TextAutogenerateMessageWaitingAnswerAnimation(QObject *parent = nullptr);
    ~TextAutogenerateMessageWaitingAnswerAnimation() override;

    [[nodiscard]] QPersistentModelIndex modelIndex() const;
    void setModelIndex(const QPersistentModelIndex &newModelIndex);

    void start();

private:
    QPersistentModelIndex mModelIndex;
};
}
