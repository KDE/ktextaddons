/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolpluginshowmetadatawidget.h"
#include <QJsonDocument>
#include <QTextEdit>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateToolPluginShowMetaDataWidget::TextAutoGenerateToolPluginShowMetaDataWidget(QWidget *parent)
    : QWidget{parent}
    , mTextEdit(new QTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mTextEdit->setObjectName(u"mTextEdit"_s);
    mainLayout->addWidget(mTextEdit);
    mTextEdit->setReadOnly(true);
}

TextAutoGenerateToolPluginShowMetaDataWidget::~TextAutoGenerateToolPluginShowMetaDataWidget() = default;

void TextAutoGenerateToolPluginShowMetaDataWidget::setMetaData(const QJsonObject &obj)
{
    const QJsonDocument doc(obj);
    const QByteArray ba = doc.toJson();
    mTextEdit->setPlainText(QString::fromLatin1(ba));
}

#include "moc_textautogeneratetoolpluginshowmetadatawidget.cpp"
