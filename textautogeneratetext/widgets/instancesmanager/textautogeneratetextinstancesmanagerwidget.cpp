/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextinstancesmanagerwidget.h"
#include "core/models/textautogeneratetextinstancemodel.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "textautogenerateaddinstancedialog.h"
#include "textautogeneratetextinstancesmanagerlistview.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGenerateManager>
#include <TextAutoGenerateText/TextAutoGenerateTextPlugin>

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
    addInstanceButton->setToolTip(i18nc("@info:tooltip", "Add Instance…"));
    addInstanceButton->setAutoRaise(true);
    hboxLayout->addWidget(addInstanceButton);
    connect(addInstanceButton, &QToolButton::clicked, this, [this, manager]() {
        TextAutoGenerateAddInstanceDialog d(manager, this);
        if (d.exec()) {
            const TextAutoGenerateTextClient::SupportedServer server = d.selectedInstanceType();
            qDebug() << " selectedInstanceType:" << server;
            TextAutoGenerateTextInstance *instance = new TextAutoGenerateTextInstance;
            instance->setName(d.instanceName());
            instance->setPluginName(server.localizedName);
            instance->setPluginIdentifier(server.pluginName);
            // TODO generate unique add identifier
            mManager->textAutoGenerateTextInstancesManager()->addInstance(instance);
        }
    });

    connect(mInstancesManagerListView, &TextAutoGenerateTextInstancesManagerListView::removeInstance, this, [this](const QByteArray &uuid) {
        mManager->textAutoGenerateTextInstancesManager()->textAutoGenerateTextInstanceModel()->removeInstance(uuid);
    });
    connect(mInstancesManagerListView, &TextAutoGenerateTextInstancesManagerListView::editInstance, this, [this](const QByteArray &uuid) {
        auto plugin = mManager->textAutoGenerateTextInstancesManager()->textAutoGenerateTextInstanceModel()->editInstance(uuid);
        if (plugin) {
            plugin->showConfigureDialog(this);
        }
    });
    mInstancesManagerListView->setObjectName(QStringLiteral("mInstancesManagerListView"));
    mainLayout->addWidget(mInstancesManagerListView);
}

TextAutoGenerateTextInstancesManagerWidget::~TextAutoGenerateTextInstancesManagerWidget() = default;

void TextAutoGenerateTextInstancesManagerWidget::save()
{
    mManager->textAutoGenerateTextInstancesManager()->saveInstances();
}

#include "moc_textautogeneratetextinstancesmanagerwidget.cpp"
