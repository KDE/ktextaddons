/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextinstallmessagewidget.h"
#include <KLocalizedString>
#include <QAction>

using namespace Qt::Literals::StringLiterals;

WhisperSpeechToTextInstallMessageWidget::WhisperSpeechToTextInstallMessageWidget(QWidget *parent)
    : KMessageWidget(parent)
{
    setMessageType(KMessageWidget::MessageType::Error);
    setWordWrap(true);
    setCloseButtonVisible(true);

    auto installAction = new QAction(i18nc("@action", "Install"), this);
    installAction->setObjectName(u"installAction"_s);
    addAction(installAction);
    connect(installAction, &QAction::triggered, this, [this]() {
        Q_EMIT installPackages(mMissingPackages);
    });
}

WhisperSpeechToTextInstallMessageWidget::~WhisperSpeechToTextInstallMessageWidget() = default;

void WhisperSpeechToTextInstallMessageWidget::setMissingPackages(const QStringList &list)
{
    mMissingPackages = list;
}

#include "moc_whisperspeechtotextinstallmessagewidget.cpp"
