/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textspeechtotext_export.h"
#include <QObject>
class QMenu;
namespace TextSpeechToText
{
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextMenu : public QObject
{
    Q_OBJECT
public:
    explicit SpeechToTextMenu(QObject *parent = nullptr);
    ~SpeechToTextMenu() override;

    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] QMenu *menu() const;

private:
    TEXTSPEECHTOTEXT_NO_EXPORT void updateMenu();
    QMenu *const mMenu;
};
}
