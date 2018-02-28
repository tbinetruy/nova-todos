/** OrgModeParser - a parser for Emacs Org Mode files, written in C++.
    Copyright (C) 2015 Mirko Boehm

    This file is part of OrgModeParser.
    OrgModeParser is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, version 3 of the
    License.

    OrgModeParser is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    See the GNU General Public License for more details. You should
    have received a copy of the GNU General Public License along with
    OrgModeParser. If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include "todos.h"

using namespace OrgMode;
using namespace std;

QList<QSharedPointer<Headline>> main2(QString inputFile, QString todoState)
{
    Parser parser;
    QFile input(inputFile);
    if (!input.open(QIODevice::ReadOnly)) {
        wcerr << "Unable to open file" << inputFile.toStdWString() << "!" << endl;
    }
    QTextStream stream(&input);
    OrgElement::Pointer orgfile = parser.parse(&stream, inputFile);
    auto const headlines = findElements<Headline>(orgfile);
    wcout << "Number of headlines: " << headlines.count() << endl;
    auto isTODO = [&](const Headline::Pointer& element) {
      return element->caption().startsWith(todoState);
    };

    auto const todos = findElements<Headline>(orgfile, isTODO);
    wcout << "Number of TODOs: " << todos.count() << endl;

    return todos;
}
