/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratepromptdialog.h"
#include "core/prompts/textautogenerateprompt.h"
#include "textautogeneratepromptwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
namespace
{
const char myTextAutoGeneratePromptDialogGroupName[] = "TextAutoGeneratePromptDialog";
}
TextAutoGeneratePromptDialog::TextAutoGeneratePromptDialog(QWidget *parent)
    : QDialog(parent)
    , mPromptWidget(new TextAutoGeneratePromptWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Debug"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mPromptWidget->setObjectName(u"mPromptWidget"_s);
    mainLayout->addWidget(mPromptWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGeneratePromptDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGeneratePromptDialog::accept);
    readConfig();
}

TextAutoGeneratePromptDialog::~TextAutoGeneratePromptDialog()
{
    writeConfig();
}

void TextAutoGeneratePromptDialog::setPrompt(const TextAutoGenerateText::TextAutoGeneratePrompt &prompt)
{
    mPromptWidget->setPrompt(prompt);
}

TextAutoGenerateText::TextAutoGeneratePrompt TextAutoGeneratePromptDialog::prompt() const
{
    return mPromptWidget->prompt();
}

void TextAutoGeneratePromptDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGeneratePromptDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAutoGeneratePromptDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGeneratePromptDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_textautogeneratepromptdialog.cpp"
