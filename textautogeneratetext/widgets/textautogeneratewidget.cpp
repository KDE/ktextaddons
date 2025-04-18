/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratewidget.h"
#include "core/textautogeneratechatmodel.h"
#include "core/textautogenerateengineloader.h"
#include "core/textautogenerateengineutil.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratemessage.h"
#include "core/textautogeneratetextclient.h"
#include "core/textautogeneratetextplugin.h"
#include "textautogeneratetextwidget_debug.h"
#include "widgets/textautogenerateheaderwidget.h"
#include "widgets/textautogeneratehistorywidget.h"
#include "widgets/textautogenerateresultwidget.h"
#include "widgets/textautogeneratetextlineeditwidget.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <KSplitterCollapserButton>
#include <QSplitter>
#include <QVBoxLayout>

using namespace TextAutogenerateText;
TextAutogenerateWidget::TextAutogenerateWidget(QWidget *parent)
    : QWidget{parent}
    , mTextAutogenerateResultWidget(new TextAutogenerateResultWidget(this))
    , mTextAutogenerateTextLineEditWidget(new TextAutogenerateTextLineEditWidget(this))
    , mSplitter(new QSplitter(this))
    , mHistoryWidget(new TextAutogenerateHistoryWidget(this))
    , mHeaderWidget(new TextAutogenerateHeaderWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});
    mHeaderWidget->setObjectName(QStringLiteral("mHeaderWidget"));
    mainLayout->addWidget(mHeaderWidget);

    mSplitter->setOrientation(Qt::Horizontal);
    mSplitter->setObjectName(QStringLiteral("mSplitter"));

    mainLayout->addWidget(mSplitter, 1);

    mTextAutogenerateResultWidget->setObjectName(QStringLiteral("mTextAutogenerateResultWidget"));

    mHistoryWidget->setObjectName(QStringLiteral("mHistoryWidget"));
    mSplitter->addWidget(mHistoryWidget);
    mSplitter->addWidget(mTextAutogenerateResultWidget);

    new KSplitterCollapserButton(mHistoryWidget, mSplitter);

    mTextAutogenerateTextLineEditWidget->setObjectName(QStringLiteral("mTextAutogenerateTextLineEditWidget"));
    mainLayout->addWidget(mTextAutogenerateTextLineEditWidget);
    connect(mTextAutogenerateTextLineEditWidget, &TextAutogenerateTextLineEditWidget::editingFinished, this, &TextAutogenerateWidget::slotEditingFinished);

    connect(mHeaderWidget, &TextAutogenerateHeaderWidget::configChanged, this, &TextAutogenerateWidget::slotConfigureChanged);
    connect(mHeaderWidget, &TextAutogenerateHeaderWidget::clearModel, this, &TextAutogenerateWidget::slotClearModel);
    loadEngine();
    readConfig();
}

TextAutogenerateWidget::~TextAutogenerateWidget()
{
    if (mTextAutogeneratePlugin) {
        mTextAutogeneratePlugin->stop();
        mTextAutogeneratePlugin->deleteLater();
    }
    writeConfig();
}

void TextAutogenerateWidget::slotClearModel()
{
    TextAutogenerateManager::self()->textAutoGenerateChatModel()->resetConversation();
}

void TextAutogenerateWidget::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QStringLiteral("TextAutogenerateWidget"));
    group.writeEntry("mainSplitter", mSplitter->sizes());
}

void TextAutogenerateWidget::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QStringLiteral("TextAutogenerateWidget"));
    const QList<int> size = {100, 400};

    mSplitter->setSizes(group.readEntry("mainSplitter", size));
}

QString TextAutogenerateWidget::textLineEdit() const
{
    return mTextAutogenerateTextLineEditWidget->text();
}

void TextAutogenerateWidget::loadEngine()
{
    if (mTextAutogeneratePlugin) {
        disconnect(mTextAutogeneratePlugin);
        delete mTextAutogeneratePlugin;
        mTextAutogeneratePlugin = nullptr;
    }
    // TODO connect(TextAutogenerateText::TextAutogenerateEngineLoader::self(), &TextAutogenerateText::TextAutogenerateEngineLoader::noPluginsFound, this, &)
    TextAutogenerateText::TextAutogenerateEngineLoader::self()->loadPlugins();

    mTextAutogenerateClient =
        TextAutogenerateText::TextAutogenerateEngineLoader::self()->createTextAutoGenerateTextClient(TextAutogenerateEngineUtil::loadEngine());
    if (!mTextAutogenerateClient) {
        const QString fallBackEngineName = TextAutogenerateText::TextAutogenerateEngineLoader::self()->fallbackFirstEngine();
        if (!fallBackEngineName.isEmpty()) {
            mTextAutogenerateClient = TextAutogenerateText::TextAutogenerateEngineLoader::self()->createTextAutoGenerateTextClient(fallBackEngineName);
        }
    }
    if (mTextAutogenerateClient) {
        mHeaderWidget->updateEngineName(TextAutogenerateText::TextAutogenerateEngineLoader::self()->generateDisplayName(mTextAutogenerateClient));
        mTextAutogeneratePlugin = mTextAutogenerateClient->createTextAutogeneratePlugin();
        connect(mTextAutogeneratePlugin, &TextAutogenerateText::TextAutogenerateTextPlugin::finished, this, &TextAutogenerateWidget::slotAutogenerateFinished);
        connect(mTextAutogeneratePlugin,
                &TextAutogenerateText::TextAutogenerateTextPlugin::errorOccurred,
                this,
                &TextAutogenerateWidget::slotAutogenerateFailed);
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Impossible to create client" << TextAutogenerateEngineUtil::loadEngine();
    }
}

void TextAutogenerateWidget::slotConfigureChanged()
{
    loadEngine();
}

void TextAutogenerateWidget::slotEditingFinished(const QString &str)
{
    mTextAutogeneratePlugin->sendMessage(str);
}

void TextAutogenerateWidget::slotAutogenerateFinished(const TextAutoGenerateMessage &msg)
{
    qDebug() << " TextAutogenerateWidget::slotAutogenerateFinished " << msg;
    // mTextAutogenerateResultWidget->addMessage(msg);
}

void TextAutogenerateWidget::slotAutogenerateFailed(const QString &errorMessage)
{
    qDebug() << " TextAutogenerateWidget::slotAutogenerateFailed " << errorMessage;
    // TODO report error
}

#include "moc_textautogeneratewidget.cpp"
