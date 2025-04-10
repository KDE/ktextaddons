/*
  SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautocorrectioncore_export.h"
#include "textautocorrectionsetting_base.h"

class QTimer;

namespace TextAutoCorrectionCore
{
/**
 * @brief The TextAutoCorrectionSettings class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTIONCORE_EXPORT TextAutoCorrectionSettings : public TextAutoCorrectionCore::TextAutoCorrectionSettingsBase
{
    Q_OBJECT
public:
    static TextAutoCorrectionSettings *self();

    /** Call this slot instead of directly @ref KConfig::sync() to
      minimize the overall config writes. Calling this slot will
      schedule a sync of the application config file using a timer, so
      that many consecutive calls can be condensed into a single
      sync, which is more efficient. */
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
