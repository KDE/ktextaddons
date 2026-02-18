/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautocorrectioncore_export.h"
#include "textautocorrectionsetting_base.h"

class QTimer;

namespace TextAutoCorrectionCore
{
/*!
 * \class TextAutoCorrectionCore::TextAutoCorrectionSettings
 * \inmodule TextAutoCorrectionCore
 * \inheaderfile TextAutoCorrectionCore/TextAutoCorrectionSettings
 *
 * \brief Singleton wrapper for text autocorrection settings configuration.
 *
 * Provides convenient access to autocorrection settings with optimized
 * configuration file synchronization using a timer.
 *
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTIONCORE_EXPORT TextAutoCorrectionSettings : public TextAutoCorrectionCore::TextAutoCorrectionSettingsBase
{
    Q_OBJECT
public:
    /*!
     * \brief Returns the singleton instance of TextAutoCorrectionSettings
     * \return A pointer to the TextAutoCorrectionSettings singleton
     */
    static TextAutoCorrectionSettings *self();

    /*!
     * \brief Requests a synchronization of the configuration settings.
     *
     * Call this slot instead of directly calling KConfig::sync() to
     * minimize the overall config writes. Calling this slot will
     * schedule a sync of the application config file using a timer, so
     * that many consecutive calls can be condensed into a single
     * sync, which is more efficient.
     */
    void requestSync();

private Q_SLOTS:
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void slotSyncNow();

private:
    TEXTAUTOCORRECTIONCORE_NO_EXPORT TextAutoCorrectionSettings();
    ~TextAutoCorrectionSettings() override;
    static TextAutoCorrectionSettings *mSelf;

    QTimer *const mConfigSyncTimer;
};
}
