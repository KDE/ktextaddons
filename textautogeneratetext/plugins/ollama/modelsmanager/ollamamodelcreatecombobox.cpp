/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamodelcreatecombobox.h"
#include "ollamamanager.h"

OllamaModelCreateComboBox::OllamaModelCreateComboBox(OllamaManager *manager, QWidget *parent)
    : QComboBox(parent)
    , mOllamaManager(manager)
{
    fillEngine();
}

OllamaModelCreateComboBox::~OllamaModelCreateComboBox() = default;

QString OllamaModelCreateComboBox::modelName() const
{
    return currentData().toString();
}

void OllamaModelCreateComboBox::fillEngine()
{
    if (mOllamaManager) {
        connect(mOllamaManager, &OllamaManager::modelsLoadDone, this, [this]() {
            const QList<OllamaModelInstalledInfo> infos = mOllamaManager->installedInfos();
            for (const auto &info : infos) {
                addItem(info.generateModelName(), info.model());
            }
        });
    }
}

#include "moc_ollamamodelcreatecombobox.cpp"
