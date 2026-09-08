/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateshowmodelinfodialog.h"
#include "widgets/common/textautogenerateshowmodelinfowidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
namespace
{
const char myTextAutoGenerateShowModelInfoDialogGroupName[] = "TextAutoGenerateShowModelInfoDialog";
}

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateShowModelInfoDialog::TextAutoGenerateShowModelInfoDialog(QWidget *parent)
    : QDialog(parent)
    , mTextAutoGenerateShowModelInfoWidget(new TextAutoGenerateShowModelInfoWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Show Model Information"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mTextAutoGenerateShowModelInfoWidget->setObjectName(u"mTextAutoGenerateShowModelInfoWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateShowModelInfoWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateShowModelInfoDialog::reject);

    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myTextAutoGenerateShowModelInfoDialogGroupName), QSize(400, 300));
}

TextAutoGenerateShowModelInfoDialog::~TextAutoGenerateShowModelInfoDialog() = default;

void TextAutoGenerateShowModelInfoDialog::setText(const QString &text)
{
    mTextAutoGenerateShowModelInfoWidget->setText(text);
}

#include "moc_textautogenerateshowmodelinfodialog.cpp"
