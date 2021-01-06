#ifndef LOADELEMENT_H
#define LOADELEMENT_H

#include <QFile>
#include <QMap>
#include <QString>
#include <QUuid>
#include <QVariant>
#include <QVector>
#include <QXmlStreamReader>

class LoadElement
{
  public:
	LoadElement(QString file);
	~LoadElement();
	[[deprecated(
		"Replaced by definition(), which has an QMap interface")]] QVariant
							definition(QString value);
	QMap<QString, QVariant> definition();
	QUuid					uuid();
	[[deprecated("Replaced by name(), which has an QMap interface")]] QString
									 name(QString language);
	QMap<QString, QString>			 name();
	QMap<QString, QVector<QVariant>> kindInformation();
	QMap<QString, QVector<QVariant>> elementInformations();
	QString							 informations();
	QVector<QMap<QString, QVariant>> description();

  private:
	QUuid							 uuid_element; //= QUuid::createUuid();
	QMap<QString, QVariant>			 definition_element;
	QMap<QString, QString>			 name_element;
	QMap<QString, QVector<QVariant>> kindInformation_element;
	QMap<QString, QVector<QVariant>> elementInformations_element;
	QString							 informations_element;
	QVector<QMap<QString, QVariant>> description_element;

	void read_definition(QXmlStreamReader* reader);
	void read_definition_uuid(QXmlStreamReader* reader);
	void read_definition_name(QXmlStreamReader* reader);
	void read_definition_kindInformation(QXmlStreamReader* reader);
	void read_definition_elementInformations(QXmlStreamReader* reader);
	void read_definition_informations(QXmlStreamReader* reader);
	void read_definition_description(QXmlStreamReader* reader);

	void read_PartLine(QXmlStreamReader* reader);
	void read_PartRectangle(QXmlStreamReader* reader);
	void read_PartEllipse(QXmlStreamReader* reader);
	void read_PartCircle(QXmlStreamReader* reader);
	void read_PartPolygon(QXmlStreamReader* reader);
	void read_PartTerminal(QXmlStreamReader* reader);
	void read_PartText(QXmlStreamReader* reader);
	void read_PartArc(QXmlStreamReader* reader);
	void read_PartDynamicTextField(QXmlStreamReader* reader);
	void read_PartInput(QXmlStreamReader* reader);
};

#endif // LOADELEMENT_H
