#ifndef VIRTUALELEMENT_H
#define VIRTUALELEMENT_H

#include <QMap>
#include <QString>
#include <QUuid>
#include <QVariant>
#include <QVector>

class VElement
{
  public:
	VElement();
	VElement(
		QMap<QString, QVariant>			 definition,
		QUuid							 uuid,
		QMap<QString, QString>			 name,
		QMap<QString, QVector<QVariant>> kindInformation,
		QMap<QString, QVector<QVariant>> elementInformations,
		QString							 informations,
		QVector<QMap<QString, QVariant>> description);
	~VElement();

	VElement& operator=(const VElement& data);

	// get
	QMap<QString, QVariant>			 definition();
	QUuid							 uuid();
	QMap<QString, QString>			 name();
	QMap<QString, QVector<QVariant>> kindInformation();
	QMap<QString, QVector<QVariant>> elementInformations();
	QString							 informations();
	QVector<QMap<QString, QVariant>> description();

	// set
	void definition(QMap<QString, QVariant> data);
	void uuid(QUuid data);
	void name(QMap<QString, QString> data);
	void kindInformation(QMap<QString, QVector<QVariant>> data);
	void elementInformations(QMap<QString, QVector<QVariant>> data);
	void informations(QString data);
	void description(QVector<QMap<QString, QVariant>> data);

  private:
	QMap<QString, QVariant>			 Definition;
	QUuid							 Uuid;
	QMap<QString, QString>			 Name;
	QMap<QString, QVector<QVariant>> KindInformation;
	QMap<QString, QVector<QVariant>> ElementInformations;
	QString							 Informations;
	QVector<QMap<QString, QVariant>> Description;
};

#endif // VIRTUALELEMENT_H
