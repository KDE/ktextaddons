/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateprojectdialog.h"
#include "textautogenerateprojectwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
namespace
{
const char myTextAutoGenerateProjectDialogGroupName[] = "TextAutoGenerateProjectDialog";
}
TextAutoGenerateProjectDialog::TextAutoGenerateProjectDialog(QWidget *parent)
    : QDialog(parent)
    , mProjectWidget(new TextAutoGenerateProjectWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Project"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mProjectWidget->setObjectName(u"mProjectWidget"_s);
    mainLayout->addWidget(mProjectWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateProjectDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateProjectDialog::accept);

    mOkButton = button->button(QDialogButtonBox::Ok);
    mOkButton->setObjectName(u"mOkButton"_s);
    mOkButton->setDefault(true);
    mOkButton->setEnabled(false);
    connect(mProjectWidget, &TextAutoGenerateProjectWidget::enableOkButton, mOkButton, &QPushButton::setEnabled);

    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myTextAutoGenerateProjectDialogGroupName), QSize(400, 150));
}

TextAutoGenerateProjectDialog::~TextAutoGenerateProjectDialog() = default;

void TextAutoGenerateProjectDialog::setProject(const TextAutoGenerateText::TextAutoGenerateProject &project)
{
    setWindowTitle(i18nc("@title:window", "Modify Project"));
    mProjectWidget->setProject(project);
}

TextAutoGenerateText::TextAutoGenerateProject TextAutoGenerateProjectDialog::project() const
{
    return mProjectWidget->project();
}

#include "moc_textautogenerateprojectdialog.cpp"
