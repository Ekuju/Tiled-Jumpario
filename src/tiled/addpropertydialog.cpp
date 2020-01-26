/*
 * addpropertydialog.cpp
 * Copyright 2015, CaptainFrog <jwilliam.perreault@gmail.com>
 * Copyright 2016, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "addpropertydialog.h"
#include "ui_addpropertydialog.h"

#include "preferences.h"
#include "properties.h"
#include "utils.h"
#include "documentmanager.h"

#include <QPushButton>
#include <QSettings>

using namespace Tiled;

static const char * const TYPE_KEY = "AddPropertyDialog/PropertyType";
static const char * const NAME_KEY = "AddPropertyDialog/PropertyName";

AddPropertyDialog::AddPropertyDialog(const QString& type, QWidget *parent)
    : QDialog(parent),
      // JUMPARIO
      mType(type),
      mUi(new Ui::AddPropertyDialog)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif

    mUi->setupUi(this);
    resize(Utils::dpiScaled(size()));



    // JUMPARIO
    {
        QString defaultType = QStringLiteral("test");
        mUi->name->addItem(defaultType, defaultType);
        mUi->name->addItem(QStringLiteral("test"), QStringLiteral("test"));
        mUi->name->setCurrentText(defaultType);

        connect(mUi->name, &QComboBox::currentTextChanged,
                this, &AddPropertyDialog::nameChanged);
    }



    {
        QString stringType = typeToName(QVariant::String);

        // Add possible types from QVariant
        mUi->typeBox->addItem(typeToName(QVariant::Bool),    false);
        mUi->typeBox->addItem(typeToName(QVariant::Color),   QColor());
        mUi->typeBox->addItem(typeToName(QVariant::Double),  0.0);
        mUi->typeBox->addItem(typeToName(filePathTypeId()),  QVariant::fromValue(FilePath()));
        mUi->typeBox->addItem(typeToName(QVariant::Int),     0);
        mUi->typeBox->addItem(typeToName(objectRefTypeId()), QVariant::fromValue(ObjectRef()));
        mUi->typeBox->addItem(stringType,                    QString());
        mUi->typeBox->setCurrentText(stringType);

        connect(mUi->typeBox, &QComboBox::currentTextChanged,
                this, &AddPropertyDialog::typeChanged);
    }

    mUi->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

AddPropertyDialog::~AddPropertyDialog()
{
    delete mUi;
}

QString AddPropertyDialog::propertyName() const
{
    return mUi->name->currentData().toString();
}

QVariant AddPropertyDialog::propertyValue() const
{
    return mUi->typeBox->currentData();
}

void AddPropertyDialog::nameChanged(const QString &text)
{
}

void AddPropertyDialog::typeChanged(const QString &text)
{
}
