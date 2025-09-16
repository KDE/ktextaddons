/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolswidget.h"
#include "core/tools/textautogeneratetexttoolpluginmanager.h"
#include "textautogeneratetextwidget_debug.h"
#include "widgets/common/textautogenerateflowlayout.h"
#include <KLocalizedString>
#include <QLabel>
#include <QToolButton>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateToolsWidget::TextAutoGenerateToolsWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new TextAutoGenerateFlowLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto label = new QLabel(i18n("Tools:"), this);
    label->setObjectName(u"label"_s);
    QFont f = label->font();
    f.setBold(true);
    label->setFont(f);
    mainLayout->setAlignment(label, Qt::AlignBottom);
    mainLayout->addWidget(label);

    const QList<TextAutoGenerateTextToolPluginManager::PluginToolInfo> lst = TextAutoGenerateTextToolPluginManager::self()->activePluginTools();
    for (const auto &info : lst) {
        auto b = new QToolButton(this);
        b->setToolTip(info.description);
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

void TextAutoGenerateToolsWidget::setActivatedTools(const QList<QByteArray> &lst)
{
    for (const auto &b : lst) {
        const auto it = std::find_if(mListButton.constBegin(), mListButton.constEnd(), [b](QToolButton *button) {
            return button->property("identifier").toByteArray() == b;
        });
        if (it != mListButton.cend()) {
            (*it)->setChecked(true);
        } else {
            qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Impossible to find button: " << b;
        }
    }
}

#include "moc_textautogeneratetoolswidget.cpp"
