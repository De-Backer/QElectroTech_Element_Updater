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
	QXmlStreamReader* reader = new QXmlStreamReader(element);

	while (reader->readNextStartElement())
	{
		if (reader->name() == QLatin1String("definition"))
			read_definition(reader);
		else if (reader->name() == QLatin1String("uuid"))
			read_definition_uuid(reader);
		else if (reader->name() == "names")
			read_definition_name(reader);
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
			"XMLerror:" + reader->errorString().toStdString()
			+ " at lineNumber "
			+ QString::number(reader->lineNumber()).toStdString());
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
	QVariant data = definition_element.value(value, "error");
	if (data != "error") return data;
	qDebug() << "_____________________________________________________________";
	qWarning() << "!! exception !!" << __LINE__ << __FILE__;
	qDebug() << "value: " << value;
	throw std::invalid_argument("unknown value");
	return 0;
}

QMap<QString, QVariant> LoadElement::definition() { return definition_element; }

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

QVector<QMap<QString, QVariant>> LoadElement::description()
{
	return description_element;
}

void LoadElement::read_definition(QXmlStreamReader* reader)
{
	definition_element.insert(
		"version",
		reader->attributes().value("version").toString());
	definition_element.insert(
		"width",
		reader->attributes().value("width").toInt());
	definition_element.insert(
		"height",
		reader->attributes().value("height").toInt());
	definition_element.insert(
		"hotspot_x",
		reader->attributes().value("hotspot_x").toInt());
	definition_element.insert(
		"hotspot_y",
		reader->attributes().value("hotspot_y").toInt());
	definition_element.insert(
		"type",
		reader->attributes().value("type").toString());
	definition_element.insert(
		"link_type",
		reader->attributes().value("link_type").toString());
}

void LoadElement::read_definition_uuid(QXmlStreamReader* reader)
{
	Q_ASSERT(
		reader->isStartElement() && reader->name() == QLatin1String("uuid"));
	uuid_element =
		QUuid::fromString(reader->attributes().value("uuid").toString());
	reader->readNextStartElement();
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
	reader->readNextStartElement();
}

void LoadElement::read_definition_informations(QXmlStreamReader* reader)
{
	Q_ASSERT(
		reader->isStartElement()
		&& reader->name() == QLatin1String("informations"));
	informations_element = reader->readElementText();
	reader->readNextStartElement();
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
			read_PartCircle(reader);
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
			read_PartInput(reader);
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
	Q_ASSERT(
		reader->isStartElement() && reader->name() == QLatin1String("line"));
	QMap<QString, QVariant> var;
	var.insert("name", reader->name().toString());
	var.insert("x1", reader->attributes().value("x1").toInt());
	var.insert("y1", reader->attributes().value("y1").toInt());
	var.insert("x2", reader->attributes().value("x2").toInt());
	var.insert("y2", reader->attributes().value("y2").toInt());
	var.insert("length1", reader->attributes().value("length1").toDouble());
	var.insert("length2", reader->attributes().value("length2").toDouble());
	var.insert("end1", reader->attributes().value("end1").toString());
	var.insert("end2", reader->attributes().value("end2").toString());
	var.insert("style", reader->attributes().value("style").toString());
	var.insert("antialias", reader->attributes().value("antialias").toString());

	description_element.append(var);
	reader->readNextStartElement();
}

void LoadElement::read_PartRectangle(QXmlStreamReader* reader)
{
	Q_ASSERT(
		reader->isStartElement() && reader->name() == QLatin1String("rect"));
	QMap<QString, QVariant> var;
	var.insert("name", reader->name().toString());
	var.insert("x", reader->attributes().value("x").toInt());
	var.insert("y", reader->attributes().value("y").toInt());
	var.insert("height", reader->attributes().value("height").toDouble());
	var.insert("width", reader->attributes().value("width").toDouble());
	var.insert("style", reader->attributes().value("style").toString());
	var.insert("antialias", reader->attributes().value("antialias").toString());
	description_element.append(var);
	reader->readNextStartElement();
}

void LoadElement::read_PartEllipse(QXmlStreamReader* reader)
{
	// diameter
	Q_ASSERT(
		reader->isStartElement() && reader->name() == QLatin1String("ellipse"));
	QMap<QString, QVariant> var;
	var.insert("name", reader->name().toString());
	var.insert("x", reader->attributes().value("x").toInt());
	var.insert("y", reader->attributes().value("y").toInt());
	var.insert("height", reader->attributes().value("height").toDouble());
	var.insert("width", reader->attributes().value("width").toDouble());
	var.insert("style", reader->attributes().value("style").toString());
	var.insert("antialias", reader->attributes().value("antialias").toString());
	description_element.append(var);
	reader->readNextStartElement();
}

void LoadElement::read_PartCircle(QXmlStreamReader* reader)
{
	// diameter
	Q_ASSERT(
		reader->isStartElement() && reader->name() == QLatin1String("circle"));
	QMap<QString, QVariant> var;
	var.insert("name", reader->name().toString());
	var.insert("x", reader->attributes().value("x").toInt());
	var.insert("y", reader->attributes().value("y").toInt());
	var.insert("diameter", reader->attributes().value("diameter").toInt());
	var.insert("style", reader->attributes().value("style").toString());
	var.insert("antialias", reader->attributes().value("antialias").toString());
	description_element.append(var);
	reader->readNextStartElement();
}

