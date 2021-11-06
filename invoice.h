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
#include <QDebug>

class Invoice
{
public:
    struct Line{
        QString name                ;
        unsigned int price          = 0;
        unsigned int amount         = 0;
        unsigned int discount       = 0;
        Line(const QString &n, const unsigned int p, const unsigned int a, const unsigned int d)
            : name(n)
            , price(p)
            , amount(a)
            , discount(d)
        {}
        bool operator==(const Line &l){
            return l.name == this->name &&
                    l.price == this->price &&
                    l.amount == this->amount &&
                    l.discount == this->discount;
        }
        friend QDebug operator<< (QDebug dbg, const Line& line){
            dbg.space() << line.name << line.price << line.amount << line.discount << Qt::endl;
            return dbg;
        }
    };
    Invoice();

    void appendLine(const Line &line);
    void appendLines(const QVector<Line> &vecLines);
    void replaceLine(const Line &line, const QVector<Line> &vecLines);
    void printInvoice(const QString &message);

    int getSize();
    Line getLineAt(const int index);

private:
    void insertLines(const int position, const QVector<Line> &vecLines);

private:
    QList<Line> listLines;
};

