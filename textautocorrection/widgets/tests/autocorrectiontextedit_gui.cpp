/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrector.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>
#include <QTextEdit>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto w = new QTextEdit;
    new TextAutoCorrectionWidgets::AutoCorrector(w);

    w->show();
    app.exec();
    delete w;
    return 0;
}
