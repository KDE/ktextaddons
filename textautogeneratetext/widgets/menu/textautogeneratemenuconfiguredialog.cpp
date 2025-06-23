/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratemenuconfiguredialog.h"
using namespace Qt::Literals::StringLiterals;

#include "textautogeneratemenuconfigurewidget.h"
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
const char myTextAutoGenerateMenuConfigureDialogGroupName[] = "TextAutoGenerateMenuConfigureDialog";
}
using namespace TextAutoGenerateText;
TextAutoGenerateMenuConfigureDialog::TextAutoGenerateMenuConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mTextMenuConfigureWidget(new TextAutoGenerateMenuConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure AI text plugins"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);

    mTextMenuConfigureWidget->setObjectName(u"mTextMenuConfigureWidget"_s);
    mainLayout->addWidget(mTextMenuConfigureWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(u"box"_s);
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &TextAutoGenerateMenuConfigureDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &TextAutoGenerateMenuConfigureDialog::reject);
    readConfig();
}

TextAutoGenerateMenuConfigureDialog::~TextAutoGenerateMenuConfigureDialog()
{
    writeConfig();
}

void TextAutoGenerateMenuConfigureDialog::setTextInfos(const QList<TextAutoGenerateMenuTextInfo> &infos)
{
    mTextMenuConfigureWidget->setTextInfos(infos);
}

QList<TextAutoGenerateMenuTextInfo> TextAutoGenerateMenuConfigureDialog::textInfos() const
{
    return mTextMenuConfigureWidget->textInfos();
}

void TextAutoGenerateMenuConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateMenuConfigureDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAutoGenerateMenuConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateMenuConfigureDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_textautogeneratemenuconfiguredialog.cpp"
