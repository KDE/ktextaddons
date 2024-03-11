# SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(translator_deepl_LIB qt6keychain)
ecm_add_test(deeplengineclienttest.cpp deeplengineclienttest.h ../deeplengineclient.cpp ../deeplengineplugin.cpp ../deeplengineutil.cpp ${translator_debug_deepl_SRCS}
    ../deeplengineconfiguredialog.cpp
    ../deeplengineconfigurewidget.cpp
    TEST_NAME deeplengineclienttest

    LINK_LIBRARIES KF6::TextAddonsWidgets KF6::WidgetsAddons Qt::Test Qt::Gui KF6::TextTranslator KF6::I18n KF6::ConfigCore ${translator_deepl_LIB}
)

#####
ecm_add_test(deeplengineconfiguredialogtest.cpp deeplengineconfiguredialogtest.h ../deeplengineconfiguredialog.cpp ../deeplengineconfigurewidget.cpp ${translator_debug_deepl_SRCS}
    TEST_NAME deeplengineconfiguredialogtest

    LINK_LIBRARIES KF6::TextAddonsWidgets Qt::Test Qt::Gui KF6::WidgetsAddons KF6::TextTranslator KF6::I18n KF6::ConfigCore
)

#####
ecm_add_test(deeplengineconfigurewidgettest.cpp deeplengineconfigurewidgettest.h ../deeplengineconfigurewidget.cpp
    TEST_NAME deeplengineconfigurewidgettest

    LINK_LIBRARIES KF6::TextAddonsWidgets Qt::Test Qt::Gui KF6::WidgetsAddons KF6::TextTranslator KF6::I18n KF6::ConfigCore
)
