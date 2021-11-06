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
    static QVector<Invoice::Line> getSmallEasySolution(const Invoice::Line &line);
    static QVector<Invoice::Line> getBigEasySolution(const Invoice::Line &line);
};

