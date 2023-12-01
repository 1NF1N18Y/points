// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2020-2021 The Points Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MEOWCOIN_QT_MEOWCOINADDRESSVALIDATOR_H
#define MEOWCOIN_QT_MEOWCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class PointsAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit PointsAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** points address widget validator, checks for a valid points address.
 */
class PointsAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit PointsAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // MEOWCOIN_QT_MEOWCOINADDRESSVALIDATOR_H
