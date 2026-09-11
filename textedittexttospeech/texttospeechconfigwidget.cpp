/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechconfigwidget.h"

#include "kokoroinstall/texttospeechkokorocheckjob.h"
#include "kokoroinstall/texttospeechkokoroinstallmessagewidget.h"
#include "kokoroinstall/texttospeechkokoroinstallpythondialog.h"
#include "textedittexttospeech_debug.h"
#include "texttospeechconfiginterface.h"
#include "texttospeechlanguagecombobox.h"
#include "texttospeechsliderwidget.h"
#include "texttospeechvoicecombobox.h"

#include "texttospeechutil.h"
#include <KLocalizedString>

#include <KConfig>
#include <KConfigGroup>
#include <KMessageWidget>
#include <QComboBox>
#include <QFormLayout>
#include <QPointer>
#include <QPushButton>
#include <QSignalBlocker>
#include <QTimer>

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;
TextToSpeechConfigWidget::TextToSpeechConfigWidget(QWidget *parent)
    : QWidget(parent)
    , mVolume(new TextToSpeechSliderWidget(u"%1 %"_s, this))
    , mRate(new TextToSpeechSliderWidget(u"%1"_s, this))
    , mPitch(new TextToSpeechSliderWidget(u"%1"_s, this))
    , mAvailableEngineCombobox(new QComboBox(this))
    , mLanguageComboBox(new TextToSpeechLanguageComboBox(this))
    , mTextToSpeechConfigInterface(new TextToSpeechConfigInterface(this))
    , mVoiceComboBox(new TextToSpeechVoiceComboBox(this))
    , mTestButton(new QPushButton(QIcon::fromTheme(u"player-volume"_s), i18n("Test"), this))
    , mMessageErrorWidget(new KMessageWidget(this))
    , mKokoroInstallMessageWidget(new TextToSpeechKokoroInstallMessageWidget(this))
{
    auto layout = new QFormLayout(this);
    layout->setContentsMargins({});

    mMessageErrorWidget->setObjectName(u"mMessageErrorWidget"_s);
    mMessageErrorWidget->setMessageType(KMessageWidget::Error);
    mMessageErrorWidget->hide();
    layout->addRow(mMessageErrorWidget);

    mKokoroInstallMessageWidget->setObjectName(u"mMessageErrorWidget"_s);
    layout->addRow(mKokoroInstallMessageWidget);

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

    mAvailableEngineCombobox->setObjectName(u"engine"_s);
    mAvailableEngineCombobox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    layout->addRow(i18n("Engine:"), mAvailableEngineCombobox);
    connect(mAvailableEngineCombobox, &QComboBox::currentIndexChanged, this, &TextToSpeechConfigWidget::slotAvailableEngineChanged);

    mLanguageComboBox->setObjectName(u"language"_s);
    layout->addRow(i18n("Language:"), mLanguageComboBox);
    connect(mLanguageComboBox, &QComboBox::currentIndexChanged, this, &TextToSpeechConfigWidget::valueChanged);

    mVoiceComboBox->setObjectName(u"voice"_s);
    layout->addRow(i18n("Voice:"), mVoiceComboBox);
    connect(mVoiceComboBox, &QComboBox::currentIndexChanged, this, &TextToSpeechConfigWidget::valueChanged);

    mTestButton->setObjectName(u"mTestButton"_s);
    mTestButton->setCheckable(true);
    mTestButton->setChecked(false);
    layout->addWidget(mTestButton);
    connect(mTestButton, &QPushButton::clicked, this, &TextToSpeechConfigWidget::slotTestTextToSpeech);
    QTimer::singleShot(0, this, &TextToSpeechConfigWidget::slotUpdateSettings);
    connect(mTextToSpeechConfigInterface, &TextToSpeechConfigInterface::stateChanged, this, &TextToSpeechConfigWidget::slotTextChanged);
    connect(mTextToSpeechConfigInterface, &TextToSpeechConfigInterface::engineErrorOccurred, this, &TextToSpeechConfigWidget::slotEngineErrorOccurred);

    connect(mKokoroInstallMessageWidget, &TextToSpeechKokoroInstallMessageWidget::installPackages, this, &TextToSpeechConfigWidget::slotInstallKokoro);
}

TextToSpeechConfigWidget::~TextToSpeechConfigWidget() = default;

void TextToSpeechConfigWidget::slotEngineErrorOccurred(const QString &engineName, const QString &errorStr)
{
    mTestButton->setEnabled(false);
    mMessageErrorWidget->setText(i18n("%1: %2", engineName, errorStr));
    mMessageErrorWidget->animatedShow();
}

void TextToSpeechConfigWidget::slotTextChanged(QTextToSpeech::State state)
{
    mTestButton->setChecked(state == QTextToSpeech::Speaking);
}

void TextToSpeechConfigWidget::initializeSettings()
{
    slotAvailableEngineChanged();
}

void TextToSpeechConfigWidget::slotAvailableEngineChanged()
{
    mTestButton->setEnabled(true);
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
    mLanguageComboBox->selectLocaleName(localeName);
}

void TextToSpeechConfigWidget::readConfig()
{
    const TextEditTextToSpeech::TextToSpeechUtil::TextToSpeechSettings settings = TextEditTextToSpeech::TextToSpeechUtil::loadSettings();
    mRate->setValue(settings.rate);
    mPitch->setValue(settings.pitch);
    mVolume->setValue(settings.volumeValue);
    mLanguageComboBox->selectLocaleName(settings.localeName);
    const QString &engineName = settings.engineName;
    // qDebug() << " engineName " << engineName;
    // qDebug() << " engineIndex " << engineIndex;
    if (const int engineIndex = mAvailableEngineCombobox->findData(engineName); engineIndex != -1) {
        mAvailableEngineCombobox->setCurrentIndex(engineIndex);
    }
    // FIXME: list of voice is not loading here... need to fix it
    mVoiceComboBox->setCurrentVoice(settings.voice);
    // qDebug() << " load settings " << settings;
}

