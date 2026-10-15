/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateagentdialog.h"
#include "core/prompts/textautogenerateagent.h"
#include "textautogenerateagentwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
namespace
{
const char myTextAutoGenerateAgentDialogGroupName[] = "TextAutoGenerateAgentDialog";
}
TextAutoGenerateAgentDialog::TextAutoGenerateAgentDialog(QWidget *parent)
    : QDialog(parent)
    , mAgentWidget(new TextAutoGenerateAgentWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Agent"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mAgentWidget->setObjectName(u"mAgentWidget"_s);
    mainLayout->addWidget(mAgentWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateAgentDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateAgentDialog::accept);
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myTextAutoGenerateAgentDialogGroupName), QSize(400, 300));
}

TextAutoGenerateAgentDialog::~TextAutoGenerateAgentDialog() = default;

void TextAutoGenerateAgentDialog::setAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent)
{
    mAgentWidget->setAgent(agent);
}

TextAutoGenerateText::TextAutoGenerateAgent TextAutoGenerateAgentDialog::agent() const
{
    return mAgentWidget->agent();
}

#include "moc_textautogenerateagentdialog.cpp"
