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
	QVariant						 definition(QString value);
	QVector<QVariant>				 definition();
	QUuid							 uuid();
	QString							 name(QString language);
	QMap<QString, QString>			 name();
	QMap<QString, QVector<QVariant>> kindInformation();
	QString							 informations();
	QVector<QMap<QString, QVariant>> description();

  private:
	// definition
	int		width	  = 0;
	int		height	  = 0;
	int		hotspot_x = 0;
	int		hotspot_y = 0;
	QString type;
	QString link_type;
	// uuid
	QUuid uuid_element = QUuid::createUuid();
	// name
	QMap<QString, QString> name_element;
	// kindInformation
	QMap<QString, QVector<QVariant>>
		kindInformation_element; // name, show, text
	// informations_element
	QString informations_element;
	QVector<QMap<QString, QVariant>> description_element;
	QFile*	element;

	void LoadElement0_22(QXmlStreamReader* reader);
	void LoadElement0_3(QXmlStreamReader* reader);
	void LoadElement0_4(QXmlStreamReader* reader);
	void LoadElement0_5(QXmlStreamReader* reader);
	void LoadElement0_60(QXmlStreamReader* reader);
	void LoadElement0_70(QXmlStreamReader* reader);
	void LoadElement0_80(QXmlStreamReader* reader);

	void read_definition(QXmlStreamReader* reader);
	void read_definition_uuid(QXmlStreamReader* reader);
	void read_definition_name(QXmlStreamReader* reader);
	void read_definition_kindInformation(QXmlStreamReader* reader);
	void read_definition_informations(QXmlStreamReader* reader);
	void read_definition_description(QXmlStreamReader* reader);

	void read_PartLine(QXmlStreamReader* reader);
	void read_PartRectangle(QXmlStreamReader* reader);
	void read_PartEllipse(QXmlStreamReader* reader);
	void read_PartPolygon(QXmlStreamReader* reader);
	void read_PartTerminal(QXmlStreamReader* reader);
	void read_PartText(QXmlStreamReader* reader);
	void read_PartArc(QXmlStreamReader* reader);
	void read_PartDynamicTextField(QXmlStreamReader* reader);
};

#endif // LOADELEMENT_H
