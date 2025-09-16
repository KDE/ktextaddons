/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetoolpluginconfigurewidget.h"
#include "textautogeneratetoolpluginshowmetadatadialog.h"
#include <KLocalizedString>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPlugin>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateToolPluginConfigureWidget::TextAutoGenerateToolPluginConfigureWidget(TextAutoGenerateTextToolPlugin *plugin, QWidget *parent)
    : QWidget{parent}
    , mDescriptionLabel(new QLabel(this))
    , mArgumentsLabel(new QLabel(this))
    , mInfoToolButton(new QToolButton(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mainLayout->addWidget(createLabel(i18nc("@label:textbox", "Description:")));

    mDescriptionLabel->setObjectName("mDescriptionLabel"_L1);
    mainLayout->addWidget(mDescriptionLabel);

    mainLayout->addWidget(createLabel(i18nc("@label:textbox", "Arguments:")));

    mArgumentsLabel->setObjectName("mArgumentsLabel"_L1);
    mArgumentsLabel->setTextFormat(Qt::RichText);
    mainLayout->addWidget(mArgumentsLabel);

    mainLayout->addWidget(mInfoToolButton);
    mInfoToolButton->setObjectName("mInfoToolButton"_L1);
    mInfoToolButton->setIcon(QIcon::fromTheme(u"info"_s));
    mInfoToolButton->setFocusPolicy(Qt::NoFocus);
    mInfoToolButton->setToolTip(i18nc("@info:tooltip", "Show metadata info"));
    connect(mInfoToolButton, &QToolButton::clicked, this, [this, plugin]() {
        TextAutoGenerateToolPluginShowMetaDataDialog d(this);
        if (plugin) {
            d.setMetaData(plugin->metadata());
        }
        d.exec();
    });

    if (plugin) {
        mDescriptionLabel->setText(plugin->description());
        generateArguments(plugin);
    }
}

TextAutoGenerateToolPluginConfigureWidget::~TextAutoGenerateToolPluginConfigureWidget() = default;

QLabel *TextAutoGenerateToolPluginConfigureWidget::createLabel(const QString &str)
{
    auto label = new QLabel(str, this);
    QFont f = label->font();
    f.setBold(true);
    label->setFont(f);
    return label;
}

void TextAutoGenerateToolPluginConfigureWidget::generateArguments(TextAutoGenerateTextToolPlugin *plugin)
{
    QString propertiesText;
    for (const auto &prop : plugin->properties()) {
        if (!propertiesText.isEmpty()) {
            propertiesText += u"<br/>"_s;
        }
        propertiesText += u"<b>%1:</b> %2"_s.arg(prop.name(), prop.description().toString());
    }
    mArgumentsLabel->setText(propertiesText);
}

#include "moc_textautogeneratetoolpluginconfigurewidget.cpp"
