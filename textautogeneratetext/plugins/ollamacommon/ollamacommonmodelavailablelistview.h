/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "widgets/availablemodel/textautogeneratemodelavailablelistview.h"
class OllamaCommonModelAvailableInfosDelegate;
class OllamaCommonModelAvailableListView : public TextAutoGenerateText::TextAutoGenerateModelAvailableListView
{
    Q_OBJECT
public:
    explicit OllamaCommonModelAvailableListView(QWidget *parent = nullptr);
    ~OllamaCommonModelAvailableListView() override;

protected:
    void resizeEvent(QResizeEvent *ev) override;

private:
    OllamaCommonModelAvailableInfosDelegate *const mAvailableInfosDelegate;
};
