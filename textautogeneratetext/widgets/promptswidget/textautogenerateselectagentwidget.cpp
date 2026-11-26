/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateselectagentwidget.h"
#include "core/models/textautogeneratetextagentmodel.h"
#include "core/textautogenerateagentprompskillmanager.h"
#include "core/textautogeneratemanager.h"
#include "textautogenerateselectagentlistwidget.h"
#include <KLocalizedString>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSelectAgentWidget::TextAutoGenerateSelectAgentWidget(TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mListWidget(new TextAutoGenerateSelectAgentListWidget(this))
    , mAgentModel(new TextAutoGenerateTextAgentModel(this))
    , mManager(manager)
    , mSearchLineEdit(new QLineEdit(this))
    , mFilterProxyModel(new QSortFilterProxyModel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search agent…"));
    mAgentModel->setObjectName(u"mAgentModel"_s);

    mFilterProxyModel->setObjectName(u"mFilterProxyModel"_s);
    mFilterProxyModel->setSourceModel(mAgentModel);
    mFilterProxyModel->setFilterRole(TextAutoGenerateTextAgentModel::Name);
    mFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    mListWidget->setModel(mFilterProxyModel);
    mListWidget->setObjectName(u"mListWidget"_s);
    mainLayout->addWidget(mSearchLineEdit);
    mainLayout->addWidget(mListWidget);

    connect(mSearchLineEdit, &QLineEdit::textChanged, mFilterProxyModel, &QSortFilterProxyModel::setFilterFixedString);

    connect(mListWidget, &TextAutoGenerateSelectAgentListWidget::addAgent, this, &TextAutoGenerateSelectAgentWidget::slotAddAgent);
    connect(mListWidget, &TextAutoGenerateSelectAgentListWidget::editAgent, this, &TextAutoGenerateSelectAgentWidget::slotEditAgent);
    connect(mListWidget, &TextAutoGenerateSelectAgentListWidget::removeAgent, this, &TextAutoGenerateSelectAgentWidget::slotRemoveAgent);
    load();
}

TextAutoGenerateSelectAgentWidget::~TextAutoGenerateSelectAgentWidget() = default;

QList<TextAutoGenerateAgent> TextAutoGenerateSelectAgentWidget::agents() const
{
    return mAgentModel->agents();
}

void TextAutoGenerateSelectAgentWidget::slotEditAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent)
{
    mAgentModel->updateAgent(agent);
    Q_EMIT settingsChanged();
}

void TextAutoGenerateSelectAgentWidget::slotAddAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent)
{
    mAgentModel->addAgent(agent);
    Q_EMIT settingsChanged();
}

void TextAutoGenerateSelectAgentWidget::slotRemoveAgent(const QByteArray &identifier)
{
    mAgentModel->removeAgent(identifier);
    Q_EMIT settingsChanged();
}

void TextAutoGenerateSelectAgentWidget::load()
{
    if (mManager) {
        mAgentModel->setAgents(mManager->textAutoGenerateAgentPrompSkillManager()->agents());
    }
}

void TextAutoGenerateSelectAgentWidget::save()
{
    if (mManager) {
        mManager->textAutoGenerateAgentPrompSkillManager()->setAgents(mAgentModel->agents());
    }
}

#include "moc_textautogenerateselectagentwidget.cpp"
