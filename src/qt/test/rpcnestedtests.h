// Copyright (c) 2016 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2020-2021 The Points Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef POINTS_QT_TEST_RPC_NESTED_TESTS_H
#define POINTS_QT_TEST_RPC_NESTED_TESTS_H

#include <QObject>
#include <QTest>

#include "txdb.h"
#include "txmempool.h"

class RPCNestedTests : public QObject
{
    Q_OBJECT

    private Q_SLOTS:
    void rpcNestedTests();

private:
    CCoinsViewDB *pcoinsdbview;
};

#endif // POINTS_QT_TEST_RPC_NESTED_TESTS_H
