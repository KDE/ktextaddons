/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "texttranslator_export.h"
#include <QWidget>
namespace TextTranslator
{
/*!
 * \class TextTranslator::TranslatorConfigureWidget
 * \inheaderfile TextTranslator/TranslatorConfigureWidget
 * \inmodule TextTranslator
 * \brief Widget for translator configuration settings.
 */
class TEXTTRANSLATOR_EXPORT TranslatorConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     */
    explicit TranslatorConfigureWidget(QWidget *parent = nullptr);
    /*!
     */
    ~TranslatorConfigureWidget() override;

    /*!
     */
    void saveSettings();
    /*!
     */
    void loadSettings();

private:
    class TranslatorConfigureWidgetPrivate;
    std::unique_ptr<TranslatorConfigureWidgetPrivate> const d;
};
}
