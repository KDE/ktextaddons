/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textedittexttospeech_private_export.h"
#include <QComboBox>
#include <QLocale>
namespace TextEditTextToSpeech
{
class TEXTEDITTEXTTOSPEECH_TESTS_EXPORT TextToSpeechLanguageComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit TextToSpeechLanguageComboBox(QWidget *parent = nullptr);
    ~TextToSpeechLanguageComboBox() override;
    void selectLocaleName(const QString &localeName);
    void updateAvailableLocales(const QVector<QLocale> &locales, const QLocale &current);
};
}
