#include "virtualelement.h"

#include <QDebug>

VElement::VElement() {}

VElement::VElement(
	QMap<QString, QVariant>			 definition,
	QUuid							 uuid,
	QMap<QString, QString>			 name,
	QMap<QString, QVector<QVariant>> kindInformation,
	QMap<QString, QVector<QVariant>> elementInformations,
	QString							 informations,
	QVector<QMap<QString, QVariant>> description)
{
	Definition			= definition;
	Uuid				= uuid;
	Name				= name;
	KindInformation		= kindInformation;
	ElementInformations = elementInformations;
	Informations		= informations;
	Description			= description;
}

VElement::~VElement() {}

VElement& VElement::operator=(const VElement& data)
{
	Definition			= data.Definition;
	Uuid				= data.Uuid;
	Name				= data.Name;
	KindInformation		= data.KindInformation;
	ElementInformations = data.ElementInformations;
	Informations		= data.Informations;
	Description			= data.Description;

	return (*this);
}

QMap<QString, QVariant>			 VElement::definition() { return Definition; }
QUuid							 VElement::uuid() { return Uuid; }
QMap<QString, QString>			 VElement::name() { return Name; }
QMap<QString, QVector<QVariant>> VElement::kindInformation()
{
	return KindInformation;
}
QMap<QString, QVector<QVariant>> VElement::elementInformations()
{
	return ElementInformations;
}
QString VElement::informations() { return Informations; }
QVector<QMap<QString, QVariant>> VElement::description() { return Description; }

void VElement::definition(QMap<QString, QVariant> data) { Definition = data; }
void VElement::uuid(QUuid data) { Uuid = data; }
void VElement::name(QMap<QString, QString> data) { Name = data; }
void VElement::kindInformation(QMap<QString, QVector<QVariant>> data)
{
	KindInformation = data;
}
void VElement::elementInformations(QMap<QString, QVector<QVariant>> data)
{
	ElementInformations = data;
}
void VElement::informations(QString data) { Informations = data; }
void VElement::description(QVector<QMap<QString, QVariant>> data)
{
	Description = data;
}
