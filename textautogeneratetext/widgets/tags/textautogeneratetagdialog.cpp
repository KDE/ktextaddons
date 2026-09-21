/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetagdialog.h"
#include "textautogeneratetagwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
namespace
{
const char myTextAutoGenerateTagDialogGroupName[] = "TextAutoGenerateTagDialog";
}
TextAutoGenerateTagDialog::TextAutoGenerateTagDialog(QWidget *parent)
    : QDialog(parent)
    , mTagWidget(new TextAutoGenerateTagWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Tag"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mTagWidget->setObjectName(u"mTagWidget"_s);
    mainLayout->addWidget(mTagWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateTagDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateTagDialog::accept);

    mOkButton = button->button(QDialogButtonBox::Ok);
    mOkButton->setObjectName(u"mOkButton"_s);
    mOkButton->setDefault(true);
    mOkButton->setEnabled(false);
    connect(mTagWidget, &TextAutoGenerateTagWidget::enableOkButton, mOkButton, &QPushButton::setEnabled);

    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myTextAutoGenerateTagDialogGroupName), QSize(400, 150));
}

TextAutoGenerateTagDialog::~TextAutoGenerateTagDialog() = default;

void TextAutoGenerateTagDialog::setTag(const TextAutoGenerateText::TextAutoGenerateTag &tag)
{
    setWindowTitle(i18nc("@title:window", "Modify Tag"));
    mTagWidget->setTag(tag);
}

TextAutoGenerateText::TextAutoGenerateTag TextAutoGenerateTagDialog::tag() const
{
    return mTagWidget->tag();
}

#include "moc_textautogeneratetagdialog.cpp"
