/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextcomboboxwidget.h"
#include <TextSpeechToText/SpeechToTextEngineLoader>
using namespace TextSpeechToText;
SpeechToTextComboBoxWidget::SpeechToTextComboBoxWidget(QWidget *parent)
    : QComboBox(parent)
{
}

SpeechToTextComboBoxWidget::~SpeechToTextComboBoxWidget() = default;

void SpeechToTextComboBoxWidget::fillEngine()
{
    const QMap<QString, QString> map = TextSpeechToText::SpeechToTextEngineLoader::self()->speechToTextEngineInfos();
    QMapIterator<QString, QString> iMap(map);
    while (iMap.hasNext()) {
        iMap.next();
        addItem(iMap.value(), iMap.key());
    }
}

#include "moc_speechtotextcomboboxwidget.cpp"
