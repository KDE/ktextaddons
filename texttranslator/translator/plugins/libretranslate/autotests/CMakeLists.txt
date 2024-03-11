# SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(translator_libretranslate_LIB qt6keychain)
ecm_add_test(libretranslateengineclienttest.cpp libretranslateengineclienttest.h ../libretranslateengineclient.cpp ../libretranslateengineplugin.cpp
    ../libretranslateengineconfiguredialog.cpp ../libretranslateengineconfigurewidget.cpp ../libretranslateengineutil.h ../libretranslateengineutil.cpp
    ${translator_libretranslate_debug_SRCS}
    TEST_NAME libretranslateengineclienttest
    
    LINK_LIBRARIES KF6::TextAddonsWidgets KF6::WidgetsAddons Qt::Test Qt::Gui KF6::TextTranslator KF6::I18n KF6::ConfigCore ${translator_libretranslate_LIB}
)

######
ecm_add_test(libretranslateengineconfigurewidgettest.cpp libretranslateengineconfigurewidgettest.h
    ../libretranslateengineconfigurewidget.cpp
    TEST_NAME libretranslateengineconfigurewidgettest
    
    LINK_LIBRARIES KF6::TextAddonsWidgets KF6::WidgetsAddons Qt::Test Qt::Gui KF6::TextTranslator KF6::I18n
)

######
ecm_add_test(libretranslateengineconfiguredialogtest.cpp libretranslateengineconfiguredialogtest.h
    ../libretranslateengineconfiguredialog.cpp ../libretranslateengineconfigurewidget.cpp
    TEST_NAME libretranslateengineconfiguredialogtest
    
    LINK_LIBRARIES KF6::TextAddonsWidgets KF6::WidgetsAddons Qt::Test Qt::Gui KF6::TextTranslator KF6::I18n
)

######
ecm_add_test(libretranslateengineutiltest.cpp libretranslateengineutiltest.h
    ../libretranslateengineutil.cpp
    TEST_NAME libretranslateengineutiltest
    
    LINK_LIBRARIES KF6::TextAddonsWidgets KF6::WidgetsAddons Qt::Test Qt::Gui KF6::TextTranslator KF6::I18n
)
