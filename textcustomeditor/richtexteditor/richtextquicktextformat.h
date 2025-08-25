/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"
#include <QWidget>
namespace TextCustomEditor
{
class TEXTCUSTOMEDITOR_EXPORT RichTextQuickTextFormat : public QWidget
{
    Q_OBJECT
public:
    explicit RichTextQuickTextFormat(QWidget *parent = nullptr);
    ~RichTextQuickTextFormat() override;
};
}
