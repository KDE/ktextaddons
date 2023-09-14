/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextcomboboxwidget.h"
#include <KLocalizedString>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <TextSpeechToText/SpeechToTextEngineLoader>
using namespace TextSpeechToText;
SpeechToTextComboBoxWidget::SpeechToTextComboBoxWidget(QWidget *parent)
    : QWidget(parent)
    , mEngine(new QComboBox(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    auto label = new QLabel(i18n("Engine:"), this);
    label->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(label);

    mEngine->setObjectName(QStringLiteral("mEngine"));
    mainLayout->addWidget(mEngine);
}

SpeechToTextComboBoxWidget::~SpeechToTextComboBoxWidget() = default;

void SpeechToTextComboBoxWidget::fillEngine()
{
    const QMap<QString, QString> map = TextSpeechToText::SpeechToTextEngineLoader::self()->speechToTextEngineInfos();
    QMapIterator<QString, QString> iMap(map);
    while (iMap.hasNext()) {
        iMap.next();
        mEngine->addItem(iMap.value(), iMap.key());
    }
}

#include "moc_speechtotextcomboboxwidget.cpp"
