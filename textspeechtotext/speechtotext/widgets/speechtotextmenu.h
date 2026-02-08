/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textspeechtotext_export.h"
#include <QObject>
class QMenu;
namespace TextSpeechToText
{
/*!
 * \class SpeechToTextMenu
 * \inheaderfile TextSpeechToText/SpeechToTextMenu
 * \inmodule TextSpeechToText
 * \brief Menu widget for speech-to-text engine selection and control.
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextMenu : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit SpeechToTextMenu(QObject *parent = nullptr);
    /*!
     */
    ~SpeechToTextMenu() override;

    /*!
     */
    [[nodiscard]] bool isEmpty() const;
    /*!
     */
    [[nodiscard]] QMenu *menu() const;

private:
    TEXTSPEECHTOTEXT_NO_EXPORT void updateMenu();
    QMenu *const mMenu;
};
}
