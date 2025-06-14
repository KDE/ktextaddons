/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratestackwidget.h"
#include "common/textautogeneratenotworkingwidget.h"
#include "textautogeneratewidget.h"

#include <QStackedWidget>
#include <QVBoxLayout>

using namespace TextAutoGenerateText;
TextAutoGenerateStackWidget::TextAutoGenerateStackWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mStackedWidget(new QStackedWidget(this))
    , mTextAutoGenerateNotWorkingWidget(new TextAutoGenerateNotWorkingWidget(manager, this))
    , mTextAutoGenerateWidget(new TextAutoGenerateWidget(manager, this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mainLayout->addWidget(mStackedWidget);
    mTextAutoGenerateNotWorkingWidget->setObjectName(QStringLiteral("mTextAutoGenerateNotWorkingWidget"));
    mStackedWidget->addWidget(mTextAutoGenerateNotWorkingWidget);

    mTextAutoGenerateWidget->setObjectName(QStringLiteral("mTextAutoGenerateWidget"));
    mStackedWidget->addWidget(mTextAutoGenerateWidget);
    mStackedWidget->setCurrentWidget(mTextAutoGenerateWidget);

    connect(mTextAutoGenerateWidget, &TextAutoGenerateWidget::noPluginsFound, this, [this](const QString &msg) {
        setBrokenEngine(true, msg);
    });
    connect(mTextAutoGenerateWidget, &TextAutoGenerateWidget::pluginBroken, this, [this](const QString &msg) {
        setBrokenEngine(true, msg);
    });
    connect(mTextAutoGenerateNotWorkingWidget, &TextAutoGenerateNotWorkingWidget::ollamaStarted, this, [this]() {
        setBrokenEngine(false, {});
    });
}

TextAutoGenerateStackWidget::~TextAutoGenerateStackWidget() = default;

void TextAutoGenerateStackWidget::setBrokenEngine(bool state, const QString &errorMessage)
{
    if (state) {
        mTextAutoGenerateNotWorkingWidget->setMessageError(errorMessage);
        mStackedWidget->setCurrentWidget(mTextAutoGenerateNotWorkingWidget);
    } else {
        mTextAutoGenerateNotWorkingWidget->clearMessage();
        mStackedWidget->setCurrentWidget(mTextAutoGenerateWidget);
    }
}

#include "moc_textautogeneratestackwidget.cpp"
