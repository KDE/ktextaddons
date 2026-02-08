/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textspeechtotext_export.h"
#include <QAction>
namespace TextSpeechToText
{
/*!
 * \class SpeechToTextAction
 * \inheaderfile TextSpeechToText/SpeechToTextAction
 * \inmodule TextSpeechToText
 * \brief QAction subclass for speech-to-text functionality.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextAction : public QAction
{
    Q_OBJECT
public:
    /*!
     */
    explicit SpeechToTextAction(QObject *parent = nullptr);
    /*!
     */
    ~SpeechToTextAction() override;

private:
    TEXTSPEECHTOTEXT_NO_EXPORT void slotClicked();
};
}
