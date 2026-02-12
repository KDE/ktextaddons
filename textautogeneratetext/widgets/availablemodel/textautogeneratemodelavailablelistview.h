/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QListView>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateModelAvailableListView
 * \brief The TextAutoGenerateModelAvailableListView class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateModelAvailableListView
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateModelAvailableListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateModelAvailableListView(QWidget *parent = nullptr);
    ~TextAutoGenerateModelAvailableListView() override;
};
}