void TextToSpeechConfigWidget::writeConfig()
{
    TextEditTextToSpeech::TextToSpeechUtil::TextToSpeechSettings settings;
    settings.volumeValue = mVolume->value();
    settings.rate = mRate->value();
    settings.pitch = mPitch->value();
    settings.localeName = mLanguageComboBox->currentData().toLocale().name();
    settings.engineName = mAvailableEngineCombobox->currentData().toString();
    settings.voice = mVoiceComboBox->currentVoice();
    // qDebug() << " save settings " << settings;
    TextEditTextToSpeech::TextToSpeechUtil::writeConfig(settings);
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

void TextToSpeechConfigWidget::slotTestTextToSpeech(bool checked)
{
    if (checked) {
        TextToSpeechConfigInterface::EngineSettings settings;
        settings.rate = mRate->value();
        settings.pitch = mPitch->value();
        settings.volume = mVolume->value();
        settings.localeName = mLanguageComboBox->currentData().toLocale().name();
        settings.voice = mVoiceComboBox->currentVoice();
        qCDebug(TEXTEDITTEXTTOSPEECH_LOG) << " settings " << settings;
        mTextToSpeechConfigInterface->testEngine(settings);
    } else {
        mTextToSpeechConfigInterface->stop();
    }
}

void TextToSpeechConfigWidget::updateAvailableEngine()
{
    {
        // Filling the combobox emits currentIndexChanged() twice: once for clear() and once for
        // the first inserted item. Each emission recreates the QTextToSpeech engine and rebuilds
        // the locale and voice lists, so keep it quiet here: updateEngine() applies the selection.
        const QSignalBlocker blocker(mAvailableEngineCombobox);
        mAvailableEngineCombobox->clear();
        const QStringList lst = mTextToSpeechConfigInterface->availableEngines();
        for (const QString &engine : lst) {
            if (engine != "mock"_L1) {
                mAvailableEngineCombobox->addItem(engine, engine);
            }
        }
    }
    updateEngine();
}

void TextToSpeechConfigWidget::updateAvailableVoices()
{
    const QVector<QVoice> voices = mTextToSpeechConfigInterface->availableVoices();
    mVoiceComboBox->updateVoices(voices);
    updateVoice();
}

void TextToSpeechConfigWidget::updateVoice()
{
    KConfig config(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigFileName());
    const KConfigGroup grp = config.group(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigGroupName());
    const QString voice = grp.readEntry("voice");
    int index = mVoiceComboBox->findData(voice);
    if (index == -1) {
        index = 0;
    }
    mVoiceComboBox->setCurrentIndex(index);
}

void TextToSpeechConfigWidget::updateEngine()
{
    KConfig config(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigFileName());
    const KConfigGroup grp = config.group(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigGroupName());
    const QString engineName = grp.readEntry("engine");
    int index = mAvailableEngineCombobox->findData(engineName);
    if (index == -1) {
        index = 0;
    }
    if (mAvailableEngineCombobox->currentIndex() == index) {
        // setCurrentIndex() would not emit currentIndexChanged(), load the engine explicitly.
        slotAvailableEngineChanged();
    } else {
        mAvailableEngineCombobox->setCurrentIndex(index);
    }
}

void TextToSpeechConfigWidget::updateAvailableLocales()
{
    const QVector<QLocale> locales = mTextToSpeechConfigInterface->availableLocales();
    const QLocale current = mTextToSpeechConfigInterface->locale();
    mLanguageComboBox->updateAvailableLocales(locales, current);
    updateLocale();
}

void TextToSpeechConfigWidget::slotEngineChanged()
{
    const QString newEngineName = mAvailableEngineCombobox->currentData().toString();
    if (newEngineName == "kokoro"_L1) {
        auto job = new TextEditTextToSpeech::TextToSpeechKokoroCheckJob(this);
        connect(job, &TextEditTextToSpeech::TextToSpeechKokoroCheckJob::packagesInstalled, this, [this, newEngineName] {
            mKokoroInstallMessageWidget->animatedHide();
            mTextToSpeechConfigInterface->setEngine(newEngineName);
            slotLocalesAndVoices();
        });
        connect(job, &TextEditTextToSpeech::TextToSpeechKokoroCheckJob::needToInstallPackages, this, [this](const QStringList &missing) {
            mKokoroInstallMessageWidget->setText(i18n("Kokoro is not installed. Missing: %1", missing.join(", "_L1)));
            mKokoroInstallMessageWidget->animatedShow();
        });
        connect(job, &TextEditTextToSpeech::TextToSpeechKokoroCheckJob::needToReinstall, this, [this] {
            // TODO
        });
        job->start();
        return;
    }
    mTextToSpeechConfigInterface->setEngine(newEngineName);
    slotLocalesAndVoices();
}

void TextToSpeechConfigWidget::slotInstallKokoro()
{
    QPointer<TextToSpeechKokoroInstallPythonDialog> dlg = new TextToSpeechKokoroInstallPythonDialog(this);
    dlg->exec();
}

void TextToSpeechConfigWidget::slotLanguageChanged()
{
    // QLocale locale = mLanguage->currentData().value<QLocale>();
    // TODO
    qCWarning(TEXTEDITTEXTTOSPEECH_LOG) << "slotLanguageChanged: not implemented yet";
}

#include "moc_texttospeechconfigwidget.cpp"
