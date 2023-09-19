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

QString SpeechToTextComboBoxWidget::engineName() const
{
    return mEngine->currentData().toString();
}

void SpeechToTextComboBoxWidget::setEngineName(const QString &engineName)
{
    const int countItem(mEngine->count());
    for (int i = 0; i < countItem; ++i) {
        if (mEngine->itemData(i).toString() == engineName) {
            mEngine->setCurrentIndex(i);
            break;
        }
    }
}

#include "moc_speechtotextcomboboxwidget.cpp"
