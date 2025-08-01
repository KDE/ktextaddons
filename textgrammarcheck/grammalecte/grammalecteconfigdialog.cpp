/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteconfigdialog.h"
using namespace Qt::Literals::StringLiterals;

#include "grammalecteconfigwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
static const char myConfigGrammalecteConfigDialog[] = "GrammalecteConfigDialog";
}
using namespace TextGrammarCheck;
GrammalecteConfigDialog::GrammalecteConfigDialog(QWidget *parent, bool disableMessageBox)
    : QDialog(parent)
    , mConfigWidget(new GrammalecteConfigWidget(this, disableMessageBox))
{
    setWindowTitle(i18nc("@title:window", "Configure Grammalecte"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);

    mConfigWidget->setObjectName(u"configwidget"_s);
    mainLayout->addWidget(mConfigWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(u"box"_s);
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &GrammalecteConfigDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &GrammalecteConfigDialog::reject);
    readConfig();
}

GrammalecteConfigDialog::~GrammalecteConfigDialog()
{
    writeConfig();
}

void GrammalecteConfigDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGrammalecteConfigDialog));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void GrammalecteConfigDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(500, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGrammalecteConfigDialog));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

#include "moc_grammalecteconfigdialog.cpp"
