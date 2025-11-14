/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateshowdebugdialog.h"
#include "textautogenerateshowdebugwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
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
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateShowDebugDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAutoGenerateShowDebugDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateShowDebugDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_textautogenerateshowdebugdialog.cpp"
