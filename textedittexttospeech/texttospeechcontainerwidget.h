/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textedittexttospeech_export.h"
#include <QWidget>
namespace TextEditTextToSpeech
{
class TextToSpeechContainerWidgetPrivate;
/*!
 * \class TextEditTextToSpeech::TextToSpeechContainerWidget
 * \inmodule TextEditTextToSpeech
 * \inheaderfile TextEditTextToSpeech/TextToSpeechContainerWidget
 *
 * \brief The TextToSpeechContainerWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEDITTEXTTOSPEECH_EXPORT TextToSpeechContainerWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextToSpeechContainerWidget(QWidget *parent = nullptr);
    /*!
     */
    ~TextToSpeechContainerWidget() override;

    /*!
     */
    void say(const QString &text);

    /*!
     */
    qsizetype enqueue(const QString &text);

private:
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void initialize();
    std::unique_ptr<TextToSpeechContainerWidgetPrivate> const d;
};
}
