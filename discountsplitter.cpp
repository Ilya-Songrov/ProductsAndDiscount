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
    if (line.quantity < 1) {
        return QVector<Invoice::Line>{modifyIncorrectLine(line)};
    }
    else if (line.discount % line.quantity == 0) {
        return QVector<Invoice::Line>{line};
    }
    return splitLine(line);
}

QVector<Invoice::Line> DiscountSplitter::splitLine(const Invoice::Line &line)
{
    QVector<unsigned int> quantity_candidates;
    quantity_candidates.resize(line.quantity);
    std::iota(std::begin(quantity_candidates), std::end(quantity_candidates), 1);
    QVector<QVector<unsigned int>> quantity_output = combinationSum(quantity_candidates, line.quantity, line.quantity);
    std::sort(quantity_output.begin(), quantity_output.end(), [](const QVector<unsigned int> &vec1, const QVector<unsigned int> &vec2){ return vec1.size() < vec2.size();});
//    qDebug() << "quantity_output" << quantity_output << Qt::endl;

    QVector<unsigned int> discount_candidates;
    discount_candidates.resize(line.discount);
    std::iota(std::begin(discount_candidates), std::end(discount_candidates), 1);
    QVector<QVector<unsigned int>> discount_output = combinationSum(discount_candidates, line.discount, line.quantity);
    std::sort(discount_output.begin(), discount_output.end(), [](const QVector<unsigned int> &vec1, const QVector<unsigned int> &vec2){ return vec1.size() < vec2.size();});
//    qDebug() << "discount_output" << discount_output << Qt::endl;

    return getSplitingLines(quantity_output, discount_output, line);
}

QVector<Invoice::Line> DiscountSplitter::getSplitingLines(const QVector<QVector<unsigned int> > &quantity_output, const QVector<QVector<unsigned int> > &discount_output, const Invoice::Line &line)
{
    int discountStep = 0;
    for (const auto& vecQuantity : quantity_output) {
        for (int var = discountStep; var < discount_output.size(); ++var) {
            const auto& vecDiscount = discount_output.at(var);
            if (vecQuantity.size() == vecDiscount.size()) {
                const auto vecPairs = findDivisionWithoutRemainder(vecQuantity, vecDiscount);
                if (!vecPairs.isEmpty()) {
                    return getLinesFromVecPairs(vecPairs, line);
                }
            }
            else if(vecQuantity.size() < vecDiscount.size()){
                break;
            }
            ++discountStep;
        }
    }
    return getEasySolution(line);
}

QVector<Invoice::Line> DiscountSplitter::getLinesFromVecPairs(const QVector<QPair<unsigned int, unsigned int> > &vecParis, const Invoice::Line &line)
{
    QVector<Invoice::Line> vecLines;
    for (const auto &pair: vecParis) {
        vecLines.append(Invoice::Line{line.name, line.price, pair.first, pair.second});
    }
    return vecLines.isEmpty() ? QVector<Invoice::Line>{modifyIncorrectLine(line)} : vecLines;
}

QVector<Invoice::Line> DiscountSplitter::getEasySolution(const Invoice::Line &line)
{
    if (line.quantity > line.discount || line.quantity < 1 || line.discount < 1) {
        return QVector<Invoice::Line>{modifyIncorrectLine(line)};
    }
    QVector<Invoice::Line> vecLines;
    for (unsigned int var = 0; var < line.quantity - 1; ++var) {
        vecLines.append(Invoice::Line{line.name, line.price, 1, 1});
    }
    vecLines.append(Invoice::Line{line.name, line.price, 1, line.discount - line.quantity + 1});
    return vecLines;
}

Invoice::Line DiscountSplitter::modifyIncorrectLine(const Invoice::Line &line)
{
    if (line.quantity < 1) {
        qWarning() << "Error. Quantity less 0" << Qt::endl;
        return Invoice::Line{line.name, line.price, 1, 1};
    }
    else if (line.quantity > line.discount || line.discount < 1) {
        qWarning() << "Error. Quantity more discount" << Qt::endl;
        return Invoice::Line{line.name, line.price, line.quantity, line.quantity};
    }
    qWarning() << "Error. Can't find necessary numbers. To solve the problem, I reduce the discount" << Qt::endl;
    const auto discount = line.discount > 0 ? (line.discount - (line.quantity % line.discount)) : line.quantity;
    return Invoice::Line{line.name, line.price, line.quantity, discount};
}

QVector<QVector<unsigned int> > DiscountSplitter::combinationSum(QVector<unsigned int> &candidates, int target, const int maxSize)
{
    QVector<QVector<unsigned int>> output;
    QVector<unsigned int> current;
    std::sort(candidates.begin(), candidates.end());
    backtrack(output, current, candidates, target, 0, maxSize);
    return output;
}

void DiscountSplitter::backtrack(QVector<QVector<unsigned int> > &output, QVector<unsigned int> &current, QVector<unsigned int> &candidates, int remain, int start, const int maxSize)
{
    if (remain < 0){
        return;
    }
    else if (remain == 0){
        output.push_back(current);
    }
    else {
        for(int var = start; var < candidates.size(); ++var){
            if (current.size() >= maxSize) {
                return;
            }
            current.push_back(candidates.at(var));
            backtrack(output, current, candidates, remain - candidates.at(var), var, maxSize);
            current.pop_back();
        }
    }
}

QVector<QPair<unsigned int, unsigned int> > DiscountSplitter::findDivisionWithoutRemainder(const QVector<unsigned int> &quantity_candidates, const QVector<unsigned int> &discount_candidates)
{
    if (quantity_candidates.size() != discount_candidates.size()) {
        return {};
    }
    QVector<QPair<unsigned int, unsigned int> > vecPairs;
    for (int var = 0; var < quantity_candidates.size(); ++var) {
        const auto quantity = quantity_candidates.at(var);
        const auto discount = discount_candidates.at(var);
        if (discount % quantity != 0) {
            return {};
        }
        vecPairs.append(qMakePair(quantity, discount));
    }
    return vecPairs;
}
