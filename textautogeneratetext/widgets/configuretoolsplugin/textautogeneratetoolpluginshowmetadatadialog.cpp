/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetoolpluginshowmetadatadialog.h"
#include "widgets/configuretoolsplugin/textautogeneratetoolpluginshowmetadatawidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <qdialogbuttonbox.h>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
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
}

TextAutoGenerateToolPluginShowMetaDataDialog::~TextAutoGenerateToolPluginShowMetaDataDialog() = default;

void TextAutoGenerateToolPluginShowMetaDataDialog::setMetaData(const QJsonObject &obj)
{
    mTextAutoGenerateToolPluginShowMetaDataWidget->setMetaData(obj);
}

#include "moc_textautogeneratetoolpluginshowmetadatadialog.cpp"
