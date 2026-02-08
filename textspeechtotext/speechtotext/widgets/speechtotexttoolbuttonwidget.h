/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textspeechtotext_export.h"
#include <QWidget>
class QToolButton;
namespace TextSpeechToText
{
/*!
 * \class SpeechToTextToolButtonWidget
 * \inheaderfile TextSpeechToText/SpeechToTextToolButtonWidget
 * \inmodule TextSpeechToText
 * \brief Tool button widget for speech-to-text functionality.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextToolButtonWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     */
    explicit SpeechToTextToolButtonWidget(QWidget *parent = nullptr);
    /*!
     */
    ~SpeechToTextToolButtonWidget() override;

private:
    TEXTSPEECHTOTEXT_NO_EXPORT void slotButtonClicked();
    QToolButton *const mToolButton;
};
}
