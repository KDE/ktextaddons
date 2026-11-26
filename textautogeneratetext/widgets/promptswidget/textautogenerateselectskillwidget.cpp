/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateselectskillwidget.h"
#include "core/models/textautogeneratetextskillmodel.h"
#include "core/textautogenerateagentprompskillmanager.h"
#include "core/textautogeneratemanager.h"
#include "textautogenerateselectskilllistwidget.h"
#include <KLocalizedString>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSelectSkillWidget::TextAutoGenerateSelectSkillWidget(TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mListWidget(new TextAutoGenerateSelectSkillListWidget(this))
    , mSkillModel(new TextAutoGenerateTextSkillModel(this))
    , mManager(manager)
    , mSearchLineEdit(new QLineEdit(this))
    , mFilterProxyModel(new QSortFilterProxyModel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search skill…"));
    mainLayout->addWidget(mSearchLineEdit);

    mSkillModel->setObjectName(u"mSkillModel"_s);

    mFilterProxyModel->setObjectName(u"mFilterProxyModel"_s);
    mFilterProxyModel->setSourceModel(mSkillModel);
    mFilterProxyModel->setFilterRole(TextAutoGenerateTextSkillModel::Name);
    mFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    mListWidget->setModel(mFilterProxyModel);
    mListWidget->setObjectName(u"mListWidget"_s);
    mainLayout->addWidget(mListWidget);

    connect(mSearchLineEdit, &QLineEdit::textChanged, mFilterProxyModel, &QSortFilterProxyModel::setFilterFixedString);

    connect(mListWidget, &TextAutoGenerateSelectSkillListWidget::addSkill, this, &TextAutoGenerateSelectSkillWidget::slotAddSkill);
    connect(mListWidget, &TextAutoGenerateSelectSkillListWidget::editSkill, this, &TextAutoGenerateSelectSkillWidget::slotEditSkill);
    connect(mListWidget, &TextAutoGenerateSelectSkillListWidget::removeSkill, this, &TextAutoGenerateSelectSkillWidget::slotRemoveSkill);
    load();
}

TextAutoGenerateSelectSkillWidget::~TextAutoGenerateSelectSkillWidget() = default;

QList<TextAutoGenerateSkill> TextAutoGenerateSelectSkillWidget::skills() const
{
    return mSkillModel->skills();
}

void TextAutoGenerateSelectSkillWidget::slotEditSkill(const TextAutoGenerateText::TextAutoGenerateSkill &skill)
{
    mSkillModel->updateSkill(skill);
    Q_EMIT settingsChanged();
}

void TextAutoGenerateSelectSkillWidget::slotAddSkill(const TextAutoGenerateText::TextAutoGenerateSkill &skill)
{
    mSkillModel->addSkill(skill);
    Q_EMIT settingsChanged();
}

void TextAutoGenerateSelectSkillWidget::slotRemoveSkill(const QByteArray &identifier)
{
    mSkillModel->removeSkill(identifier);
    Q_EMIT settingsChanged();
}

void TextAutoGenerateSelectSkillWidget::load()
{
    if (mManager) {
        mSkillModel->setSkills(mManager->textAutoGenerateAgentPrompSkillManager()->skills());
    }
}

void TextAutoGenerateSelectSkillWidget::save()
{
    if (mManager) {
        mManager->textAutoGenerateAgentPrompSkillManager()->setSkills(mSkillModel->skills());
    }
}

#include "moc_textautogenerateselectskillwidget.cpp"
