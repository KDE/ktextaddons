/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskdialog.h"

#include "textautogeneratequickaskwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
const char myQuickAskDialogGroupName[] = "QuickAskDialog";
}

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateQuickAskDialog::TextAutoGenerateQuickAskDialog(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QDialog(parent)
    , mTextAutoGenerateQuickAskWidget(new TextAutoGenerateQuickAskWidget(manager, this))
    , mManager(manager)
{
    setWindowTitle(i18nc("@title:window", "Quick Ask"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mTextAutoGenerateQuickAskWidget->setObjectName(u"mTextAutoGenerateQuickAskWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateQuickAskWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateQuickAskDialog::reject);
    readConfig();
}

TextAutoGenerateQuickAskDialog::~TextAutoGenerateQuickAskDialog()
{
    writeConfig();
}

void TextAutoGenerateQuickAskDialog::ask(const TextAutoGenerateText::TextAutoGenerateManager::AskMessageInfo &info)
{
    mManager->ask(info);
}

void TextAutoGenerateQuickAskDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myQuickAskDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAutoGenerateQuickAskDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myQuickAskDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_textautogeneratequickaskdialog.cpp"
