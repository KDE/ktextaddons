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
namespace
{
constexpr const char *button_property("identifier");
}
TextAutoGenerateToolsWidget::TextAutoGenerateToolsWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new TextAutoGenerateFlowLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto label = new QLabel(i18nc("@label:textbox", "Tools:"), this);
    label->setObjectName(u"label"_s);
    QFont f = label->font();
    f.setBold(true);
    label->setFont(f);
    mainLayout->setAlignment(label, Qt::AlignBottom);
    mainLayout->addWidget(label);
    mainLayout->setHorizontalSpacing(0);

    const QList<TextAutoGenerateTextToolPluginManager::PluginToolInfo> lst = TextAutoGenerateTextToolPluginManager::self()->activePluginTools();
    mListButton.reserve(lst.count());
    for (const auto &info : lst) {
        auto b = new QToolButton(this);
        b->setToolTip(info.description);
        b->setText(info.displayName);
        b->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        b->setAutoRaise(true);
        if (!info.iconName.isEmpty()) {
            b->setIcon(QIcon::fromTheme(info.iconName));
        }
        b->setProperty(button_property, info.identifier);
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
            activeTools.append(b->property(button_property).toByteArray());
        }
    }
    return activeTools;
}

void TextAutoGenerateToolsWidget::disableTools()
{
    for (const auto &b : std::as_const(mListButton)) {
        b->setChecked(false);
    }
}

void TextAutoGenerateToolsWidget::setActivatedTools(const QList<QByteArray> &lst)
{
    disableTools();
    bool foundTools = false;
    for (const auto &b : lst) {
        const auto it = std::find_if(mListButton.constBegin(), mListButton.constEnd(), [b](QToolButton *button) {
            return button->property(button_property).toByteArray() == b;
        });
        if (it != mListButton.cend()) {
            (*it)->setChecked(true);
            foundTools = true;
        } else {
            qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Impossible to find button: " << b;
        }
    }
    if (foundTools) {
        setVisible(true);
    }
}

#include "moc_textautogeneratetoolswidget.cpp"
