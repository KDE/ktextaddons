/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "texttranslator_export.h"
#include <QDialog>
namespace TextTranslator
{
class TranslatorConfigureWidget;
/*!
 * \class TranslatorConfigureDialog
 * \inheaders TextTranslator/TranslatorConfigureDialog
 * \inmodule TextTranslator
 * \brief Dialog for translator configuration.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTTRANSLATOR_EXPORT TranslatorConfigureDialog : public QDialog
{
public:
    /*!
     */
    explicit TranslatorConfigureDialog(QWidget *parent = nullptr);
    /*!
     */
    ~TranslatorConfigureDialog() override;

private:
    TEXTTRANSLATOR_NO_EXPORT void slotAccept();
    TranslatorConfigureWidget *const mTranslatorConfigureWidget;
};
}
