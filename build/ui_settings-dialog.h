/********************************************************************************
** Form generated from reading UI file 'settings-dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_2D_DIALOG_H
#define UI_SETTINGS_2D_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QCheckBox *authRequired;
    QLabel *lbl_password;
    QLineEdit *password;
    QCheckBox *serverEnabled;
    QLabel *lbl_serverPort;
    QSpinBox *serverPort;
    QCheckBox *alertsEnabled;
    QCheckBox *debugEnabled;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->resize(407, 195);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SettingsDialog->sizePolicy().hasHeightForWidth());
        SettingsDialog->setSizePolicy(sizePolicy);
        SettingsDialog->setSizeGripEnabled(false);
        verticalLayout = new QVBoxLayout(SettingsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        authRequired = new QCheckBox(SettingsDialog);
        authRequired->setObjectName(QStringLiteral("authRequired"));

        formLayout->setWidget(3, QFormLayout::FieldRole, authRequired);

        lbl_password = new QLabel(SettingsDialog);
        lbl_password->setObjectName(QStringLiteral("lbl_password"));

        formLayout->setWidget(4, QFormLayout::LabelRole, lbl_password);

        password = new QLineEdit(SettingsDialog);
        password->setObjectName(QStringLiteral("password"));
        password->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(4, QFormLayout::FieldRole, password);

        serverEnabled = new QCheckBox(SettingsDialog);
        serverEnabled->setObjectName(QStringLiteral("serverEnabled"));
        serverEnabled->setChecked(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, serverEnabled);

        lbl_serverPort = new QLabel(SettingsDialog);
        lbl_serverPort->setObjectName(QStringLiteral("lbl_serverPort"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lbl_serverPort);

        serverPort = new QSpinBox(SettingsDialog);
        serverPort->setObjectName(QStringLiteral("serverPort"));
        serverPort->setMinimum(1024);
        serverPort->setMaximum(65535);
        serverPort->setValue(4444);

        formLayout->setWidget(2, QFormLayout::FieldRole, serverPort);

        alertsEnabled = new QCheckBox(SettingsDialog);
        alertsEnabled->setObjectName(QStringLiteral("alertsEnabled"));
        alertsEnabled->setChecked(true);

        formLayout->setWidget(5, QFormLayout::FieldRole, alertsEnabled);

        debugEnabled = new QCheckBox(SettingsDialog);
        debugEnabled->setObjectName(QStringLiteral("debugEnabled"));
        debugEnabled->setChecked(false);

        formLayout->setWidget(6, QFormLayout::FieldRole, debugEnabled);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "OBSWebsocket.Settings.DialogTitle", 0));
        authRequired->setText(QApplication::translate("SettingsDialog", "OBSWebsocket.Settings.AuthRequired", 0));
        lbl_password->setText(QApplication::translate("SettingsDialog", "OBSWebsocket.Settings.Password", 0));
        serverEnabled->setText(QApplication::translate("SettingsDialog", "OBSWebsocket.Settings.ServerEnable", 0));
        lbl_serverPort->setText(QApplication::translate("SettingsDialog", "OBSWebsocket.Settings.ServerPort", 0));
        alertsEnabled->setText(QApplication::translate("SettingsDialog", "OBSWebsocket.Settings.AlertsEnable", 0));
        debugEnabled->setText(QApplication::translate("SettingsDialog", "OBSWebsocket.Settings.DebugEnable", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_2D_DIALOG_H
