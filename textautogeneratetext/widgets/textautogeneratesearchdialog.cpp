/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchdialog.h"

#include "textautogeneratesearchwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>

namespace
{
const char myTextAutoGenerateSearchDialogGroupName[] = "TextAutoGenerateSearchDialog";
}
using namespace Qt::Literals::StringLiterals;
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
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myTextAutoGenerateSearchDialogGroupName), 400, 300);
}

void TextAutoGenerateSearchDialog::writeConfig()
{
    TextAddonsWidgets::LoadDialogSizeUtils::saveDialogSize(this, QLatin1StringView(myTextAutoGenerateSearchDialogGroupName));
}

#include "moc_textautogeneratesearchdialog.cpp"
