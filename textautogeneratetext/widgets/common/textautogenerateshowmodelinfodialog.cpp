/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateshowmodelinfodialog.h"
#include "widgets/common/textautogenerateshowmodelinfowidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
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
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mTextAutoGenerateShowModelInfoWidget->setObjectName(u"mTextAutoGenerateShowModelInfoWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateShowModelInfoWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateShowModelInfoDialog::reject);

    readConfig();
}

TextAutoGenerateShowModelInfoDialog::~TextAutoGenerateShowModelInfoDialog()
{
    writeConfig();
}

void TextAutoGenerateShowModelInfoDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateShowModelInfoDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAutoGenerateShowModelInfoDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateShowModelInfoDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_textautogenerateshowmodelinfodialog.cpp"
