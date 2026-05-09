/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "plugins/plugincommon/plugincommonmodelinstalledinfosdelegate.h"

class OllamaModelInstalledInfosDelegate : public PluginCommonModelInstalledInfosDelegate
{
    Q_OBJECT
public:
    explicit OllamaModelInstalledInfosDelegate(QListView *view);
    ~OllamaModelInstalledInfosDelegate() override;

    [[nodiscard]] QTextDocument *documentForIndex(const QModelIndex &index, int width) const override;
};
