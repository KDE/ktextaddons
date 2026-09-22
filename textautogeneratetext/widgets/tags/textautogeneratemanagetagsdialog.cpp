/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemanagetagsdialog.h"
#include "textautogeneratemanagetagswidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
namespace
{
const char myTextAutoGenerateManageTagsDialogGroupName[] = "TextAutoGenerateManageTagsDialog";
}
TextAutoGenerateManageTagsDialog::TextAutoGenerateManageTagsDialog(QWidget *parent)
    : QDialog(parent)
    , mManageTagsWidget(new TextAutoGenerateManageTagsWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Manage Tags"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mManageTagsWidget->setObjectName(u"mManageTagsWidget"_s);
    mainLayout->addWidget(mManageTagsWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateManageTagsDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateManageTagsDialog::accept);

    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myTextAutoGenerateManageTagsDialogGroupName), QSize(400, 300));
}

TextAutoGenerateManageTagsDialog::~TextAutoGenerateManageTagsDialog() = default;

void TextAutoGenerateManageTagsDialog::setTags(const QList<TextAutoGenerateText::TextAutoGenerateTag> &tags)
{
    mManageTagsWidget->setTags(tags);
}

QList<TextAutoGenerateText::TextAutoGenerateTag> TextAutoGenerateManageTagsDialog::tags() const
{
    return mManageTagsWidget->tags();
}

#include "moc_textautogeneratemanagetagsdialog.cpp"
