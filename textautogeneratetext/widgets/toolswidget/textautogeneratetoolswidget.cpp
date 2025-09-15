/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolswidget.h"
#include "core/tools/textautogeneratetexttoolpluginmanager.h"
#include "widgets/common/textautogenerateflowlayout.h"
#include <QToolButton>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateToolsWidget::TextAutoGenerateToolsWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new TextAutoGenerateFlowLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    const QList<TextAutoGenerateTextToolPluginManager::PluginToolInfo> lst = TextAutoGenerateTextToolPluginManager::self()->activePluginTools();
    for (const auto &info : lst) {
        auto b = new QToolButton(this);
        b->setText(info.displayName);
        b->setAutoRaise(true);
        b->setProperty("identifier", info.identifier);
        b->setCheckable(true);
        mainLayout->addWidget(b);
        mListButton.append(b);
    }
}

TextAutoGenerateToolsWidget::~TextAutoGenerateToolsWidget() = default;

QList<QByteArray> TextAutoGenerateToolsWidget::generateListOfActiveTools() const
{
    QList<QByteArray> activeTools;
    for (const auto b : std::as_const(mListButton)) {
        if (b->isChecked()) {
            activeTools.append(b->property("identifier").toByteArray());
        }
    }
    return activeTools;
}

#include "moc_textautogeneratetoolswidget.cpp"
