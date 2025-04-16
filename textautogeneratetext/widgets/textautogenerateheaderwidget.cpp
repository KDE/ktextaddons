/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateheaderwidget.h"
#include "widgets/textautogenerateconfiguredialog.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutogenerateText;
TextAutogenerateHeaderWidget::TextAutogenerateHeaderWidget(QWidget *parent)
    : QWidget{parent}
    , mEngineName(new QLabel(this))
    , mConfigureEngine(new QToolButton(this))
    , mClearChat(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mEngineName->setObjectName("mEngineName"_L1);
    mainLayout->addWidget(mEngineName);
    QFont f = mEngineName->font();
    f.setBold(true);
    f.setItalic(true);
    mEngineName->setFont(f);

    mConfigureEngine->setObjectName("mConfigureEngine"_L1);
    mConfigureEngine->setToolTip(i18nc("@info:tooltip", "Configure…"));
    mConfigureEngine->setAutoRaise(true);
    mConfigureEngine->setIcon(QIcon::fromTheme(QStringLiteral("settings-configure")));
    mainLayout->addWidget(mConfigureEngine);
    mainLayout->addStretch(1);
    connect(mConfigureEngine, &QToolButton::clicked, this, &TextAutogenerateHeaderWidget::slotConfigureEngine);

    mClearChat->setObjectName("mClearChat"_L1);
    mClearChat->setToolTip(i18nc("@info:tooltip", "Clear"));
    mClearChat->setAutoRaise(true);
    mClearChat->setIcon(QIcon::fromTheme(QStringLiteral("settings-configure"))); // TODO fix it
    mainLayout->addWidget(mClearChat);
}

TextAutogenerateHeaderWidget::~TextAutogenerateHeaderWidget() = default;

void TextAutogenerateHeaderWidget::updateEngineName(const QString &engineName)
{
    mEngineName->setText(engineName);
}

void TextAutogenerateHeaderWidget::slotConfigureEngine()
{
    TextAutogenerateText::TextAutogenerateConfigureDialog d(this);
    if (d.exec()) {
        d.saveSettings();
        Q_EMIT configChanged();
    }
}

#include "moc_textautogenerateheaderwidget.cpp"
