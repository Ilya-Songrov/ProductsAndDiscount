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

#include "discountsplitter.h"

DiscountSplitter::DiscountSplitter()
{

}

QVector<Invoice::Line> DiscountSplitter::splitInvoiceLine(const Invoice::Line &line)
{
    if (line.amount < 1 || line.discount < 1) {
        const auto li = Invoice::Line{line.name, line.price, 1, 1};
        qWarning() << QString("Error. Amount: %1, Discount: %2. I create new line:").arg(line.amount).arg(line.discount) << li << Qt::endl;
        return QVector<Invoice::Line>{ li };
    }
    else if (line.amount > line.discount) {
        const auto li = Invoice::Line{line.name, line.price, line.amount, line.amount};
        qWarning() << QString("Error. Amount: %1, Discount: %2. I create new line:").arg(line.amount).arg(line.discount) << li << Qt::endl;
        return QVector<Invoice::Line>{ li };
    }
    else if (line.discount % line.amount == 0) {
        return QVector<Invoice::Line>{line};
    }
    return getSmallEasySolution(line);
}

QVector<Invoice::Line> DiscountSplitter::getSmallEasySolution(const Invoice::Line &line)
{
    if (line.amount == 1) {
        return QVector<Invoice::Line>{line};
    }
    QVector<Invoice::Line> vecLines;
    const auto amountMinusOne = line.amount - 1;
    const auto l1 = Invoice::Line{line.name, line.price, amountMinusOne, line.discount - (line.discount % amountMinusOne)};
    const auto l2 = Invoice::Line{line.name, line.price, 1, line.discount - l1.discount};
    vecLines.append(l1);
    vecLines.append(l2);
    return vecLines;
}

QVector<Invoice::Line> DiscountSplitter::getBigEasySolution(const Invoice::Line &line)
{
    QVector<Invoice::Line> vecLines;
    for (unsigned int var = 0; var < line.amount - 1; ++var) {
        vecLines.append(Invoice::Line{line.name, line.price, 1, 1});
    }
    vecLines.append(Invoice::Line{line.name, line.price, 1, line.discount - line.amount + 1});
    return vecLines;
}


