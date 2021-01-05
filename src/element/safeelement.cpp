#include "safeelement.h"

#include <QDebug>
#include <QFile>
#include <QMap>

SafeElement::SafeElement(QString outputfile, VElement element)
{
	element_data = element;
	qDebug() << "----- SafeElement ";
	qDebug() << element.definition();
	qDebug() << element_data.definition();
	qDebug() << element_data.description();
	qDebug() << element_data.elementInformations();
	qDebug() << element_data.informations();
	qDebug() << element_data.kindInformation();
	qDebug() << element_data.name();
	qDebug() << element_data.uuid();
	qDebug() << " SafeElement ----- ";

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
	writer->writeComment("note: this is still in the testing phase!");
	write_definition(writer);
	writer->writeComment("note: this is still in the testing phase!");
	writer->writeEndDocument();
	file->close();
}

SafeElement::~SafeElement()
{
	// file->close();
	//	file->deleteLater();
	//	delete file;
}

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
	writer->writeComment("line");
	for (int var = 0; var < element_data.description().size(); ++var)
	{
		if (element_data.description()
				.at(var)
				.value("XML_ElementName")
				.toString()
			== "line")
		{
			qDebug() << "write_PartLine" << element_data.description().at(var);
			writer->writeStartElement(element_data.description()
										  .at(var)
										  .value("XML_ElementName")
										  .toString());
			QMapIterator<QString, QVariant> data(
				element_data.description().at(var));
			while (data.hasNext())
			{
				data.next();
				if (data.key() != "XML_ElementName")
					writer->writeAttribute(data.key(), data.value().toString());
			}
			writer->writeEndElement();
		}
	}
}

void SafeElement::write_PartRectangle(QXmlStreamWriter* writer)
{
	writer->writeComment("rect");
	for (int var = 0; var < element_data.description().size(); ++var)
	{
		if (element_data.description()
				.at(var)
				.value("XML_ElementName")
				.toString()
			== "rect")
		{
			qDebug() << "write_Partrect" << element_data.description().at(var);
			writer->writeStartElement(element_data.description()
										  .at(var)
										  .value("XML_ElementName")
										  .toString());
			QMapIterator<QString, QVariant> data(
				element_data.description().at(var));
			while (data.hasNext())
			{
				data.next();
				if (data.key() != "XML_ElementName")
					writer->writeAttribute(data.key(), data.value().toString());
			}
			writer->writeEndElement();
		}
	}
}

void SafeElement::write_PartEllipse(QXmlStreamWriter* writer)
{
	writer->writeComment("ellipse");
	for (int var = 0; var < element_data.description().size(); ++var)
	{
		if (element_data.description()
				.at(var)
				.value("XML_ElementName")
				.toString()
			== "ellipse")
		{
			qDebug() << "write_PartEllipse"
					 << element_data.description().at(var);
			writer->writeStartElement(element_data.description()
										  .at(var)
										  .value("XML_ElementName")
										  .toString());
			QMapIterator<QString, QVariant> data(
				element_data.description().at(var));
			while (data.hasNext())
			{
				data.next();
				if (data.key() != "XML_ElementName")
					writer->writeAttribute(data.key(), data.value().toString());
			}
			writer->writeEndElement();
		}
	}
}

void SafeElement::write_PartCircle(QXmlStreamWriter* writer)
{
	writer->writeComment("circle");
	for (int var = 0; var < element_data.description().size(); ++var)
	{
		if (element_data.description()
				.at(var)
				.value("XML_ElementName")
				.toString()
			== "circle")
		{
			qDebug() << "write_PartCircle"
					 << element_data.description().at(var);
			writer->writeStartElement(element_data.description()
										  .at(var)
										  .value("XML_ElementName")
										  .toString());
			QMapIterator<QString, QVariant> data(
				element_data.description().at(var));
			while (data.hasNext())
			{
				data.next();
				if (data.key() != "XML_ElementName")
					writer->writeAttribute(data.key(), data.value().toString());
			}
			writer->writeEndElement();
		}
	}
}

