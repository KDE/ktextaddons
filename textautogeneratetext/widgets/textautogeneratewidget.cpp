/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratewidget.h"
#include "core/textautogenerateengineloader.h"
#include "core/textautogenerateengineutil.h"
#include "core/textautogeneratetextclient.h"
#include "core/textautogeneratetextplugin.h"
#include "widgets/textautogenerateresultwidget.h"
#include "widgets/textautogeneratetextlineeditwidget.h"

#include <QVBoxLayout>

using namespace TextAutogenerateText;
TextAutogenerateWidget::TextAutogenerateWidget(QWidget *parent)
    : QWidget{parent}
    , mTextAutogenerateResultWidget(new TextAutogenerateResultWidget(this))
    , mTextAutogenerateTextLineEditWidget(new TextAutogenerateTextLineEditWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});

    mTextAutogenerateResultWidget->setObjectName(QStringLiteral("mTextAutogenerateResultWidget"));
    mainLayout->addWidget(mTextAutogenerateResultWidget);

    mTextAutogenerateTextLineEditWidget->setObjectName(QStringLiteral("mTextAutogenerateTextLineEditWidget"));
    mainLayout->addWidget(mTextAutogenerateTextLineEditWidget);
    connect(mTextAutogenerateTextLineEditWidget, &TextAutogenerateTextLineEditWidget::editingFinished, this, &TextAutogenerateWidget::slotEditingFinished);
}

TextAutogenerateWidget::~TextAutogenerateWidget() = default;

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
    mTextAutogenerateClient =
        TextAutogenerateText::TextAutogenerateEngineLoader::self()->createTextAutoGenerateTextClient(TextAutogenerateEngineUtil::loadEngine());
    if (!mTextAutogenerateClient) {
        const QString fallBackEngineName = TextAutogenerateText::TextAutogenerateEngineLoader::self()->fallbackFirstEngine();
        if (!fallBackEngineName.isEmpty()) {
            mTextAutogenerateClient = TextAutogenerateText::TextAutogenerateEngineLoader::self()->createTextAutoGenerateTextClient(fallBackEngineName);
        }
    }
    if (mTextAutogenerateClient) {
        mTextAutogeneratePlugin = mTextAutogenerateClient->createTextAutogeneratePlugin();
        connect(mTextAutogeneratePlugin, &TextAutogenerateText::TextAutogenerateTextPlugin::finished, this, &TextAutogenerateWidget::slotAutogenerateFinished);
        connect(mTextAutogeneratePlugin,
                &TextAutogenerateText::TextAutogenerateTextPlugin::errorOccurred,
                this,
                &TextAutogenerateWidget::slotAutogenerateFailed);
    }
}

void TextAutogenerateWidget::slotEditingFinished(const QString &str)
{
    // TODO
}

void TextAutogenerateWidget::slotAutogenerateFinished()
{
    // TODO
}

void TextAutogenerateWidget::slotAutogenerateFailed()
{
    // TODO
}

#include "moc_textautogeneratewidget.cpp"
