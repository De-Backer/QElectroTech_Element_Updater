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
	QXmlStreamReader* Reader = new QXmlStreamReader(element);
	Reader->readNextStartElement();
	if (Reader->name() != "definition")
	{
		qDebug() << "element has not definition";
		throw std::invalid_argument("element has not definition");
		return;
	}
	if (Reader->attributes().value("version") == "0.22")
	{ LoadElement0_22(Reader); }
	else if (Reader->attributes().value("version") == "0.3")
	{
		LoadElement0_3(Reader);
	}
	else if (Reader->attributes().value("version") == "0.4")
	{
		LoadElement0_4(Reader);
	}
	else if (Reader->attributes().value("version") == "0.5")
	{
		LoadElement0_5(Reader);
	}
	else if (Reader->attributes().value("version") == "0.60")
	{
		LoadElement0_60(Reader);
	}
	else if (Reader->attributes().value("version") == "0.70")
	{
		LoadElement0_70(Reader);
	}
	else if (Reader->attributes().value("version") == "0.80")
	{
		LoadElement0_80(Reader);
	}
}

LoadElement::~LoadElement()
{
	element->close();
	element->deleteLater();
	delete element;
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
 * @brief LoadElement::name
 * @param language
 * @return
 */
QString LoadElement::name(QString language)
{
	QString defkey = name_element.value("en", "error");
	return name_element.value(language, defkey);
}

QString LoadElement::informations() { return informations_element; }

void LoadElement::LoadElement0_22(QXmlStreamReader* reader)
{
	// definition
	width	  = reader->attributes().value("width").toInt();
	height	  = reader->attributes().value("height").toInt();
	hotspot_x = reader->attributes().value("hotspot_x").toInt();
	hotspot_y = reader->attributes().value("hotspot_y").toInt();
	type	  = reader->attributes().value("type").toString();
	link_type = ""; //?

	// uuid
	reader->readNextStartElement();
	if (reader->name() != "uuid")
	{
		qDebug() << "element has not uuid";
		throw std::invalid_argument("element has not uuid");
		return;
	}
	uuid_element =
		QUuid::fromString(reader->attributes().value("uuid").toString());
}

/**
 * @brief LoadElement::LoadElement0_3
 * @param element
 * loads the element and converts it to the next version
 */
void LoadElement::LoadElement0_3(QXmlStreamReader* reader)
{
	// definition
	if (reader->name() == QLatin1String("definition")) read_definition(reader);

	while (reader->readNextStartElement())
	{
		if (reader->name() == QLatin1String("uuid"))
			read_definition_uuid(reader);
		else
			reader->skipCurrentElement();
	}

	while (reader->readNextStartElement())
	{
		if (reader->name() == "names") { read_definition_name(reader); }
		else if (reader->name() == QLatin1String("informations"))
			read_definition_informations(reader);
		else
			reader->skipCurrentElement();
	}

	if (reader->hasError())
	{
		throw std::invalid_argument(
			"XMLerror:" + reader->errorString().toStdString());
	}
}

void LoadElement::LoadElement0_4(QXmlStreamReader* reader)
{
	reader->attributes();
}

void LoadElement::LoadElement0_5(QXmlStreamReader* reader)
{
	reader->attributes();
}

void LoadElement::LoadElement0_60(QXmlStreamReader* reader)
{
	reader->attributes();
}

void LoadElement::LoadElement0_70(QXmlStreamReader* reader)
{
	reader->attributes();
}

void LoadElement::LoadElement0_80(QXmlStreamReader* reader)
{
	reader->attributes();
}

void LoadElement::read_definition(QXmlStreamReader* reader)
{
	width	  = reader->attributes().value("width").toInt();
	height	  = reader->attributes().value("height").toInt();
	hotspot_x = reader->attributes().value("hotspot_x").toInt();
	hotspot_y = reader->attributes().value("hotspot_y").toInt();
	type	  = reader->attributes().value("type").toString();
	link_type = reader->attributes().value("link_type").toString();
}

void LoadElement::read_definition_uuid(QXmlStreamReader* reader)
{
	Q_ASSERT(
		reader->isStartElement() && reader->name() == QLatin1String("uuid"));
	uuid_element =
		QUuid::fromString(reader->attributes().value("uuid").toString());
}

void LoadElement::read_definition_name(QXmlStreamReader* reader)
{
	Q_ASSERT(
		reader->isStartElement() && reader->name() == QLatin1String("names"));
	reader->readNextStartElement();
	Q_ASSERT(
		reader->isStartElement() && reader->name() == QLatin1String("name"));

	while (reader->name() == "name")
	{
		QString key, value;

		key	  = reader->attributes().value("lang").toString();
		value = reader->readElementText();
		name_element.insert(key, value);

		reader->readNextStartElement();
	}
}

void LoadElement::read_definition_kindInformation(QXmlStreamReader* reader)
{
	reader->attributes();
}

void LoadElement::read_definition_informations(QXmlStreamReader* reader)
{
	Q_ASSERT(
		reader->isStartElement()
		&& reader->name() == QLatin1String("informations"));
	informations_element = reader->readElementText();
}

void LoadElement::read_definition_description(QXmlStreamReader* reader)
{
	reader->attributes();
}
