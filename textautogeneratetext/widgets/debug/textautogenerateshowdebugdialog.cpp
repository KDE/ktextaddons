/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateshowdebugdialog.h"
#include "textautogenerateshowdebugwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
namespace
{
const char myTextAutoGenerateShowDebugDialogGroupName[] = "TextAutoGenerateShowDebugDialog";
}
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateShowDebugDialog::TextAutoGenerateShowDebugDialog(QWidget *parent)
    : QDialog(parent)
    , mShowDebugWidget(new TextAutoGenerateShowDebugWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Debug"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mShowDebugWidget->setObjectName(u"mShowDebugWidget"_s);
    mainLayout->addWidget(mShowDebugWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateShowDebugDialog::reject);
    readConfig();
}

TextAutoGenerateShowDebugDialog::~TextAutoGenerateShowDebugDialog()
{
    writeConfig();
}

void TextAutoGenerateShowDebugDialog::setPlainText(const QString &text)
{
    mShowDebugWidget->setPlainText(text);
}

void TextAutoGenerateShowDebugDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myTextAutoGenerateShowDebugDialogGroupName), 400, 300);
}

void TextAutoGenerateShowDebugDialog::writeConfig()
{
    TextAddonsWidgets::LoadDialogSizeUtils::saveDialogSize(this, QLatin1StringView(myTextAutoGenerateShowDebugDialogGroupName));
}

#include "moc_textautogenerateshowdebugdialog.cpp"
