/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolconfigdialog.h"

#include "languagetoolconfigwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
namespace
{
const char myConfigGroupName[] = "LanguageToolConfigDialog";
}
using namespace Qt::Literals::StringLiterals;
using namespace TextGrammarCheck;
LanguageToolConfigDialog::LanguageToolConfigDialog(QWidget *parent)
    : QDialog(parent)
    , mConfigWidget(new LanguageToolConfigWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure LanguageTool"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);

    mConfigWidget->setObjectName(u"configwidget"_s);
    mainLayout->addWidget(mConfigWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Reset, this);
    box->setObjectName(u"box"_s);
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &LanguageToolConfigDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &LanguageToolConfigDialog::reject);
    connect(box->button(QDialogButtonBox::Reset), &QPushButton::clicked, mConfigWidget, &LanguageToolConfigWidget::resetValue);
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myConfigGroupName), QSize(500, 300));
}

LanguageToolConfigDialog::~LanguageToolConfigDialog() = default;

#include "moc_languagetoolconfigdialog.cpp"
