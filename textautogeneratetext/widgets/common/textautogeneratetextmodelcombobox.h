/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QComboBox>
#include <TextAutoGenerateText/TextAutoGenerateTextPlugin>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextModelComboBox
 * \brief The TextAutoGenerateTextModelComboBox class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextModelComboBox
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextModelComboBox : public QComboBox
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for TextAutoGenerateTextModelComboBox
     * \param parent The parent widget
     */
    explicit TextAutoGenerateTextModelComboBox(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for TextAutoGenerateTextModelComboBox
     */
    ~TextAutoGenerateTextModelComboBox() override;
    /*!
     * \brief Sets the list of available models
     * \param lst The list of model information
     */
    void setModelList(const QList<TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier> &lst);
    /*!
     * \brief Returns the currently selected model identifier
     * \return The model identifier
     */
    [[nodiscard]] QString currentModel() const;
    /*!
     * \brief Sets the currently selected model
     * \param identifier The model identifier to select
     */
    void setCurrentModel(const QString &identifier);
};
}
