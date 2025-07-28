/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextinstancesmanagerwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "core/models/textautogeneratetextinstancemodel.h"
#include "core/textautogenerateengineloader.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "textautogenerateaddinstancedialog.h"
#include "textautogeneratetextinstancesmanagerlistview.h"
#include "textautogeneratetextwidget_debug.h"
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
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});
    mainLayout->setSpacing(0);

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setContentsMargins({});
    hboxLayout->setObjectName(u"hboxLayout"_s);

    mainLayout->addLayout(hboxLayout);

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    hboxLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search…"));
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    connect(mSearchLineEdit, &QLineEdit::textChanged, mInstancesManagerListView, &TextAutoGenerateTextInstancesManagerListView::slotSearchChanged);

    auto addInstanceButton = new QToolButton(this);
    addInstanceButton->setObjectName(u"addInstanceButton"_s);
    addInstanceButton->setIcon(QIcon::fromTheme(u"list-add"_s));
    addInstanceButton->setToolTip(i18nc("@info:tooltip", "Add Instance…"));
    addInstanceButton->setAutoRaise(true);
    hboxLayout->addWidget(addInstanceButton);
    connect(addInstanceButton, &QToolButton::clicked, this, &TextAutoGenerateTextInstancesManagerWidget::slotAddInstance);

    connect(mInstancesManagerListView,
            &TextAutoGenerateTextInstancesManagerListView::addInstance,
            this,
            &TextAutoGenerateTextInstancesManagerWidget::slotAddInstance);
    connect(mInstancesManagerListView, &TextAutoGenerateTextInstancesManagerListView::removeInstance, this, [this](const QByteArray &uuid) {
        if (auto plugin = mManager->textAutoGenerateTextInstancesManager()->textAutoGenerateTextInstanceModel()->removeInstance(uuid); plugin) {
            plugin->remove();
        }
    });
    connect(mInstancesManagerListView, &TextAutoGenerateTextInstancesManagerListView::editInstance, this, [this](const QByteArray &uuid) {
        auto plugin = mManager->textAutoGenerateTextInstancesManager()->textAutoGenerateTextInstanceModel()->editInstance(uuid);
        Q_ASSERT(plugin);
        plugin->showConfigureDialog(this);
    });
    connect(mInstancesManagerListView, &TextAutoGenerateTextInstancesManagerListView::markAsDefaultChanged, this, [this](const QByteArray &uuid) {
        mManager->textAutoGenerateTextInstancesManager()->textAutoGenerateTextInstanceModel()->setCurrentInstance(uuid);
    });
    mInstancesManagerListView->setObjectName(u"mInstancesManagerListView"_s);
    mainLayout->addWidget(mInstancesManagerListView);
}

TextAutoGenerateTextInstancesManagerWidget::~TextAutoGenerateTextInstancesManagerWidget() = default;

void TextAutoGenerateTextInstancesManagerWidget::save()
{
    mManager->textAutoGenerateTextInstancesManager()->saveInstances();
}

void TextAutoGenerateTextInstancesManagerWidget::slotAddInstance()
{
    TextAutoGenerateAddInstanceDialog d(mManager, this);
    if (d.exec()) {
        const TextAutoGenerateTextClient::SupportedServer server = d.selectedInstanceType();
        // qDebug() << " selectedInstanceType:" << server;
        auto instance = new TextAutoGenerateTextInstance;
        instance->setPluginName(server.pluginName);
        instance->setPluginIdentifier(server.identifier);
        instance->setInstanceUuid(QUuid::createUuid().toByteArray(QUuid::Id128));
        instance->setEnabled(true);
        auto client = mManager->textAutoGenerateTextInstancesManager()->textAutoGenerateEngineLoader()->searchTextAutoGenerateTextClient(server.pluginName);
        if (!client) {
            qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << " Impossible to create client " << server.pluginName;
        } else {
            auto plugin = client->createTextAutoGeneratePlugin(mManager, instance);
            plugin->setDisplayName(d.instanceName());
            instance->setPlugin(plugin);
            mManager->textAutoGenerateTextInstancesManager()->addInstance(instance);
        }
    }
}
#include "moc_textautogeneratetextinstancesmanagerwidget.cpp"
