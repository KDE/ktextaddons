/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextcomboboxwidget.h"
#include "speechtotext/textspeechtotextutil.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <TextSpeechToText/SpeechToTextEngineLoader>

using namespace TextSpeechToText;
SpeechToTextComboBoxWidget::SpeechToTextComboBoxWidget(QWidget *parent)
    : QWidget(parent)
    , mEngine(new QComboBox(this))
    , mConfigureEngine(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    auto label = new QLabel(i18n("Engine:"), this);
    label->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(label);

    mEngine->setObjectName(QStringLiteral("mEngine"));
    mainLayout->addWidget(mEngine);

    mConfigureEngine->setObjectName(QStringLiteral("mConfigureEngine"));
    mainLayout->addWidget(mConfigureEngine);
    mConfigureEngine->setEnabled(false); // Disable by default
    mConfigureEngine->setIcon(QIcon::fromTheme(QStringLiteral("settings-configure")));

    connect(mConfigureEngine, &QToolButton::clicked, this, &SpeechToTextComboBoxWidget::slotConfigureEngine);
    connect(mEngine, &QComboBox::currentIndexChanged, this, &SpeechToTextComboBoxWidget::slotEngineChanged);
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

void SpeechToTextComboBoxWidget::slotConfigureEngine()
{
    const QString engine = mEngine->currentData().toString();
    if (TextSpeechToText::SpeechToTextEngineLoader::self()->hasConfigurationDialog(engine)) {
        if (TextSpeechToText::SpeechToTextEngineLoader::self()->showConfigureDialog(engine, this)) {
            Q_EMIT configureChanged(engine);
        }
    }
}

void SpeechToTextComboBoxWidget::slotEngineChanged(int index)
{
    const QString engine = mEngine->itemData(index).toString();
    mConfigureEngine->setEnabled(TextSpeechToText::SpeechToTextEngineLoader::self()->hasConfigurationDialog(engine));
    Q_EMIT engineChanged(engine);
}

void SpeechToTextComboBoxWidget::load()
{
    KConfigGroup groupTranslate(KSharedConfig::openConfig(), TextSpeechToTextUtil::groupTranslateName());
    const QString engine = groupTranslate.readEntry(TextSpeechToTextUtil::engineTextToSpeechName(), TextSpeechToTextUtil::defaultEngineName());
    const int index = mEngine->findData(engine);
    if (index != -1) {
        mEngine->setCurrentIndex(index);
    }
}

void SpeechToTextComboBoxWidget::save()
{
    const QString engine = mEngine->currentData().toString();
    KConfigGroup groupTranslate(KSharedConfig::openConfig(), TextSpeechToTextUtil::groupTranslateName());
    groupTranslate.writeEntry(TextSpeechToTextUtil::engineTextToSpeechName(), engine);
}

#include "moc_speechtotextcomboboxwidget.cpp"
