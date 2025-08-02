/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaskjobwidget.h"
using namespace Qt::Literals::StringLiterals;

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGenerateAskJob>
#include <TextAutoGenerateText/TextAutoGenerateManager>

TextAutoGenerateAskJobWidget::TextAutoGenerateAskJobWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    auto hbox = new QHBoxLayout;
    hbox->setContentsMargins({});

    auto lineEdit = new QLineEdit(this);
    hbox->addWidget(lineEdit);
    auto askButton = new QPushButton(u"Ask"_s, this);
    hbox->addWidget(askButton);

    auto configureButton = new QPushButton(u"Configure..."_s, this);
    hbox->addWidget(configureButton);

    mainLayout->addLayout(hbox);

    auto plainTextEdit = new QPlainTextEdit(this);
    plainTextEdit->setReadOnly(true);

    mainLayout->addWidget(plainTextEdit);

    TextAutoGenerateText::TextAutoGenerateManager *manager = new TextAutoGenerateText::TextAutoGenerateManager(this);
    connect(askButton, &QPushButton::clicked, this, [this, lineEdit, plainTextEdit, manager]() {
        if (const QString text = lineEdit->text(); !text.isEmpty()) {
            TextAutoGenerateText::TextAutoGenerateAskJob *job = new TextAutoGenerateText::TextAutoGenerateAskJob(this);
            job->setText(text);
            job->setManager(manager);
            connect(job, &TextAutoGenerateText::TextAutoGenerateAskJob::generateTextDone, this, []() {
                qDebug() << " generate text done ::::::::::";
            });
            connect(job, &TextAutoGenerateText::TextAutoGenerateAskJob::generateTextInProgress, this, [plainTextEdit](const QString &str) {
                plainTextEdit->setPlainText(str);
            });
            job->start();
        }
    });

    connect(configureButton, &QPushButton::clicked, this, [this, manager]() {
        // TODO
    });
}

TextAutoGenerateAskJobWidget::~TextAutoGenerateAskJobWidget() = default;

#include "moc_textautogenerateaskjobwidget.cpp"
