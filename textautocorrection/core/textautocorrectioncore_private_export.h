/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautocorrectioncore_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef TEXTAUTOCORRECTIONCORE_TESTS_EXPORT
#define TEXTAUTOCORRECTIONCORE_TESTS_EXPORT TEXTAUTOCORRECTIONCORE_EXPORT
#endif
#else /* not compiling tests */
#define TEXTAUTOCORRECTIONCORE_TESTS_EXPORT
#endif
