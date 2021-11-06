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

#pragma once

#include <QObject>
#include <QVector>
#include <QDebug>

#include "invoice.h"

class DiscountSplitter
{
public:
    DiscountSplitter();

    static QVector<Invoice::Line> splitInvoiceLine(const Invoice::Line &line);

private:
    static QVector<Invoice::Line> splitLine(const Invoice::Line &line);
    static QVector<Invoice::Line> getSplitingLines(const QVector<QVector<unsigned int>> &amount_output,
                                                   const QVector<QVector<unsigned int>> &discount_output,
                                                   const Invoice::Line &line);
    static QVector<Invoice::Line> getLinesFromVecPairs(const QVector<QPair<unsigned int, unsigned int> > &vecParis,
                                                       const Invoice::Line &line);
    static QVector<Invoice::Line> getEasySolution(const Invoice::Line &line);
    static Invoice::Line modifyIncorrectLine(const Invoice::Line &line);

    static QVector<QVector<unsigned int>> combinationSum(QVector<unsigned int> &candidates, int target, const int maxSize);
    static void backtrack(QVector<QVector<unsigned int>> &output, QVector<unsigned int> &current, QVector<unsigned int> &candidates, int remain, int start, const int maxSize);

    static QVector<QPair<unsigned int, unsigned int> > findDivisionWithoutRemainder(
            const QVector<unsigned int>& amount_candidates,
            const QVector<unsigned int>& discount_candidates);
};

