/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpserverrootswidget.h"
#include <KEditListWidget>
#include <KLocalizedString>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpServerRootsWidget::AddMcpServerRootsWidget(QWidget *parent)
    : QWidget{parent}
    , mDirectoryLineEdit(new QLineEdit(this))
    , mEditListWidget(new KEditListWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    // Editor: line edit + button to select directory
    auto editorWidget = new QWidget(this);
    editorWidget->setObjectName(u"editorWidget"_s);
    auto editorLayout = new QHBoxLayout(editorWidget);
    editorLayout->setObjectName(u"editorLayout"_s);
    editorLayout->setContentsMargins({});

    mDirectoryLineEdit->setObjectName(u"mDirectoryLineEdit"_s);
    mDirectoryLineEdit->setClearButtonEnabled(true);
    mDirectoryLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Folder…"));
    editorLayout->addWidget(mDirectoryLineEdit);

    auto selectDirectoryButton = new QToolButton(editorWidget);
    selectDirectoryButton->setObjectName(u"selectDirectoryButton"_s);
    selectDirectoryButton->setIcon(QIcon::fromTheme(u"document-open-folder"_s));
    selectDirectoryButton->setToolTip(i18nc("@info:tooltip", "Select Folder"));
    editorLayout->addWidget(selectDirectoryButton);
    connect(selectDirectoryButton, &QToolButton::clicked, this, &AddMcpServerRootsWidget::selectDirectory);

    mEditListWidget->setObjectName(u"mEditListWidget"_s);
    mEditListWidget->setCustomEditor(KEditListWidget::CustomEditor(editorWidget, mDirectoryLineEdit));
    mEditListWidget->setButtons(KEditListWidget::Add | KEditListWidget::Remove);
    mEditListWidget->setToolTip(i18nc("@info:tooltip", "Folders that server is allowed to access"));
    mainLayout->addWidget(mEditListWidget);
    connect(mEditListWidget, &KEditListWidget::changed, this, &AddMcpServerRootsWidget::rootsChanged);
}

AddMcpServerRootsWidget::~AddMcpServerRootsWidget() = default;

void AddMcpServerRootsWidget::selectDirectory()
{
    const QString directory = QFileDialog::getExistingDirectory(this, i18nc("@title:window", "Select Folder"), mDirectoryLineEdit->text());
    if (!directory.isEmpty()) {
        mDirectoryLineEdit->setText(directory);
    }
}

QStringList AddMcpServerRootsWidget::roots() const
{
    return mEditListWidget->items();
}

void AddMcpServerRootsWidget::setRoots(const QStringList &roots)
{
    mEditListWidget->setItems(roots);
}

#include "moc_addmcpserverrootswidget.cpp"
