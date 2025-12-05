/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolpluginshowmetadatawidget.h"
#include "textautogeneratetextwidget_debug.h"
#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/SyntaxHighlighter>
#include <KSyntaxHighlighting/Theme>
#include <QJsonDocument>
#include <QJsonObject>
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

    const KSyntaxHighlighting::Definition def = mRepo.definitionForName(u"Json"_s);
    if (!def.isValid()) {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Invalid definition name";
    }

    auto hl = new KSyntaxHighlighting::SyntaxHighlighter(mTextEdit->document());
    hl->setTheme((palette().color(QPalette::Base).lightness() < 128) ? mRepo.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                                                                     : mRepo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
    hl->setDefinition(def);
}

TextAutoGenerateToolPluginShowMetaDataWidget::~TextAutoGenerateToolPluginShowMetaDataWidget() = default;

void TextAutoGenerateToolPluginShowMetaDataWidget::setMetaData(const QJsonObject &obj)
{
    const QJsonDocument doc(obj);
    const QByteArray ba = doc.toJson();
    mTextEdit->setPlainText(QString::fromUtf8(ba));
}

#include "moc_textautogeneratetoolpluginshowmetadatawidget.cpp"
