/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechconfigwidget.h"

#include "textedittexttospeech_debug.h"
#include "texttospeechconfiginterface.h"
#include "texttospeechlanguagecombobox.h"
#include "texttospeechsliderwidget.h"
#include "texttospeechvoicecombobox.h"

#include "texttospeechutil.h"
#include <KLocalizedString>

#include <KConfig>
#include <KConfigGroup>
#include <QComboBox>
#include <QFormLayout>
#include <QPushButton>
#include <QTimer>

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;
TextToSpeechConfigWidget::TextToSpeechConfigWidget(QWidget *parent)
    : QWidget(parent)
    , mVolume(new TextToSpeechSliderWidget(u"%1 %"_s, this))
    , mRate(new TextToSpeechSliderWidget(u"%1"_s, this))
    , mPitch(new TextToSpeechSliderWidget(u"%1"_s, this))
    , mAvailableEngine(new QComboBox(this))
    , mLanguage(new TextToSpeechLanguageComboBox(this))
    , mTextToSpeechConfigInterface(new TextToSpeechConfigInterface(this))
    , mVoice(new TextToSpeechVoiceComboBox(this))
    , mTestButton(new QPushButton(QIcon::fromTheme(u"player-volume"_s), i18n("Test"), this))
{
    auto layout = new QFormLayout(this);
    mVolume->setObjectName(u"volume"_s);
    mVolume->setRange(0, 100);
    connect(mVolume, &TextToSpeechSliderWidget::valueChanged, this, &TextToSpeechConfigWidget::valueChanged);

    layout->addRow(i18n("Volume:"), mVolume);

    mRate->setObjectName(u"rate"_s);
    mRate->setRange(-100, 100);
    layout->addRow(i18n("Rate:"), mRate);
    connect(mRate, &TextToSpeechSliderWidget::valueChanged, this, &TextToSpeechConfigWidget::valueChanged);

    mPitch->setRange(-100, 100);
    connect(mPitch, &TextToSpeechSliderWidget::valueChanged, this, &TextToSpeechConfigWidget::valueChanged);
    mPitch->setObjectName(u"pitch"_s);
    layout->addRow(i18n("Pitch:"), mPitch);

    mAvailableEngine->setObjectName(u"engine"_s);
    layout->addRow(i18n("Engine:"), mAvailableEngine);
    connect(mAvailableEngine, &QComboBox::currentIndexChanged, this, &TextToSpeechConfigWidget::slotAvailableEngineChanged);

    mLanguage->setObjectName(u"language"_s);
    layout->addRow(i18n("Language:"), mLanguage);
    connect(mLanguage, &QComboBox::currentIndexChanged, this, &TextToSpeechConfigWidget::valueChanged);

    mVoice->setObjectName(u"voice"_s);
    layout->addRow(i18n("Voice:"), mVoice);
    connect(mVoice, &QComboBox::currentIndexChanged, this, &TextToSpeechConfigWidget::valueChanged);

    mTestButton->setObjectName(u"mTestButton"_s);
    layout->addWidget(mTestButton);
    connect(mTestButton, &QPushButton::clicked, this, &TextToSpeechConfigWidget::slotTestTextToSpeech);
    QTimer::singleShot(0, this, &TextToSpeechConfigWidget::slotUpdateSettings);
}

TextToSpeechConfigWidget::~TextToSpeechConfigWidget() = default;

void TextToSpeechConfigWidget::initializeSettings()
{
    slotAvailableEngineChanged();
}

void TextToSpeechConfigWidget::slotAvailableEngineChanged()
{
    slotEngineChanged();
    slotLanguageChanged();
    valueChanged();
}

void TextToSpeechConfigWidget::valueChanged()
{
    Q_EMIT configChanged(true);
}

void TextToSpeechConfigWidget::updateLocale()
{
    KConfig config(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigFileName());
    const KConfigGroup grp = config.group(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigGroupName());
    const QString localeName = grp.readEntry("localeName");
    if (localeName.isEmpty()) {
        return;
    }
    mLanguage->selectLocaleName(localeName);
}

void TextToSpeechConfigWidget::readConfig()
{
    const TextEditTextToSpeech::TextToSpeechUtil::TextToSpeechSettings settings = TextEditTextToSpeech::TextToSpeechUtil::loadSettings();
    mRate->setValue(settings.rate);
    mPitch->setValue(settings.pitch);
    mVolume->setValue(settings.volumeValue);
    mLanguage->selectLocaleName(settings.localeName);
    const QString engineName = settings.engineName;
    // qDebug() << " engineName " << engineName;
    const int engineIndex = mAvailableEngine->findData(engineName);
    // qDebug() << " engineIndex " << engineIndex;
    if (engineIndex != -1) {
        mAvailableEngine->setCurrentIndex(engineIndex);
    }
    // FIXME: list of voice is not loading here... need to fix it
    mVoice->setCurrentVoice(settings.voice);
    // qDebug() << " load settings " << settings;
}