void LoadElement::read_PartPolygon(QXmlStreamReader* reader)
{
	Q_ASSERT(
		reader->isStartElement() && reader->name() == QLatin1String("polygon"));
	QMap<QString, QVariant> var;
	var.insert("name", reader->name().toString());
	var.insert("style", reader->attributes().value("style").toString());
	var.insert("antialias", reader->attributes().value("antialias").toString());
	var.insert("closed", reader->attributes().value("closed").toString());
	int nr = 1;
	while (reader->attributes().hasAttribute(QString("x%1").arg(nr)))
	{
		var.insert(
			QString("x%1").arg(nr),
			reader->attributes().value(QString("x%1").arg(nr)).toInt());
		var.insert(
			QString("y%1").arg(nr),
			reader->attributes().value(QString("y%1").arg(nr)).toInt());
		++nr;
	}
	description_element.append(var);

	reader->readNextStartElement();
}

void LoadElement::read_PartTerminal(QXmlStreamReader* reader)
{
	Q_ASSERT(
		reader->isStartElement()
		&& reader->name() == QLatin1String("terminal"));
	QMap<QString, QVariant> var;
	var.insert("name", reader->name().toString());
	var.insert("x", reader->attributes().value("x").toInt());
	var.insert("y", reader->attributes().value("y").toInt());
	var.insert(
		"orientation",
		reader->attributes().value("orientation").toString());
	var.insert("number", reader->attributes().value("number").toInt());
	var.insert("terminalname", reader->attributes().value("name").toString());
	var.insert(
		"nameHidden",
		reader->attributes().value("nameHidden").toString());
	description_element.append(var);

	reader->readNextStartElement();
}

void LoadElement::read_PartText(QXmlStreamReader* reader)
{
	Q_ASSERT(
		reader->isStartElement() && reader->name() == QLatin1String("text"));
	QMap<QString, QVariant> var;
	var.insert("name", reader->name().toString());
	var.insert("x", reader->attributes().value("x").toInt());
	var.insert("y", reader->attributes().value("y").toInt());
	var.insert("rotation", reader->attributes().value("rotation").toInt());
	var.insert("font", reader->attributes().value("font").toString());
	var.insert("text", reader->attributes().value("text").toString());
	var.insert("color", reader->attributes().value("color").toString());
	description_element.append(var);

	reader->readNextStartElement();
}

void LoadElement::read_PartArc(QXmlStreamReader* reader)
{
	Q_ASSERT(
		reader->isStartElement() && reader->name() == QLatin1String("arc"));
	QMap<QString, QVariant> var;
	var.insert("name", reader->name().toString());
	var.insert("x", reader->attributes().value("x").toInt());
	var.insert("y", reader->attributes().value("y").toInt());
	var.insert("height", reader->attributes().value("height").toDouble());
	var.insert("width", reader->attributes().value("width").toDouble());
	var.insert("start", reader->attributes().value("start").toInt());
	var.insert("angle", reader->attributes().value("angle").toInt());
	var.insert("style", reader->attributes().value("style").toString());
	var.insert("antialias", reader->attributes().value("antialias").toString());
	description_element.append(var);
	reader->readNextStartElement();
}

void LoadElement::read_PartDynamicTextField(QXmlStreamReader* reader)
{
	Q_ASSERT(
		reader->isStartElement()
		&& reader->name() == QLatin1String("dynamic_text"));
	QMap<QString, QVariant> var;
	var.insert("name", reader->name().toString());
	var.insert("x", reader->attributes().value("x").toInt());
	var.insert("y", reader->attributes().value("y").toInt());
	var.insert("z", reader->attributes().value("z").toInt());
	var.insert("rotation", reader->attributes().value("rotation").toInt());
	var.insert("text_width", reader->attributes().value("text_width").toInt());
	var.insert("text_from", reader->attributes().value("text_from").toString());
	var.insert(
		"Valignment",
		reader->attributes().value("Valignment").toString());
	var.insert(
		"Halignment",
		reader->attributes().value("Halignment").toString());
	var.insert("font", reader->attributes().value("font").toString());
	var.insert("frame", reader->attributes().value("frame").toString());
	var.insert(
		"uuid",
		QUuid::fromString(reader->attributes().value("uuid").toString()));
	description_element.append(var);
	reader->readNextStartElement();
}

void LoadElement::read_PartInput(QXmlStreamReader* reader)
{
	Q_ASSERT(
		reader->isStartElement() && reader->name() == QLatin1String("input"));
	QMap<QString, QVariant> var;
	var.insert("name", reader->name().toString());
	var.insert("x", reader->attributes().value("x").toInt());
	var.insert("y", reader->attributes().value("y").toInt());
	var.insert("size", reader->attributes().value("size").toInt());
	var.insert("rotation", reader->attributes().value("rotation").toString());
	var.insert("text", reader->attributes().value("text").toString());
	description_element.append(var);
	reader->readNextStartElement();
}
