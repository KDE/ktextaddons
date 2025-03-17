/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratedialog.h"
#include "textautogeneratestackwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
const char myTextAutogenerateDialogGroupName[] = "TextAutogenerateDialog";
}
using namespace TextAutogenerateText;

TextAutogenerateDialog::TextAutogenerateDialog(QWidget *parent)
    : QDialog(parent)
    , mTextAutogenerateWidget(new TextAutogenerateStackWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Conversation"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mTextAutogenerateWidget->setObjectName(QStringLiteral("mTextAutogenerateWidget"));
    mainLayout->addWidget(mTextAutogenerateWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(QStringLiteral("button"));
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutogenerateDialog::reject);
    readConfig();
}

TextAutogenerateDialog::~TextAutogenerateDialog()
{
    writeConfig();
}

void TextAutogenerateDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutogenerateDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAutogenerateDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutogenerateDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_textautogeneratedialog.cpp"
