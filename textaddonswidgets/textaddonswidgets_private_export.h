/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textaddonswidgets_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef TEXTADDONSWIDGETS_TESTS_EXPORT
#define TEXTADDONSWIDGETS_TESTS_EXPORT TEXTADDONSWIDGETS_EXPORT
#endif
#else /* not compiling tests */
#define TEXTADDONSWIDGETS_TESTS_EXPORT
#endif
