#include "loadelement.h"

#include <QDebug>
#include <QFile>
#include <QString>
#include <QXmlStreamReader>
#include <QtXml>

LoadElement::LoadElement(QString file)
{
	qDebug() << this << file;
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

	qDebug() << "_____________________________________________________________";
	qWarning() << "!! exception !!" << __LINE__ << __FILE__;
	qDebug() << "value: " << value;
	throw std::invalid_argument("unknown value");
	return 0;
}

QVector<QVariant> LoadElement::definition()
{
	QVector<QVariant> var;
	var.append(width);
	var.append(height);
	var.append(hotspot_x);
	var.append(hotspot_y);
	var.append(type);
	var.append(link_type);
	return var;
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

QMap<QString, QString> LoadElement::name() { return name_element; }

QMap<QString, QVector<QVariant>> LoadElement::kindInformation()
{
	return kindInformation_element;
}

QString LoadElement::informations() { return informations_element; }

QVector<QVector<QVariant>> LoadElement::description()
{
	return description_element;
}

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
		else if (reader->name() == QLatin1String("kindInformations"))
			read_definition_kindInformation(reader);
		else if (reader->name() == QLatin1String("description"))
			read_definition_description(reader);
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
	LoadElement0_3(reader);
}

void LoadElement::LoadElement0_5(QXmlStreamReader* reader)
{
	LoadElement0_3(reader);
}

void LoadElement::LoadElement0_60(QXmlStreamReader* reader)
{
	LoadElement0_3(reader);
}

void LoadElement::LoadElement0_70(QXmlStreamReader* reader)
{
	LoadElement0_3(reader);
}

void LoadElement::LoadElement0_80(QXmlStreamReader* reader)
{
	LoadElement0_3(reader);
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
	Q_ASSERT(
		reader->isStartElement()
		&& reader->name() == QLatin1String("description"));
	while (reader->readNextStartElement())
	{
		if (reader->name() == "line") { read_PartLine(reader); }
		else if (reader->name() == QLatin1String("rect"))
			read_PartRectangle(reader);
		else if (reader->name() == QLatin1String("ellipse"))
			read_PartEllipse(reader);
		else if (reader->name() == QLatin1String("circle"))
			read_PartEllipse(reader);
		else if (reader->name() == QLatin1String("polygon"))
			read_PartPolygon(reader);
		else if (reader->name() == QLatin1String("terminal"))
			read_PartTerminal(reader);
		else if (reader->name() == QLatin1String("text"))
			read_PartText(reader);
		else if (reader->name() == QLatin1String("arc"))
			read_PartArc(reader);
		else if (reader->name() == QLatin1String("dynamic_text"))
			read_PartDynamicTextField(reader);
		else if (reader->name() == QLatin1String("input"))
			read_PartDynamicTextField(reader);
		else
			reader->skipCurrentElement();
	}
	if (reader->hasError())
	{
		throw std::invalid_argument(
			"XMLerror:" + reader->errorString().toStdString());
	}
}

void LoadElement::read_PartLine(QXmlStreamReader* reader)
{
	//	Q_ASSERT(
	//		reader->isStartElement() && reader->name() ==
	// QLatin1String("line"));
	// 0 line
	// 1 x1="-5"
	// 2 y1="13"
	// 3 x2="4"
	// 4 y2="20"
	// 5 length1="1.5"
	// 6 length2="1.5"
	// 7 end1="none"
	// 8 end2="none"
	// 9 style="line-style:normal;line-weight:thin;filling:none;color:black"
	// 10 antialias="false"
	QVector<QVariant> var(1, reader->name().toString());
	var.append(reader->attributes().value("x1").toInt());
	var.append(reader->attributes().value("y1").toInt());
	var.append(reader->attributes().value("x2").toInt());
	var.append(reader->attributes().value("y2").toInt());
	var.append(reader->attributes().value("length1").toDouble());
	var.append(reader->attributes().value("length2").toDouble());
	var.append(reader->attributes().value("end1").toString());
	var.append(reader->attributes().value("end2").toString());
	var.append(reader->attributes().value("style").toString());
	var.append(reader->attributes().value("antialias").toString());

	description_element.append(var);
	reader->readNextStartElement();
}

void LoadElement::read_PartRectangle(QXmlStreamReader* reader)
{
	reader->attributes().value("length1");
	reader->readNextStartElement();
}

void LoadElement::read_PartEllipse(QXmlStreamReader* reader)
{
	reader->attributes().value("length1");
	reader->readNextStartElement();
}

void LoadElement::read_PartPolygon(QXmlStreamReader* reader)
{
	reader->attributes().value("length1");
	reader->readNextStartElement();
}

void LoadElement::read_PartTerminal(QXmlStreamReader* reader)
{
	reader->attributes().value("length1");
	reader->readNextStartElement();
}

void LoadElement::read_PartText(QXmlStreamReader* reader)
{
	reader->attributes().value("length1");
	reader->readNextStartElement();
}

void LoadElement::read_PartArc(QXmlStreamReader* reader)
{
	reader->attributes().value("length1");
	reader->readNextStartElement();
}

void LoadElement::read_PartDynamicTextField(QXmlStreamReader* reader)
{
	reader->attributes().value("length1");
	reader->readNextStartElement();
}
