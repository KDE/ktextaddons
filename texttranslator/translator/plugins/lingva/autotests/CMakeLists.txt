# SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
ecm_add_test(lingvaengineclienttest.cpp lingvaengineclienttest.h ../lingvaengineclient.cpp ../lingvaengineplugin.cpp ../lingvaengineutil.cpp
    ../lingvaenginedialog.cpp ../lingvaenginewidget.cpp ${translator_lingva_debug_SRCS}
    TEST_NAME lingvaengineclienttest
    
    LINK_LIBRARIES KF6::TextAddonsWidgets KF6::WidgetsAddons Qt::Test Qt::Gui KF6::TextTranslator KF6::I18n KF6::ConfigCore
)

#######
ecm_add_test(lingvaenginewidgettest.cpp lingvaenginewidgettest.h ../lingvaenginewidget.cpp
    TEST_NAME lingvaenginewidgettest
    
    LINK_LIBRARIES KF6::TextAddonsWidgets KF6::WidgetsAddons Qt::Test Qt::Gui KF6::TextTranslator KF6::I18n KF6::ConfigCore
)

#######
ecm_add_test(lingvaenginedialogtest.cpp lingvaenginedialogtest.h ../lingvaenginedialog.cpp ../lingvaenginewidget.cpp
    TEST_NAME lingvaenginedialogtest
    
    LINK_LIBRARIES KF6::TextAddonsWidgets KF6::WidgetsAddons Qt::Test Qt::Gui KF6::TextTranslator KF6::I18n KF6::ConfigCore
)

#######
ecm_add_test(lingvaengineutiltest.h lingvaengineutiltest.cpp ../lingvaengineutil.cpp
    TEST_NAME lingvaengineutiltest
    
    LINK_LIBRARIES KF6::TextAddonsWidgets KF6::WidgetsAddons Qt::Test Qt::Gui KF6::TextTranslator KF6::I18n KF6::ConfigCore
)
