/*
    SPDX-FileCopyrightText: 2002 Dave Corrie <kde@davecorrie.com>
    SPDX-FileCopyrightText: 2014 Daniel Vrátil <dvratil@redhat.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textutils_export.h"

#include <QString>

/*!
 * \namespace TextUtils::TextUtilsTextToHtml
 * \inmodule TextUtils
 *
 * Copied from KTextToHTML (KCoreAddons), with its parsing optimizations.
 */
namespace TextUtils
{
namespace TextUtilsTextToHtml
{
Q_NAMESPACE_EXPORT(TEXTUTILS_EXPORT)
/*!
 * \value PreserveSpaces Preserve white-space formatting of the text
 * \value ReplaceSmileys Replace text emoticons smileys by emoticons images
 * \value IgnoreUrls Don't parse and replace any URLs
 * \value HighlightText Interpret text highlighting markup, like *bold*, _underline_ and /italic/, and wrap them in corresponding HTML entities
 * \value ConvertPhoneNumbers Replace phone numbers with tel: links
 */
enum Option {
    PreserveSpaces = 1 << 1,
    ReplaceSmileys = 1 << 2,
    IgnoreUrls = 1 << 3,
    HighlightText = 1 << 4,
    ConvertPhoneNumbers = 1 << 5,
};
Q_DECLARE_FLAGS(Options, Option)
Q_DECLARE_OPERATORS_FOR_FLAGS(Options)
Q_FLAG_NS(Options)

/*!
 * Converts plaintext into html. The following characters are converted
 * to HTML entities: & " < >. Newlines are also preserved.
 *
 * \a plainText The text to be converted into HTML.
 *
 * \a options The options to use when processing \a plainText.
 *
 * \a maxUrlLen The maximum length of permitted URLs. The reason for
 *                    this limit is that there may be possible security
 *                    implications in handling URLs of unlimited length.
 *
 * \a maxAddressLen The maximum length of permitted email addresses.
 *                    The reason for this limit is that there may be possible
 *                    security implications in handling addresses of unlimited
 *                    length.
 *
 * Returns an HTML version of the text supplied in the 'plainText'
 * parameter, suitable for inclusion in the BODY of an HTML document.
 */
[[nodiscard]] TEXTUTILS_EXPORT QString convertToHtml(const QString &plainText,
                                                     const TextUtils::TextUtilsTextToHtml::Options &options,
                                                     int maxUrlLen = 4096,
                                                     int maxAddressLen = 255);

}
}
