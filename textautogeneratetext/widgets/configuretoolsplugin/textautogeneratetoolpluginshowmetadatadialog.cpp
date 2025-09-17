/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetoolpluginshowmetadatadialog.h"
#include "widgets/configuretoolsplugin/textautogeneratetoolpluginshowmetadatawidget.h"
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
TextAutoGenerateToolPluginShowMetaDataDialog::TextAutoGenerateToolPluginShowMetaDataDialog(QWidget *parent)
    : QDialog(parent)
    , mTextAutoGenerateToolPluginShowMetaDataWidget(new TextAutoGenerateToolPluginShowMetaDataWidget(this))
{
    setWindowTitle(i18n("Metadata Info"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mTextAutoGenerateToolPluginShowMetaDataWidget->setObjectName(u"mTextAutoGenerateToolPluginShowMetaDataWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateToolPluginShowMetaDataWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateToolPluginShowMetaDataDialog::reject);
    readConfig();
}

TextAutoGenerateToolPluginShowMetaDataDialog::~TextAutoGenerateToolPluginShowMetaDataDialog()
{
    writeConfig();
}

void TextAutoGenerateToolPluginShowMetaDataDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateToolPluginShowMetaDataDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAutoGenerateToolPluginShowMetaDataDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateToolPluginShowMetaDataDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void TextAutoGenerateToolPluginShowMetaDataDialog::setMetaData(const QJsonObject &obj)
{
    mTextAutoGenerateToolPluginShowMetaDataWidget->setMetaData(obj);
}

#include "moc_textautogeneratetoolpluginshowmetadatadialog.cpp"
