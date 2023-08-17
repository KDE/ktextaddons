/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef TEXTCUSTOMEDITOR_TESTS_EXPORT
#define TEXTCUSTOMEDITOR_TESTS_EXPORT TEXTCUSTOMEDITOR_EXPORT
#endif
#else /* not compiling tests */
#define TEXTCUSTOMEDITOR_TESTS_EXPORT
#endif
