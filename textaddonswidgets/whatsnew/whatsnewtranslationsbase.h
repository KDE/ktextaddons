/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <KLazyLocalizedString>
#include <TextAddonsWidgets/WhatsNewInfo>
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::WhatsNewTranslationsBase
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/WhatsNewTranslationsBase
 *
 * \brief The WhatsNewTranslationsBase class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT WhatsNewTranslationsBase
{
public:
    /*!
     * \brief Constructor for WhatsNewTranslationsBase
     */
    WhatsNewTranslationsBase();
    /*!
     * \brief Virtual destructor for WhatsNewTranslationsBase
     */
    virtual ~WhatsNewTranslationsBase();
    /*!
     * \brief Creates a list of WhatsNewInfo objects with the latest changes
     * \return A list of WhatsNewInfo objects
     */
    [[nodiscard]] virtual QList<WhatsNewInfo> createWhatsNewInfo() const = 0;
    /*!
     * \brief Returns the MD5 hash of the new features
     * \return The MD5 hash string
     */
    [[nodiscard]] QString newFeaturesMD5() const;

private:
    [[nodiscard]] virtual QList<KLazyLocalizedString> lastNewFeatures() const = 0;
};
}
