/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textedittexttospeech_export.h"
#include <QWidget>
namespace TextEditTextToSpeech
{
class TextToSpeechContainerWidgetPrivate;
/**
 * @brief The TextToSpeechContainerWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEDITTEXTTOSPEECH_EXPORT TextToSpeechContainerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextToSpeechContainerWidget(QWidget *parent = nullptr);
    ~TextToSpeechContainerWidget() override;

    void say(const QString &text);

    qsizetype enqueue(const QString &text);

private:
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void initialize();
    std::unique_ptr<TextToSpeechContainerWidgetPrivate> const d;
};
}
