/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchdialog.h"
using namespace Qt::Literals::StringLiterals;

#include "textautogeneratesearchwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
const char myTextAutoGenerateSearchDialogGroupName[] = "TextAutoGenerateSearchDialog";
}
using namespace TextAutoGenerateText;
TextAutoGenerateSearchDialog::TextAutoGenerateSearchDialog(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QDialog{parent}
    , mTextAutoGenerateSearchWidget(new TextAutoGenerateSearchWidget(manager, this))
{
    setWindowTitle(i18nc("@title:window", "Search"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mTextAutoGenerateSearchWidget->setObjectName(u"mTextAutoGenerateSearchWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateSearchWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateSearchDialog::reject);
    readConfig();
}

TextAutoGenerateSearchDialog::~TextAutoGenerateSearchDialog()
{
    writeConfig();
}

void TextAutoGenerateSearchDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateSearchDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAutoGenerateSearchDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateSearchDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_textautogeneratesearchdialog.cpp"
