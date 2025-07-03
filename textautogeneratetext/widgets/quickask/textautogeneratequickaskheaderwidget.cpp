/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskheaderwidget.h"
#include <QLabel>

#include "core/textautogeneratemanager.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QToolButton>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateQuickAskHeaderWidget::TextAutoGenerateQuickAskHeaderWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mModelInstanceLabel(new QLabel(this))
    , mManager(manager)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mModelInstanceLabel->setObjectName(u"mModelInstanceLabel"_s);
    mainLayout->addWidget(mModelInstanceLabel);

    mainLayout->addStretch(1);
    auto configureButton = new QToolButton(this);
    configureButton->setAutoRaise(true);
    configureButton->setObjectName(u"configureButton"_s);
    configureButton->setIcon(QIcon::fromTheme(u"settings-configure"_s));
    configureButton->setToolTip(i18nc("@info:tooltip", "Configure…"));
    mainLayout->addWidget(configureButton);

    QFont f = mModelInstanceLabel->font();
    f.setBold(true);
    f.setItalic(true);
    mModelInstanceLabel->setFont(f);

    connect(configureButton, &QToolButton::clicked, this, &TextAutoGenerateQuickAskHeaderWidget::configureRequested);
    connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::loadEngineDone, this, [this]() {
        updateEngineModelName(mManager->generateEngineDisplayName());
    });
}

TextAutoGenerateQuickAskHeaderWidget::~TextAutoGenerateQuickAskHeaderWidget() = default;

void TextAutoGenerateQuickAskHeaderWidget::updateEngineModelName(const QString &str)
{
    mModelInstanceLabel->setText(str);
}

#include "moc_textautogeneratequickaskheaderwidget.cpp"
