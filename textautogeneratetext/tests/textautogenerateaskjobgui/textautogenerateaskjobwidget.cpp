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
    auto button = new QPushButton(u"Ask"_s, this);
    hbox->addWidget(button);

    mainLayout->addLayout(hbox);

    auto plainTextEdit = new QPlainTextEdit(this);
    plainTextEdit->setReadOnly(true);

    mainLayout->addWidget(plainTextEdit);

    connect(button, &QPushButton::clicked, this, [this, lineEdit, plainTextEdit]() {
        if (const QString text = lineEdit->text(); !text.isEmpty()) {
            TextAutoGenerateText::TextAutoGenerateManager *manager = new TextAutoGenerateText::TextAutoGenerateManager(this);
            TextAutoGenerateText::TextAutoGenerateAskJob *job = new TextAutoGenerateText::TextAutoGenerateAskJob(this);
            job->setText(text);
            job->setManager(manager);
            connect(job, &TextAutoGenerateText::TextAutoGenerateAskJob::generateTextDone, this, [this]() {
                qDebug() << " generate text done ::::::::::";
            });
            connect(job, &TextAutoGenerateText::TextAutoGenerateAskJob::generateTextInProgress, this, [this, plainTextEdit](const QString &str) {
                plainTextEdit->setPlainText(str);
            });
            job->start();
        }
    });
}

TextAutoGenerateAskJobWidget::~TextAutoGenerateAskJobWidget() = default;

#include "moc_textautogenerateaskjobwidget.cpp"
