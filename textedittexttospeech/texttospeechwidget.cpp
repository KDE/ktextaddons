/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "texttospeechactions.h"
#include "texttospeechconfigdialog.h"
#include "texttospeechinterface.h"
#include "texttospeechsliderwidget.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPointer>
#include <QTimer>
#include <QToolButton>

using namespace std::chrono_literals;
#include <chrono>

using namespace TextEditTextToSpeech;

class Q_DECL_HIDDEN TextEditTextToSpeech::TextToSpeechWidgetPrivate
{
public:
    TextToSpeechWidgetPrivate() = default;

    QPointer<TextEditTextToSpeech::TextToSpeechConfigDialog> mConfigDialog;
    QToolButton *mStopButton = nullptr;
    QToolButton *mPlayPauseButton = nullptr;
    QToolButton *mConfigureButton = nullptr;
    TextToSpeechInterface *mTextToSpeechInterface = nullptr;
    TextToSpeechActions *mTextToSpeechActions = nullptr;
    TextToSpeechSliderWidget *mVolume = nullptr;
    bool mNeedToHide = false;
};

TextToSpeechWidget::TextToSpeechWidget(QWidget *parent)
    : QWidget(parent)
    , d(new TextEditTextToSpeech::TextToSpeechWidgetPrivate)
{
    auto hbox = new QHBoxLayout(this);
    hbox->setObjectName(u"hbox"_s);
    hbox->setContentsMargins(QMargins{});

    d->mTextToSpeechActions = new TextToSpeechActions(this);
    connect(d->mTextToSpeechActions, &TextToSpeechActions::stateChanged, this, &TextToSpeechWidget::stateChanged);

    auto close = new QToolButton(this);
    close->setObjectName(u"close-button"_s);
    close->setIcon(QIcon::fromTheme(u"dialog-close"_s));
    close->setToolTip(i18nc("@info:tooltip", "Close"));
    connect(close, &QToolButton::clicked, this, &TextToSpeechWidget::slotCloseTextToSpeechWidget);
    hbox->addWidget(close);
    hbox->addStretch(0);

    auto volume = new QLabel(i18nc("@label:textbox", "Volume:"), this);
    volume->setTextFormat(Qt::PlainText);
    hbox->addWidget(volume);
    d->mVolume = new TextToSpeechSliderWidget(u"%1 %"_s, this);
    d->mVolume->setMinimumWidth(100);
    d->mVolume->setObjectName(u"volumeslider"_s);
    d->mVolume->setRange(0, 100);
    connect(d->mVolume, &TextToSpeechSliderWidget::valueChanged, this, &TextToSpeechWidget::slotVolumeChanged);
    hbox->addWidget(d->mVolume);

    d->mStopButton = new QToolButton(this);
    d->mStopButton->setObjectName(u"stopbutton"_s);
    d->mStopButton->setDefaultAction(d->mTextToSpeechActions->stopAction());
    hbox->addWidget(d->mStopButton);

    d->mPlayPauseButton = new QToolButton(this);
    d->mPlayPauseButton->setObjectName(u"playpausebutton"_s);
    d->mPlayPauseButton->setDefaultAction(d->mTextToSpeechActions->playPauseAction());
    hbox->addWidget(d->mPlayPauseButton);

    d->mConfigureButton = new QToolButton(this);
    d->mConfigureButton->setIcon(QIcon::fromTheme(u"configure"_s));
    d->mConfigureButton->setToolTip(i18nc("@info:tooltip", "Configure…"));
    d->mConfigureButton->setObjectName(u"configurebutton"_s);
    connect(d->mConfigureButton, &QToolButton::clicked, this, &TextToSpeechWidget::slotConfigure);
    hbox->addWidget(d->mConfigureButton);

    d->mTextToSpeechInterface = new TextToSpeechInterface(this, this);
    applyVolume();
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    hideWidget();
}

TextToSpeechWidget::~TextToSpeechWidget() = default;

void TextToSpeechWidget::slotCloseTextToSpeechWidget()
{
    d->mTextToSpeechActions->slotStop();
    hideWidget();
}

void TextToSpeechWidget::slotConfigure()
{
    if (!d->mConfigDialog.data()) {
        d->mNeedToHide = false;
        d->mConfigDialog = new TextToSpeechConfigDialog(this);
        if (d->mConfigDialog->exec()) {
            d->mTextToSpeechInterface->reloadSettings();
            applyVolume();
        }
        delete d->mConfigDialog;
        if (d->mNeedToHide) {
            hideWidget();
            d->mNeedToHide = false;
        }
    }
}

void TextToSpeechWidget::slotVolumeChanged(int value)
{
    d->mTextToSpeechInterface->setVolume(value / 100.0);
}

bool TextToSpeechWidget::isReady() const
{
    return d->mTextToSpeechInterface->isReady();
}

void TextToSpeechWidget::say(const QString &text)
{
    if (!text.isEmpty()) {
        if (d->mTextToSpeechInterface->isReady()) {
            d->mTextToSpeechInterface->say(text);
        } else {
            KMessageBox::error(this, i18n("Engine has a problem."), i18nc("@title:window", "Text To Speech"));
        }
    }
}

TextToSpeechWidget::State TextToSpeechWidget::state() const
{
    return d->mTextToSpeechActions->state();
}

void TextToSpeechWidget::slotStateChanged(TextEditTextToSpeech::TextToSpeech::State state)
{
    switch (state) {
    case TextEditTextToSpeech::TextToSpeech::Ready:
        if (state == TextEditTextToSpeech::TextToSpeech::Ready) {
            d->mTextToSpeechActions->setState(TextToSpeechWidget::Stop);
            if (d->mConfigDialog) {
                d->mNeedToHide = true;
            } else {
                QTimer::singleShot(2s, this, &TextToSpeechWidget::hideWidget);
            }
        }
        break;
    default:
        // TODO
        break;
    }
}

void TextToSpeechWidget::showWidget()
{
    show();
    Q_EMIT changeVisibility(true);
}

void TextToSpeechWidget::hideWidget()
{
    hide();
    Q_EMIT changeVisibility(false);
}

void TextToSpeechWidget::setState(TextToSpeechWidget::State state)
{
    d->mTextToSpeechActions->setState(state);
}

void TextToSpeechWidget::setTextToSpeechInterface(TextToSpeechInterface *interface)
{
    delete d->mTextToSpeechInterface;
    d->mTextToSpeechInterface = interface;
    // Update volume value
    if (d->mTextToSpeechInterface) {
        d->mTextToSpeechInterface->reloadSettings();
        applyVolume();
    }
}

void TextToSpeechWidget::applyVolume()
{
    // Api return volume between 0.0 -> 1.0
    // We want display between 0 -> 100
    d->mVolume->setValue(d->mTextToSpeechInterface->volume() * 100);
}

#include "moc_texttospeechwidget.cpp"
