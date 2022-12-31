/*
   SPDX-FileCopyrightText: 2014-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>
namespace KPIMTextEditTextToSpeech
{
class TextToSpeechConfigWidget;
}
class TextToSpeechConfigWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextToSpeechConfigWidgetTest(QObject *parent = nullptr);
    ~TextToSpeechConfigWidgetTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldEmitConfigChangedWhenChangeConfigValue();

private:
    void addInterface(KPIMTextEditTextToSpeech::TextToSpeechConfigWidget *widget);
};
