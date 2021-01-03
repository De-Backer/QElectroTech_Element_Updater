#include "safeelement.h"

#include <QDebug>
#include <QFile>
#include <QMap>

SafeElement::SafeElement(QString outputfile, VElement element)
{
	element_data = element;

	file = new QFile(outputfile);
	if (! file->open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "file is not open";
		throw std::invalid_argument("file is not open");
		return;
	}
	if (! file->isWritable())
	{
		qDebug() << "file is not Writable";
		throw std::invalid_argument("file is not Writable");
		return;
	}
	QXmlStreamWriter* writer = new QXmlStreamWriter(file);
	writer->setAutoFormatting(true);
	writer->writeStartDocument();
	write_definition(writer);
	writer->writeEndDocument();
}

SafeElement::~SafeElement() {}

void SafeElement::write_definition(QXmlStreamWriter* writer)
{
	writer->writeStartElement("definition");
	QMapIterator<QString, QVariant> var(element_data.definition());
	while (var.hasNext())
	{
		var.next();
		writer->writeAttribute(var.key(), var.value().toString());
	}
	write_definition_uuid(writer);
	write_definition_name(writer);
	write_definition_kindInformation(writer);
	write_definition_elementInformations(writer);
	write_definition_informations(writer);
	write_definition_description(writer);
	writer->writeEndElement(); // definition
}

void SafeElement::write_definition_uuid(QXmlStreamWriter* writer)
{
	writer->writeStartElement("uuid");
	writer->writeAttribute("uuid", element_data.uuid().toString());
	writer->writeEndElement(); // uuid
}

void SafeElement::write_definition_name(QXmlStreamWriter* writer)
{
	writer->writeStartElement("names");
	QMapIterator<QString, QString> var(element_data.name());
	while (var.hasNext())
	{
		var.next();
		writer->writeStartElement("name");
		writer->writeAttribute("lang", var.key());
		writer->writeCharacters(var.value());
		writer->writeEndElement(); // name
	}
	writer->writeEndElement(); // names
}

void SafeElement::write_definition_kindInformation(QXmlStreamWriter* writer)
{
	writer->writeStartElement("kindInformations");
	QMapIterator<QString, QVector<QVariant>> var(
		element_data.kindInformation());
	while (var.hasNext())
	{
		var.next();
		writer->writeStartElement("kindInformation");
		writer->writeAttribute("name", var.key());
		writer->writeAttribute("show", var.value().at(0).toString());
		writer->writeCharacters(var.value().at(1).toString());
		writer->writeEndElement(); // kindInformation
	}
	writer->writeEndElement(); // kindInformations
}

void SafeElement::write_definition_elementInformations(QXmlStreamWriter* writer)
{
	writer->writeStartElement("elementInformations");
	QMapIterator<QString, QVector<QVariant>> var(
		element_data.elementInformations());
	while (var.hasNext())
	{
		var.next();
		writer->writeStartElement("elementInformation");
		writer->writeAttribute("name", var.key());
		writer->writeAttribute("show", var.value().at(0).toString());
		writer->writeCharacters(var.value().at(1).toString());
		writer->writeEndElement(); // elementInformation
	}
	writer->writeEndElement(); // elementInformations
}

void SafeElement::write_definition_informations(QXmlStreamWriter* writer)
{
	writer->writeStartElement("informations");
	writer->writeCharacters(element_data.informations());
	writer->writeEndElement(); // informations
}

void SafeElement::write_definition_description(QXmlStreamWriter* writer)
{
	writer->writeStartElement("description");
	write_PartLine(writer);
	write_PartRectangle(writer);
	write_PartCircle(writer);
	write_PartEllipse(writer);
	write_PartPolygon(writer);
	write_PartArc(writer);
	write_PartDynamicTextField(writer);
	write_PartTerminal(writer);
	writer->writeEndElement(); // description
}

void SafeElement::write_PartLine(QXmlStreamWriter* writer)
{
	QMap<QString, QVariant> var;
	var.insert("name", "line");
	qDebug() << "write_PartLine" << element_data.description().indexOf(var);
	writer->writeComment("line");
}

void SafeElement::write_PartRectangle(QXmlStreamWriter* writer)
{
	QMap<QString, QVariant> var;
	var.insert("name", "rect");
	qDebug() << "write_PartRectangle"
			 << element_data.description().indexOf(var);
	writer->writeComment("rect");
}

void SafeElement::write_PartEllipse(QXmlStreamWriter* writer)
{
	QMap<QString, QVariant> var;
	var.insert("name", "ellipse");
	qDebug() << "write_PartEllipse" << element_data.description().indexOf(var);
	writer->writeComment("ellipse");
}

void SafeElement::write_PartCircle(QXmlStreamWriter* writer)
{
	QMap<QString, QVariant> var;
	var.insert("name", "circle");
	qDebug() << "write_PartCircle" << element_data.description().indexOf(var);
	writer->writeComment("circle");
}

void SafeElement::write_PartPolygon(QXmlStreamWriter* writer)
{
	QMap<QString, QVariant> var;
	var.insert("name", "polygon");
	qDebug() << "write_PartPolygon" << element_data.description().indexOf(var);
	writer->writeComment("polygon");
}

void SafeElement::write_PartTerminal(QXmlStreamWriter* writer)
{
	QMap<QString, QVariant> var;
	var.insert("name", "terminal");
	qDebug() << "write_PartTerminal" << element_data.description().indexOf(var);
	writer->writeComment("terminal");
}

void SafeElement::write_PartText(QXmlStreamWriter* writer)
{
	QMap<QString, QVariant> var;
	var.insert("name", "text");
	qDebug() << "write_PartText" << element_data.description().indexOf(var);
	writer->writeComment("text");
}

void SafeElement::write_PartArc(QXmlStreamWriter* writer)
{
	QMap<QString, QVariant> var;
	var.insert("name", "arc");
	qDebug() << "write_PartArc" << element_data.description().indexOf(var);
	writer->writeComment("arc");
}

void SafeElement::write_PartDynamicTextField(QXmlStreamWriter* writer)
{
	QMap<QString, QVariant> var;
	var.insert("name", "dynamic_text");
	qDebug() << "write_PartDynamicTextField"
			 << element_data.description().indexOf(var);
	writer->writeComment("dynamic_text");
}
