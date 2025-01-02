# SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
ecm_add_test(bingengineclienttest.cpp bingengineclienttest.h ../bingengineclient.cpp ../bingengineplugin.cpp ${translator_debug_bing_SRCS}
    TEST_NAME bingengineclienttest
    
    LINK_LIBRARIES Qt::Test Qt::Gui KF6::TextTranslator KF6::I18n
)
