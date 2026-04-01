/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetoolshowmetadatadialog.h"
#include "textautogeneratetoolshowmetadatawidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
namespace
{
const char myTextAutoGenerateToolPluginShowMetaDataDialogGroupName[] = "TextAutoGenerateToolPluginShowMetaDataDialog";
}
TextAutoGenerateToolShowMetaDataDialog::TextAutoGenerateToolShowMetaDataDialog(QWidget *parent)
    : QDialog(parent)
    , mTextAutoGenerateToolPluginShowMetaDataWidget(new TextAutoGenerateToolShowMetaDataWidget(this))
{
    setWindowTitle(i18n("Metadata Info"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mTextAutoGenerateToolPluginShowMetaDataWidget->setObjectName(u"mTextAutoGenerateToolPluginShowMetaDataWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateToolPluginShowMetaDataWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateToolShowMetaDataDialog::reject);
    readConfig();
}

TextAutoGenerateToolShowMetaDataDialog::~TextAutoGenerateToolShowMetaDataDialog()
{
    writeConfig();
}

void TextAutoGenerateToolShowMetaDataDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateToolPluginShowMetaDataDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAutoGenerateToolShowMetaDataDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateToolPluginShowMetaDataDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void TextAutoGenerateToolShowMetaDataDialog::setMetaData(const QJsonObject &obj)
{
    mTextAutoGenerateToolPluginShowMetaDataWidget->setMetaData(obj);
}

#include "moc_textautogeneratetoolshowmetadatadialog.cpp"
