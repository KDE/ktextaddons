/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskdialog.h"

#include "textautogeneratequickaskwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
namespace
{
const char myQuickAskDialogGroupName[] = "QuickAskDialog";
}

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateQuickAskDialog::TextAutoGenerateQuickAskDialog(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QDialog(parent)
    , mTextAutoGenerateQuickAskWidget(new TextAutoGenerateQuickAskWidget(manager, this))
    , mManager(manager)
{
    setWindowTitle(i18nc("@title:window", "Quick Ask"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mTextAutoGenerateQuickAskWidget->setObjectName(u"mTextAutoGenerateQuickAskWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateQuickAskWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateQuickAskDialog::reject);
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myQuickAskDialogGroupName), QSize(400, 300));
}

TextAutoGenerateQuickAskDialog::~TextAutoGenerateQuickAskDialog() = default;

void TextAutoGenerateQuickAskDialog::ask(const TextAutoGenerateText::TextAutoGenerateManager::AskMessageInfo &info)
{
    if (mManager) {
        mManager->ask(info);
    }
}

#include "moc_textautogeneratequickaskdialog.cpp"