void SafeElement::write_PartPolygon(QXmlStreamWriter* writer)
{
	writer->writeComment("polygon");
	for (int var = 0; var < element_data.description().size(); ++var)
	{
		if (element_data.description()
				.at(var)
				.value("XML_ElementName")
				.toString()
			== "polygon")
		{
			qDebug() << "write_PartPolygon"
					 << element_data.description().at(var);
			writer->writeStartElement(element_data.description()
										  .at(var)
										  .value("XML_ElementName")
										  .toString());
			QMapIterator<QString, QVariant> data(
				element_data.description().at(var));
			while (data.hasNext())
			{
				data.next();
				if (data.key() != "XML_ElementName")
					writer->writeAttribute(data.key(), data.value().toString());
			}
			writer->writeEndElement();
		}
	}
}

void SafeElement::write_PartTerminal(QXmlStreamWriter* writer)
{
	writer->writeComment("terminal");
	for (int var = 0; var < element_data.description().size(); ++var)
	{
		if (element_data.description()
				.at(var)
				.value("XML_ElementName")
				.toString()
			== "terminal")
		{
			qDebug() << "write_PartTerminal"
					 << element_data.description().at(var);
			writer->writeStartElement(element_data.description()
										  .at(var)
										  .value("XML_ElementName")
										  .toString());
			QMapIterator<QString, QVariant> data(
				element_data.description().at(var));
			while (data.hasNext())
			{
				data.next();
				if (data.key() != "XML_ElementName")
					writer->writeAttribute(data.key(), data.value().toString());
			}
			writer->writeEndElement();
		}
	}
}

void SafeElement::write_PartText(QXmlStreamWriter* writer)
{
	writer->writeComment("text");
	for (int var = 0; var < element_data.description().size(); ++var)
	{
		if (element_data.description()
				.at(var)
				.value("XML_ElementName")
				.toString()
			== "text")
		{
			qDebug() << "write_PartText" << element_data.description().at(var);
			writer->writeStartElement(element_data.description()
										  .at(var)
										  .value("XML_ElementName")
										  .toString());
			QMapIterator<QString, QVariant> data(
				element_data.description().at(var));
			while (data.hasNext())
			{
				data.next();
				if (data.key() != "XML_ElementName")
					writer->writeAttribute(data.key(), data.value().toString());
			}
			writer->writeEndElement();
		}
	}
}

void SafeElement::write_PartArc(QXmlStreamWriter* writer)
{
	writer->writeComment("arc");
	for (int var = 0; var < element_data.description().size(); ++var)
	{
		if (element_data.description()
				.at(var)
				.value("XML_ElementName")
				.toString()
			== "arc")
		{
			qDebug() << "write_PartArc" << element_data.description().at(var);
			writer->writeStartElement(element_data.description()
										  .at(var)
										  .value("XML_ElementName")
										  .toString());
			QMapIterator<QString, QVariant> data(
				element_data.description().at(var));
			while (data.hasNext())
			{
				data.next();
				if (data.key() != "XML_ElementName")
					writer->writeAttribute(data.key(), data.value().toString());
			}
			writer->writeEndElement();
		}
	}
}

void SafeElement::write_PartDynamicTextField(QXmlStreamWriter* writer)
{
	writer->writeComment("dynamic_text");
	for (int var = 0; var < element_data.description().size(); ++var)
	{
		if (element_data.description()
				.at(var)
				.value("XML_ElementName")
				.toString()
			== "dynamic_text")
		{
			qDebug() << "write_PartDynamicTextField"
					 << element_data.description().at(var);
			writer->writeStartElement(element_data.description()
										  .at(var)
										  .value("XML_ElementName")
										  .toString());
			QMapIterator<QString, QVariant> data(
				element_data.description().at(var));
			while (data.hasNext())
			{
				data.next();
				if (data.key() != "XML_ElementName" && data.key() != "text"
					&& data.key() != "info_name")
					writer->writeAttribute(data.key(), data.value().toString());
			}
			{
				writer->writeStartElement("text");
				writer->writeCharacters(element_data.description()
											.at(var)
											.value("text")
											.toString());
				writer->writeEndElement();
			}
			{
				writer->writeStartElement("info_name");
				writer->writeCharacters(element_data.description()
											.at(var)
											.value("info_name")
											.toString());
				writer->writeEndElement();
			}

			writer->writeEndElement();
		}
	}
}
