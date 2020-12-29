#include "loadelement.h"

#include <QUuid>
#include <QtDebug>
#include <catch2/catch.hpp>
#include <exception>

TEST_CASE("LoadElement 0.3.0", "0.3.0")
{
	try
	{
		LoadElement mytest(TEST_CATCH_PATH "/testfile_0_3_0.elmt");
		CHECK(10 == mytest.definition("width").toInt());
		CHECK(30 == mytest.definition("height").toInt());
		CHECK(5 == mytest.definition("hotspot_x").toInt());
		CHECK(0 == mytest.definition("hotspot_y").toInt());
		CHECK("element" == mytest.definition("type").toString().toStdString());
		// no link_type
		// Todo wat moet dit zijn def?
		CHECK("" == mytest.definition("link_type").toString().toStdString());
		// no version in definition but in file => version="0.3"
		// Todo wat moet dit zijn?
		REQUIRE_THROWS_WITH(mytest.definition("version"), "unknown value");

		// Todo een beter manier vinden voor random waarden
		REQUIRE_THROWS_WITH(mytest.definition("definition"), "unknown value");
		REQUIRE_THROWS_WITH(mytest.definition("name"), "unknown value");
		REQUIRE_THROWS_WITH(mytest.definition("description"), "unknown value");

		// uuid
		CHECK(
			QUuid("0EE598EC-C72A-43A3-B330-741E2D41940A")
				.toString()
				.toStdString()
			== mytest.uuid().toString().toStdString());

		// name
		CHECK(
			"قابس و مقبس متعدد الأقطاب, تمثيل أحادي الخط"
			== mytest.name("ar").toStdString());
		CHECK(
			"Steckverbindung komplett mit 6 Kontakten"
			== mytest.name("de").toStdString());
		CHECK(
			"Plug and multipolar representation\nunifilar"
			== mytest.name("en").toStdString());
		CHECK(
			"Spina e presa multipolari, rappresentazione unifilare"
			== mytest.name("it").toStdString());
		CHECK(
			"Prise et fiche multipolaires, représentation\nunifilaire\n"
			== mytest.name("fr").toStdString());
		CHECK("Złącze wielostykowe" == mytest.name("pl").toStdString());
		CHECK(
			"Conector multipolar, representación unifilar"
			== mytest.name("es").toStdString());
		CHECK(
			"Zásuvka a zástrčka vícepólová, v jednopólovém znázornění"
			== mytest.name("cs").toStdString());
		CHECK(
			"Steker en Contact veelpolig enkellijns"
			== mytest.name("nl").toStdString());

		// test defkey en
		CHECK(
			"Plug and multipolar representation\nunifilar"
			== mytest.name("ww").toStdString());

		// informations
		CHECK("EN 60617: 03-03-08" == mytest.informations().toStdString());
	}
	catch (std::exception& e)
	{
		CHECK(0 == e.what()); // what is exception?
	}
}
