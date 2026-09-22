/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemanageprojectsdialog.h"
#include "textautogeneratemanageprojectswidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
namespace
{
const char myTextAutoGenerateManageProjectsDialogGroupName[] = "TextAutoGenerateManageProjectsDialog";
}
TextAutoGenerateManageProjectsDialog::TextAutoGenerateManageProjectsDialog(QWidget *parent)
    : QDialog(parent)
    , mManageProjectsWidget(new TextAutoGenerateManageProjectsWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Manage Projects"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mManageProjectsWidget->setObjectName(u"mManageProjectsWidget"_s);
    mainLayout->addWidget(mManageProjectsWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateManageProjectsDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateManageProjectsDialog::accept);

    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myTextAutoGenerateManageProjectsDialogGroupName), QSize(400, 300));
}

TextAutoGenerateManageProjectsDialog::~TextAutoGenerateManageProjectsDialog() = default;

void TextAutoGenerateManageProjectsDialog::setProjects(const QList<TextAutoGenerateText::TextAutoGenerateProject> &projects)
{
    mManageProjectsWidget->setProjects(projects);
}

QList<TextAutoGenerateText::TextAutoGenerateProject> TextAutoGenerateManageProjectsDialog::projects() const
{
    return mManageProjectsWidget->projects();
}

#include "moc_textautogeneratemanageprojectsdialog.cpp"
