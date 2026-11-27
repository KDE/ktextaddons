/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QObject>

#include "textautogeneratetext_export.h"
class QWidget;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextPluginConfigure
 * \brief The TextAutoGenerateTextPluginConfigure class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextPluginConfigure
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextPluginConfigure
{
public:
    virtual ~TextAutoGenerateTextPluginConfigure() = default;
    virtual void showConfigureDialog(QWidget *parent) = 0;

protected:
    TextAutoGenerateTextPluginConfigure() = default;

private:
    Q_DISABLE_COPY_MOVE(TextAutoGenerateTextPluginConfigure)
};

}
Q_DECLARE_INTERFACE(TextAutoGenerateText::TextAutoGenerateTextPluginConfigure, "org.kde.textautogeneratetext.pluginconfigure")
