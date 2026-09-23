/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemanageprojectswidget.h"
#include "core/models/textautogenerateprojectsmodel.h"
#include "textautogenerateprojectdialog.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QHBoxLayout>
#include <QListView>
#include <QPointer>
#include <QToolButton>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

TextAutoGenerateManageProjectsWidget::TextAutoGenerateManageProjectsWidget(QWidget *parent)
    : QWidget{parent}
    , mProjectsListView(new QListView(this))
    , mProjectsModel(new TextAutoGenerateProjectsModel(this))
    , mAddButton(new QToolButton(this))
    , mModifyButton(new QToolButton(this))
    , mRemoveButton(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mProjectsListView->setObjectName(u"mProjectsListView"_s);
    mProjectsListView->setModel(mProjectsModel);
    mProjectsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(mProjectsListView);
    connect(mProjectsListView, &QListView::doubleClicked, this, qOverload<const QModelIndex &>(&TextAutoGenerateManageProjectsWidget::slotModifyProject));
    connect(mProjectsListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &TextAutoGenerateManageProjectsWidget::updateButtons);

    auto buttonLayout = new QVBoxLayout;
    buttonLayout->setObjectName(u"buttonLayout"_s);
    buttonLayout->setContentsMargins({});
    mainLayout->addLayout(buttonLayout);

    mAddButton->setObjectName(u"mAddButton"_s);
    mAddButton->setIcon(QIcon::fromTheme(u"list-add"_s));
    mAddButton->setToolTip(i18nc("@info:tooltip", "Add Project…"));
    mAddButton->setAutoRaise(true);
    buttonLayout->addWidget(mAddButton);
    connect(mAddButton, &QToolButton::clicked, this, &TextAutoGenerateManageProjectsWidget::slotAddProject);

    mModifyButton->setObjectName(u"mModifyButton"_s);
    mModifyButton->setIcon(QIcon::fromTheme(u"edit-rename"_s));
    mModifyButton->setToolTip(i18nc("@info:tooltip", "Modify Project…"));
    mModifyButton->setAutoRaise(true);
    buttonLayout->addWidget(mModifyButton);
    connect(mModifyButton, &QToolButton::clicked, this, qOverload<>(&TextAutoGenerateManageProjectsWidget::slotModifyProject));

    mRemoveButton->setObjectName(u"mRemoveButton"_s);
    mRemoveButton->setIcon(QIcon::fromTheme(u"list-remove"_s));
    mRemoveButton->setToolTip(i18nc("@info:tooltip", "Remove Project"));
    mRemoveButton->setAutoRaise(true);
    buttonLayout->addWidget(mRemoveButton);
    connect(mRemoveButton, &QToolButton::clicked, this, &TextAutoGenerateManageProjectsWidget::slotRemoveProject);

    buttonLayout->addStretch(1);

    updateButtons();
}

TextAutoGenerateManageProjectsWidget::~TextAutoGenerateManageProjectsWidget() = default;

void TextAutoGenerateManageProjectsWidget::setProjects(const QList<TextAutoGenerateText::TextAutoGenerateProject> &projects)
{
    mProjectsModel->setProjects(projects);
    updateButtons();
}

QList<TextAutoGenerateText::TextAutoGenerateProject> TextAutoGenerateManageProjectsWidget::projects() const
{
    return mProjectsModel->projects();
}

void TextAutoGenerateManageProjectsWidget::slotAddProject()
{
    QPointer<TextAutoGenerateProjectDialog> dialog(new TextAutoGenerateProjectDialog(this));
    if (dialog->exec()) {
        mProjectsModel->addProject(dialog->project());
    }
    delete dialog;
}

void TextAutoGenerateManageProjectsWidget::slotModifyProject()
{
    slotModifyProject(mProjectsListView->currentIndex());
}

void TextAutoGenerateManageProjectsWidget::slotModifyProject(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    QPointer<TextAutoGenerateProjectDialog> dialog(new TextAutoGenerateProjectDialog(this));
    dialog->setProject(projectFromIndex(index));
    if (dialog->exec()) {
        mProjectsModel->updateProject(dialog->project());
    }
    delete dialog;
}

void TextAutoGenerateManageProjectsWidget::slotRemoveProject()
{
    const QModelIndex index = mProjectsListView->currentIndex();
    if (!index.isValid()) {
        return;
    }
    const QString name = index.data(TextAutoGenerateProjectsModel::Name).toString();
    if (KMessageBox::questionTwoActions(this,
                                        i18n("Do you want to remove this project (%1)? Its chats will be kept, outside of any project.", name),
                                        i18nc("@title:window", "Remove Project"),
                                        KStandardGuiItem::remove(),
                                        KStandardGuiItem::cancel())
        == KMessageBox::PrimaryAction) {
        mProjectsModel->removeProject(index.data(TextAutoGenerateProjectsModel::Identifier).toByteArray());
        updateButtons();
    }
}

TextAutoGenerateText::TextAutoGenerateProject TextAutoGenerateManageProjectsWidget::projectFromIndex(const QModelIndex &index) const
{
    TextAutoGenerateText::TextAutoGenerateProject project;
    project.setIdentifier(index.data(TextAutoGenerateProjectsModel::Identifier).toByteArray());
    project.setName(index.data(TextAutoGenerateProjectsModel::Name).toString());
    // TODO project.setColor(index.data(TextAutoGenerateProjectsModel::Color).value<QColor>());
    return project;
}

void TextAutoGenerateManageProjectsWidget::updateButtons()
{
    const bool hasSelection = mProjectsListView->selectionModel()->hasSelection();
    mModifyButton->setEnabled(hasSelection);
    mRemoveButton->setEnabled(hasSelection);
}

#include "moc_textautogeneratemanageprojectswidget.cpp"
