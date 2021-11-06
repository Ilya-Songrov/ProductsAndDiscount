/**************************************************************************
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/.
**
**************************************************************************/

#include "invoice.h"

Invoice::Invoice()
{

}

void Invoice::appendLine(const Line &line)
{
    listLines.append(line);
}

void Invoice::appendLines(const QVector<Line> &vecLines)
{
    insertLines(listLines.size(), vecLines);
}

void Invoice::replaceLine(const Line &line, const QVector<Line> &vecLines)
{
    const int index = listLines.indexOf(line, 0);
    if (index == -1) {
        appendLines(vecLines);
        return;
    }
    listLines.removeAt(index);
    insertLines(index, vecLines);
}

void Invoice::printInvoice()
{
    const int space_name        = 10;
    const int space_price       = 10;
    const int space_quantity    = 10;
    const int space_discount    = 10;
    qDebug() << "Invoice:"
             << "\033[38;2;232;7;184m" << Qt::endl
             << QString("%1   %2   %3   %4").arg(
                    QString("name:")     .leftJustified(space_name        ),
                    QString("price:")    .leftJustified(space_price       ),
                    QString("quantity:") .leftJustified(space_quantity    ),
                    QString("discount:") .leftJustified(space_discount    ))
             << "\033[0m"
                ;
    for (const Line& line: qAsConst(listLines)) {
        qDebug()  << QString("%1   %2   %3   %4").arg(
                         line.name                      .leftJustified(space_name        ),
                         QString::number(line.price)    .leftJustified(space_price       ),
                         QString::number(line.quantity) .leftJustified(space_quantity    ),
                         QString::number(line.discount) .leftJustified(space_discount    ))
                     ;
    }
    qDebug() << Qt::endl;
}

int Invoice::getSize()
{
    return listLines.size();
}

Invoice::Line Invoice::getLineAt(const int index)
{
    return listLines.size() > index ? listLines.at(index) : Line{"", 0, 0, 0};
}

void Invoice::insertLines(const int position, const QVector<Line> &vecLines)
{
    for (int var = 0; var < vecLines.size(); ++var) {
        listLines.insert(position + var, vecLines.at(var));
    }
}