void TextToSpeechConfigWidget::writeConfig()
{
    TextEditTextToSpeech::TextToSpeechUtil::TextToSpeechSettings settings;
    settings.volumeValue = mVolume->value();
    settings.rate = mRate->value();
    settings.pitch = mPitch->value();
    settings.localeName = mLanguage->currentData().toLocale().name();
    settings.engineName = mAvailableEngine->currentData().toString();
    settings.voice = mVoice->currentVoice();
    // qDebug() << " save settings " << settings;
    TextEditTextToSpeech::TextToSpeechUtil::writeConfig(std::move(settings));
}

void TextToSpeechConfigWidget::slotLocalesAndVoices()
{
    updateAvailableLocales();
    updateAvailableVoices();
}

void TextToSpeechConfigWidget::slotUpdateSettings()
{
    updateAvailableEngine();
    slotLocalesAndVoices();
    readConfig();
}

void TextToSpeechConfigWidget::setTextToSpeechConfigInterface(TextToSpeechConfigInterface *interface)
{
    delete mTextToSpeechConfigInterface;
    mTextToSpeechConfigInterface = interface;
    slotLocalesAndVoices();
}

void TextToSpeechConfigWidget::restoreDefaults()
{
    mRate->setValue(0);
    mPitch->setValue(0);
    mVolume->setValue(50);

    // TODO load default value
}

void TextToSpeechConfigWidget::slotTestTextToSpeech()
{
    TextToSpeechConfigInterface::EngineSettings settings;
    settings.rate = mRate->value();
    settings.pitch = mPitch->value();
    settings.volume = mVolume->value();
    settings.localeName = mLanguage->currentData().toLocale().name();
    settings.voice = mVoice->currentVoice();
    qCDebug(TEXTEDITTEXTTOSPEECH_LOG) << " settings " << settings;
    mTextToSpeechConfigInterface->testEngine(settings);
}

void TextToSpeechConfigWidget::updateAvailableEngine()
{
    mAvailableEngine->clear();
    const QStringList lst = mTextToSpeechConfigInterface->availableEngines();
    for (const QString &engine : lst) {
        if (engine != "mock"_L1) {
            mAvailableEngine->addItem(engine, engine);
        }
    }
    mAvailableEngine->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    updateEngine();
}

void TextToSpeechConfigWidget::updateAvailableVoices()
{
    const QVector<QVoice> voices = mTextToSpeechConfigInterface->availableVoices();
    mVoice->updateVoices(voices);
    updateVoice();
}

void TextToSpeechConfigWidget::updateVoice()
{
    KConfig config(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigFileName());
    const KConfigGroup grp = config.group(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigGroupName());
    const QString voice = grp.readEntry("voice");
    int index = mVoice->findData(voice);
    if (index == -1) {
        index = 0;
    }
    mVoice->setCurrentIndex(index);
}

void TextToSpeechConfigWidget::updateEngine()
{
    KConfig config(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigFileName());
    const KConfigGroup grp = config.group(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigGroupName());
    const QString engineName = grp.readEntry("engine");
    int index = mAvailableEngine->findData(engineName);
    if (index == -1) {
        index = 0;
    }
    mAvailableEngine->setCurrentIndex(index);
}

void TextToSpeechConfigWidget::updateAvailableLocales()
{
    mLanguage->clear();
    const QVector<QLocale> locales = mTextToSpeechConfigInterface->availableLocales();
    const QLocale current = mTextToSpeechConfigInterface->locale();
    mLanguage->updateAvailableLocales(locales, current);
    updateLocale();
}

void TextToSpeechConfigWidget::slotEngineChanged()
{
    const QString newEngineName = mAvailableEngine->currentData().toString();
    qCDebug(TEXTEDITTEXTTOSPEECH_LOG) << "newEngineName " << newEngineName;
    mTextToSpeechConfigInterface->setEngine(newEngineName);
    updateAvailableLocales();
    slotLocalesAndVoices();
}

void TextToSpeechConfigWidget::slotLanguageChanged()
{
    // QLocale locale = mLanguage->currentData().value<QLocale>();
    // TODO
    qCWarning(TEXTEDITTEXTTOSPEECH_LOG) << "slotLanguageChanged: not implemented yet";
}

#include "moc_texttospeechconfigwidget.cpp"
