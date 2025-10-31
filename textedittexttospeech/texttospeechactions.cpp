/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechactions.h"

#include <KLocalizedString>
#include <QAction>

using namespace TextEditTextToSpeech;
using namespace Qt::Literals::StringLiterals;

class Q_DECL_HIDDEN TextEditTextToSpeech::TextToSpeechActionsPrivate
{
public:
    TextToSpeechActionsPrivate() = default;

    void updateButtonState();
    TextToSpeechWidget::State mState = TextToSpeechWidget::Stop;
    QAction *mStopAction = nullptr;
    QAction *mPlayPauseAction = nullptr;
};

TextToSpeechActions::TextToSpeechActions(QObject *parent)
    : QObject(parent)
    , d(new TextEditTextToSpeech::TextToSpeechActionsPrivate)
{
    d->mStopAction = new QAction(i18nc("@action", "Stop"), this);
    d->mStopAction->setObjectName(u"stopbutton"_s);
    d->mStopAction->setIcon(QIcon::fromTheme(u"media-playback-stop"_s));
    d->mStopAction->setToolTip(i18nc("@info:tooltip", "Stop"));
    connect(d->mStopAction, &QAction::triggered, this, &TextToSpeechActions::slotStop);

    d->mPlayPauseAction = new QAction(this);
    d->mPlayPauseAction->setObjectName(u"playpausebutton"_s);
    d->mPlayPauseAction->setIcon(QIcon::fromTheme(u"media-playback-start"_s));
    connect(d->mPlayPauseAction, &QAction::triggered, this, &TextToSpeechActions::slotPlayPause);

    d->updateButtonState();
}

TextToSpeechActions::~TextToSpeechActions() = default;

QAction *TextToSpeechActions::stopAction() const
{
    return d->mStopAction;
}

QAction *TextToSpeechActions::playPauseAction() const
{
    return d->mPlayPauseAction;
}

TextToSpeechWidget::State TextToSpeechActions::state() const
{
    return d->mState;
}

void TextToSpeechActions::setState(TextToSpeechWidget::State state)
{
    if (d->mState != state) {
        d->mState = state;
        d->updateButtonState();
    }
}

void TextToSpeechActionsPrivate::updateButtonState()
{
    mPlayPauseAction->setIcon(QIcon::fromTheme((mState == TextToSpeechWidget::Stop) ? u"media-playback-start"_s : u"media-playback-pause"_s));
    mPlayPauseAction->setEnabled((mState != TextToSpeechWidget::Stop));
    const QString text = (mState != TextToSpeechWidget::Play) ? i18n("Pause") : i18n("Play");
    mPlayPauseAction->setToolTip(text);
    mPlayPauseAction->setText(text);
}

void TextToSpeechActions::slotPlayPause()
{
    if (d->mState == TextEditTextToSpeech::TextToSpeechWidget::Pause || d->mState == TextEditTextToSpeech::TextToSpeechWidget::Stop) {
        d->mState = TextEditTextToSpeech::TextToSpeechWidget::Play;
    } else if (d->mState == TextEditTextToSpeech::TextToSpeechWidget::Play) {
        d->mState = TextEditTextToSpeech::TextToSpeechWidget::Pause;
    } else {
        return;
    }
    d->updateButtonState();
    Q_EMIT stateChanged(d->mState);
}

void TextToSpeechActions::slotStop()
{
    if (d->mState != TextEditTextToSpeech::TextToSpeechWidget::Stop) {
        d->mState = TextEditTextToSpeech::TextToSpeechWidget::Stop;
        d->updateButtonState();
        Q_EMIT stateChanged(d->mState);
    }
}

#include "moc_texttospeechactions.cpp"
