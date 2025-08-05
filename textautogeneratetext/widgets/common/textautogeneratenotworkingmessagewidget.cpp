/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratenotworkingmessagewidget.h"
#include "core/textautogeneratetextutils.h"

#include <KLocalizedString>
#include <QDesktopServices>
#include <QUrl>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateNotWorkingMessageWidget::TextAutoGenerateNotWorkingMessageWidget(QWidget *parent)
    : KMessageWidget(parent)
{
    setCloseButtonVisible(false);
    setMessageType(KMessageWidget::MessageType::Error);
    setPosition(KMessageWidget::Header);
}

TextAutoGenerateNotWorkingMessageWidget::~TextAutoGenerateNotWorkingMessageWidget() = default;

void TextAutoGenerateNotWorkingMessageWidget::slotDownloadOllama()
{
#if defined(Q_OS_WIN)
    QDesktopServices::openUrl(QUrl(u"https://ollama.com/download/windows"_s));
#elif defined(Q_OS_MACOS)
    QDesktopServices::openUrl(QUrl(u"https://ollama.com/download/mac"_s));
#endif
}

void TextAutoGenerateNotWorkingMessageWidget::setMessageInfo(const QString &errorMessage)
{
    const QString ollamaPath = TextAutoGenerateText::TextAutoGenerateTextUtils::findExecutable(u"ollama"_s);
    if (ollamaPath.isEmpty()) {
#if !defined(Q_OS_WIN) && !defined(Q_OS_MACOS)
        setText(i18n("Ollama not found on system. Ask to your administrator system to install it."));
#else
        setText(i18n("Ollama not found on system. Please install it."));
        auto downloadOllamaAction = new QAction(i18nc("@action", "Download Ollama"), this);
        downloadOllamaAction->setObjectName(u"downloadOllamaAction"_s);
        connect(downloadOllamaAction, &QAction::triggered, this, &TextAutoGenerateNotWorkingMessageWidget::slotDownloadOllama);
        addAction(downloadOllamaAction);
#endif
    } else {
        setText(errorMessage);
        auto startOllamaAction = new QAction(i18nc("@action", "Start Ollama"), this);
        startOllamaAction->setObjectName(u"startOllamaAction"_s);
        connect(startOllamaAction, &QAction::triggered, this, &TextAutoGenerateNotWorkingMessageWidget::startOllama);
        addAction(startOllamaAction);
    }
}

#include "moc_textautogeneratenotworkingmessagewidget.cpp"
