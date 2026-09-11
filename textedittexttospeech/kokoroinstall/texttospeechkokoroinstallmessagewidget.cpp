/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokoroinstallmessagewidget.h"
#include <KLocalizedString>

using namespace TextEditTextToSpeech;
TextToSpeechKokoroInstallMessageWidget::TextToSpeechKokoroInstallMessageWidget(QWidget *parent)
    : KMessageWidget(parent)
{
    setMessageType(KMessageWidget::MessageType::Error);
    setWordWrap(true);
    setCloseButtonVisible(true);

    auto installAction = new QAction(i18nc("@action", "Install"), this);
    addAction(installAction);
    connect(installAction, &QAction::triggered, this, [this]() {
        Q_EMIT installPackages();
    });
}

TextToSpeechKokoroInstallMessageWidget::~TextToSpeechKokoroInstallMessageWidget() = default;
#include "moc_texttospeechkokoroinstallmessagewidget.cpp"
