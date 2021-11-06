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

#include <QCoreApplication>

#include "discountsplitter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Invoice invoiceOriginal;
    invoiceOriginal.appendLine(Invoice::Line{"Product_A", 127, 5, 21});
    invoiceOriginal.appendLine(Invoice::Line{"Product_B", 127, 4, 9});
    invoiceOriginal.appendLine(Invoice::Line{"Product_C", 127, 3, 23});
    invoiceOriginal.appendLine(Invoice::Line{"Product_D", 353, 5, 45});
    invoiceOriginal.appendLine(Invoice::Line{"Product_E", 353, 2, 2});
    invoiceOriginal.appendLine(Invoice::Line{"Product_E", 353, 13, 245});
    invoiceOriginal.appendLine(Invoice::Line{"Product_E", 353, 957, 999});
    invoiceOriginal.appendLine(Invoice::Line{"Product_E", 123, 7111555, 8111555});
//    invoiceOriginal.appendLine(Invoice::Line{"Product_E", 877, 7111555, 17});
//    invoiceOriginal.appendLine(Invoice::Line{"Product_F", 353, 2, 1});
//    invoiceOriginal.appendLine(Invoice::Line{"Product_G", 353, 2, 0});
//    invoiceOriginal.appendLine(Invoice::Line{"Product_H", 353, 0, 1});
    invoiceOriginal.printInvoice("Original invoice:");

    Invoice invoiceModified;
    for (int var = 0; var < invoiceOriginal.getSize(); ++var) {
        invoiceModified.appendLines(DiscountSplitter::splitInvoiceLine(invoiceOriginal.getLineAt(var)));
    }
    invoiceModified.printInvoice("Modified invoice:");

    return a.exec();
}


