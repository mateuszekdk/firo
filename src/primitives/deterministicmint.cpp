// Copyright (c) 2019 The Zcoin Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <tinyformat.h>
#include "deterministicmint.h"

using namespace libzerocoin;

CDeterministicMint::CDeterministicMint()
{
    SetNull();
}

CDeterministicMint::CDeterministicMint(const uint32_t& nCount, const uint256& hashSeed, const uint256& hashSerial, const Bignum& pubcoin)
{
    SetNull();
    this->nCount = nCount;
    this->hashSeed = hashSeed;
    this->hashSerial = hashSerial;
    this->pubcoin = pubcoin;
}

void CDeterministicMint::SetNull()
{
    nCount = 0;
    hashSeed.SetNull();
    hashSerial.SetNull();
    txid.SetNull();
    nHeight = -1;
    nId = 0;
    denom = CoinDenomination::ZQ_ERROR;
    isUsed = false;
}

std::string CDeterministicMint::ToString() const
{
    return strprintf(" DeterministicMint:\n   count=%d\n   hashseed=%s\n   hashSerial=%s\n   hashPubcoin=%s\n   txid=%s\n   height=%d\n   id=%d\n   denom=%d\n   isUsed=%d\n",
    nCount, hashSeed.GetHex(), hashSerial.GetHex(), GetPubCoinHash(pubcoin).GetHex(), txid.GetHex(), nHeight, nId, denom, isUsed);
}