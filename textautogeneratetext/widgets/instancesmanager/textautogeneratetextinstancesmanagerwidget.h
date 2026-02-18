/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
class QLineEdit;
namespace TextAutoGenerateText
{
class TextAutoGenerateTextInstancesManagerListView;
class TextAutoGenerateManager;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextInstancesManagerWidget
 * \brief The TextAutoGenerateTextInstancesManagerWidget class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextInstancesManagerWidget
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstancesManagerWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for TextAutoGenerateTextInstancesManagerWidget
     * \param manager The TextAutoGenerateManager instance
     * \param parent The parent widget
     */
    explicit TextAutoGenerateTextInstancesManagerWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    /*!
     * \brief Destructor for TextAutoGenerateTextInstancesManagerWidget
     */
    ~TextAutoGenerateTextInstancesManagerWidget() override;

    /*!
     * \brief Saves the current instances configuration
     */
    void save();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAddInstance();
    TextAutoGenerateTextInstancesManagerListView *const mInstancesManagerListView;
    QLineEdit *const mSearchLineEdit;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
