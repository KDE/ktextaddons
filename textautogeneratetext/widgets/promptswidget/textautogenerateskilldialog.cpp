/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateskilldialog.h"
#include "core/prompts/textautogenerateskill.h"
#include "textautogenerateskillwidget.h"
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
const char myTextAutoGenerateSkillDialogGroupName[] = "TextAutoGenerateSkillDialog";
}
TextAutoGenerateSkillDialog::TextAutoGenerateSkillDialog(QWidget *parent)
    : QDialog(parent)
    , mSkillWidget(new TextAutoGenerateSkillWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Debug"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mSkillWidget->setObjectName(u"mPromptWidget"_s);
    mainLayout->addWidget(mSkillWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateSkillDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateSkillDialog::accept);
    readConfig();
}

TextAutoGenerateSkillDialog::~TextAutoGenerateSkillDialog()
{
    writeConfig();
}

void TextAutoGenerateSkillDialog::setSkill(const TextAutoGenerateText::TextAutoGenerateSkill &prompt)
{
    mSkillWidget->setSkill(prompt);
}

TextAutoGenerateText::TextAutoGenerateSkill TextAutoGenerateSkillDialog::skill() const
{
    return mSkillWidget->skill();
}

void TextAutoGenerateSkillDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateSkillDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAutoGenerateSkillDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateSkillDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_textautogenerateskilldialog.cpp"
