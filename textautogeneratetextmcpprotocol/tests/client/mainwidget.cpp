/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "mainwidget.h"
#include <QSplitter>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocol/McpProtocolClient>

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    auto splitter = new QSplitter(this);
    mainLayout->addWidget(splitter);
    splitter->setChildrenCollapsible(false);

    auto treeview = new QTreeWidget(this);
    splitter->addWidget(treeview);
    // TODO
    auto client = new TextAutoGenerateTextMcpProtocolCore::McpProtocolClient(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType::Sse, this);
}

MainWidget::~MainWidget()
{
    qDeleteAll(mListClient);
}

#include "moc_mainwidget.cpp"
