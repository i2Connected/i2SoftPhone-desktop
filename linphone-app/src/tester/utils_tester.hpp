/*
 * Copyright (c) 2010-2023 Belledonne Communications SARL.
 *
 * This file is part of linphone-desktop
 * (see https://www.linphone.org).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 
 #include <QTest>

class AppController;

class UtilsTester: public QObject
{
    Q_OBJECT
   std::string app;
   char * appPtr;
   int argc = 1;
   QThread * mApplication;
   AppController * mController;
public:
	UtilsTester(AppController * controller);
	~UtilsTester();
	
private slots:
	void initTestCase();
	void cleanupTestCase();
    void test_osProduct();
    void test_register();
    void test_call();
    void test_call2();
};