#include "loadelement.h"

#include <QDebug>
#include <QFile>
#include <QString>
#include <QXmlStreamReader>
#include <QtXml>

LoadElement::LoadElement(QString file)
{
	element = new QFile(file);
	if (! element->open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "element is not open";
		throw std::invalid_argument("element is not open");
		return;
	}
	if (! element->isReadable())
	{
		qDebug() << "element is not Readable";
		throw std::invalid_argument("element is not Readable");
		return;
	}
	Reader = new QXmlStreamReader(element);
	Reader->readNextStartElement();
	if (Reader->name() != "definition")
	{
		qDebug() << "element has not definition";
		throw std::invalid_argument("element has not definition");
		return;
	}
	if (Reader->attributes().value("version") == "0.3")
	{ LoadElement0_3_0(Reader); }
	else if (Reader->attributes().value("version") == "0.7")
	{
		LoadElement0_7_0(Reader);
	}
}

/**
 * @brief LoadElement::definition
 * @param value
 * @return
 */
QVariant LoadElement::definition(QString value)
{
	if (value == "width") return width;
	if (value == "height") return height;
	if (value == "hotspot_x") return hotspot_x;
	if (value == "hotspot_y") return hotspot_y;
	if (value == "type") return type;
	if (value == "link_type") return link_type;

	qDebug() << "value: " << value;
	throw std::invalid_argument("unknown value");
	return 0;
}

QUuid LoadElement::uuid() { return uuid_element; }

/**
 * @brief LoadElement::LoadElement0_3_0
 * @param element
 * loads the element and converts it to the next version
 */
void LoadElement::LoadElement0_3_0(QXmlStreamReader* reader)
{
	// definition
	width	  = reader->attributes().value("width").toInt();
	height	  = reader->attributes().value("height").toInt();
	hotspot_x = reader->attributes().value("hotspot_x").toInt();
	hotspot_y = reader->attributes().value("hotspot_y").toInt();
	type	  = reader->attributes().value("type").toString();
	link_type = reader->attributes().value("link_type").toString();

	// uuid
	Reader->readNextStartElement();
	if (Reader->name() != "uuid")
	{
		qDebug() << "element has not uuid";
		throw std::invalid_argument("element has not uuid");
		return;
	}
	uuid_element =
		QUuid::fromString(reader->attributes().value("uuid").toString());
}
void LoadElement::LoadElement0_7_0(QXmlStreamReader* reader)
{
	reader->attributes();
}
