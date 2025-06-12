/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextinstancesmanagerwidget.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "textautogenerateaddinstancedialog.h"
#include "textautogeneratetextinstancesmanagerlistview.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QLineEdit>
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGenerateManager>
#include <qtoolbutton.h>

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManagerWidget::TextAutoGenerateTextInstancesManagerWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mInstancesManagerListView(new TextAutoGenerateTextInstancesManagerListView(manager, this))
    , mSearchLineEdit(new QLineEdit(this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});
    mainLayout->setSpacing(0);

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setContentsMargins({});
    hboxLayout->setObjectName(QStringLiteral("hboxLayout"));

    mainLayout->addLayout(hboxLayout);

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    hboxLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search…"));
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    connect(mSearchLineEdit, &QLineEdit::textChanged, mInstancesManagerListView, &TextAutoGenerateTextInstancesManagerListView::slotSearchChanged);

    auto addInstanceButton = new QToolButton(this);
    addInstanceButton->setObjectName(QStringLiteral("addInstanceButton"));
    addInstanceButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    addInstanceButton->setAutoRaise(true);
    hboxLayout->addWidget(addInstanceButton);
    connect(addInstanceButton, &QToolButton::clicked, this, [this, manager]() {
        TextAutoGenerateAddInstanceDialog d(manager, this);
        if (d.exec()) {
            const TextAutoGenerateTextClient::SupportedServer server = d.selectedInstanceType();
            qDebug() << " selectedInstanceType:" << server;
            TextAutoGenerateTextInstance instance;
            instance.setName(d.instanceName());
            instance.setPluginName(server.localizedName);
            instance.setPluginIdentifier(server.pluginName);
            mManager->textAutoGenerateTextInstancesManager()->addInstance(instance);
        }
    });

    mInstancesManagerListView->setObjectName(QStringLiteral("mInstancesManagerListView"));
    mainLayout->addWidget(mInstancesManagerListView);
}

TextAutoGenerateTextInstancesManagerWidget::~TextAutoGenerateTextInstancesManagerWidget() = default;

#include "moc_textautogeneratetextinstancesmanagerwidget.cpp"
