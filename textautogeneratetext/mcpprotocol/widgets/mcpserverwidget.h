/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetextmcpprotocolwidgets_export.h"
#include <QWidget>
class QLineEdit;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class McpServerListView;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextInstancesMcpServerWidget
 * \brief The TextAutoGenerateTextInstancesMcpServerWidget class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextInstancesMcpServerWidget
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT McpServerWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief McpServerWidget
     * \param manager
     * \param parent
     */
    explicit McpServerWidget(QWidget *parent = nullptr);
    /*!
     */
    ~McpServerWidget() override;

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotAddServer();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotRemoveServer(const QByteArray &identifier);
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotEditServer(const QByteArray &identifier);
    QLineEdit *const mSearchLineEdit;
    McpServerListView *const mMcpServerListView;
};
}
