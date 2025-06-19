/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratenotworkingwidget.h"
#include "core/textautogeneratetextutils.h"
#include "textautogeneratenotworkingmessagewidget.h"
#include "textautogeneratetextwidget_debug.h"
#include <KLocalizedString>
#include <KMessageWidget>
#include <QProcess>
#include <QPushButton>
#include <QVBoxLayout>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateNotWorkingWidget::TextAutoGenerateNotWorkingWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mMessageWidget(new TextAutoGenerateNotWorkingMessageWidget(this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mMessageWidget->setObjectName("mMessageWidget"_L1);
    mainLayout->addWidget(mMessageWidget, 0, Qt::AlignVCenter);
    connect(mMessageWidget, &TextAutoGenerateNotWorkingMessageWidget::startOllama, this, &TextAutoGenerateNotWorkingWidget::slotStartOllama);

    auto configureButton = new QPushButton(i18nc("@action:button", "Configure…"), this);
    configureButton->setObjectName("configureButton"_L1);
    connect(configureButton, &QPushButton::clicked, this, &TextAutoGenerateNotWorkingWidget::slotConfigure);
    mainLayout->addWidget(configureButton, 0, Qt::AlignVCenter);
    mainLayout->addStretch(1);
}

TextAutoGenerateNotWorkingWidget::~TextAutoGenerateNotWorkingWidget() = default;

void TextAutoGenerateNotWorkingWidget::setMessageError(const QString &str)
{
    mMessageWidget->setText(str);
    mMessageWidget->animatedShow();
}

void TextAutoGenerateNotWorkingWidget::clearMessage()
{
    mMessageWidget->setText({});
    mMessageWidget->animatedHide();
}

void TextAutoGenerateNotWorkingWidget::slotConfigure()
{
}

void TextAutoGenerateNotWorkingWidget::slotStartOllama()
{
    const QString ollamaPath = TextAutoGenerateText::TextAutoGenerateTextUtils::findExecutable(QStringLiteral("ollama"));
    if (ollamaPath.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Ollama doesn't exist";
        return;
    }
    const bool status = QProcess::startDetached(ollamaPath, {QStringLiteral("start")});
    if (!status) {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Impossible to start ollama";
    } else {
        clearMessage();
        Q_EMIT ollamaStarted();
    }
}

#include "moc_textautogeneratenotworkingwidget.cpp"
