/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QTreeView>

class VoskEngineLanguageTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit VoskEngineLanguageTreeView(QWidget *parent = nullptr);
    ~VoskEngineLanguageTreeView() override;
};
