/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "modelsmanager/ollamamodelavailableinfosmanager.h"
#include "modelsmanager/ollamamodelavailablewidget.h"
#include "ollamamanager.h"
#include "ollamasettings.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto manager = new OllamaManager(new OllamaSettings);
    auto w = new OllamaModelAvailableWidget(manager);
    OllamaModelAvailableInfosManager managerModelInfosManager;
    if (managerModelInfosManager.loadAvailableModels()) {
        w->setAvailableInfos(managerModelInfosManager.modelInfos());
    }
    w->resize(600, 400);
    w->show();
    app.exec();
    delete w;
    return 0;
}
