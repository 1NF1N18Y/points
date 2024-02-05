// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2017-2020 The OLDNAMENEEDKEEP__Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"

#include <assert.h>
#include "chainparamsseeds.h"

//TODO: Take these out
extern double algoHashTotal[16];
extern int algoHashHits[16];


static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << CScriptNum(0) << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}


//   Build the genesis block. Note that the output of its generation
//   transaction cannot be spent since it did not originally exist in the
//   database.
 
//   CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1701427325, nBits=1d00ffff, nNonce=2083236893, vtx=1)
//     CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
//      CTxIn(COutPoint(000000, -1), coinbase 0492fa0716eb6e529044d9bc1c8d6dc9649d7af52665dbe36ef8e7ff70a5bcff40541d56007f1c897815b457366bd43806258440fb103e90984a284c8d339ef9999)
//       CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
//     vMerkleTree: 4a5e1e
 
// New Genesis Block Creation

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Points was made on 12/1/2023 for learning blockchain";
    const CScript genesisOutputScript = CScript() << ParseHex("0492fa0716eb6e529044d9bc1c8d6dc9649d7af52665dbe36ef8e7ff70a5bcff40541d56007f1c897815b457366bd43806258440fb103e90984a284c8d339ef9999") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

void CChainParams::TurnOffSegwit() {
	consensus.nSegwitEnabled = false;
}

void CChainParams::TurnOffCSV() {
	consensus.nCSVEnabled = false;
}

void CChainParams::TurnOffBIP34() {
	consensus.nBIP34Enabled = false;
}

void CChainParams::TurnOffBIP65() {
	consensus.nBIP65Enabled = false;
}

void CChainParams::TurnOffBIP66() {
	consensus.nBIP66Enabled = false;
}

bool CChainParams::BIP34() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::BIP65() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::BIP66() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::CSVEnabled() const{
	return consensus.nCSVEnabled;
}


/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        //consensus.nSubsidyHalvingInterval = 100;  //~ 4 yrs at 1 min block time
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; // 
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled 	= true;
        consensus.powLimit 		= uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.kawpowLimit 	= uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Estimated starting diff for first 180 kawpow blocks
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
	    consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1613; // Approx 80% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1653004800; // Friday, 20 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1653264000; // Monday, 23 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;  //Assets (HIP2)
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1653004800; // Friday, 20 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1653264000; // Monday, 23 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;  // Assets (HIP5)
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 1653004800; // Friday, 20 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1653264000; // Monday, 23 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 1714; // Approx 85% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 1653004800; // Friday, 20 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 1653264000; // Monday, 23 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 1714; // Approx 85% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 1653004800; // Friday, 20 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1653264000; // Monday, 23 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 1411; // Approx 70% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 1653004800; // Friday, 20 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 1653264000; // Monday, 23 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 1411; // Approx 70% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 2016;
	
	    consensus.BIP34LockedIn = 6048; // Locked_in at height 6048


        // The best chain should have at least this much work
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010"); // block 1

        // By default assume that the signatures in ancestors of this block are valid
        consensus.defaultAssumeValid = uint256S("0x004be34bb6e7c20aad94b1638a1e50c5fb6bc5523a5f962bb80b0c84124f1333"); // Block 113

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x50; // P
        pchMessageStart[1] = 0x4E; // N
        pchMessageStart[2] = 0x54; // T
        pchMessageStart[3] = 0x53; // S
        nDefaultPort = 3466;
        nPruneAfterHeight = 100000;
		
		uint32_t nGenesisTime = 1701429301;	

 

		genesis = CreateGenesisBlock(nGenesisTime, 16349779, 0x1e00ffff, 4, 5000 * COIN);
        consensus.hashGenesisBlock = genesis.GetX16RHash();	
		// std::cout << "consensus.hashGenesisBlock.GetHex() " << consensus.hashGenesisBlock.GetHex() << std::endl;
		// std::cout << "genesis.hashPrevBlock().GetHex() " << genesis.hashPrevBlock.GetHex() << std::endl;		
		assert(consensus.hashGenesisBlock == uint256S("0x000000d21317d68f5253f7ef4cecb163e09d004b598a98be62e857708719fc33"));
        assert(genesis.hashMerkleRoot == uint256S("85c1058564afa9f0ef033b305f3a8815cfb90c75099ff9498739955d5ea242bf"));


        vSeeds.emplace_back("194.163.179.204:3466", false);

        // Address start with P
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,55);  
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,117); 
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,107); 
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x8D, 0xF2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x89, 0xA6, 0xE4};


        // POINTS BIP44 cointype in mainnet is '3448'
        nExtCoinType = 3448;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

		checkpointData = (CCheckpointData) {
            {
            	{
            	    {0, uint256S("0x000000d21317d68f5253f7ef4cecb163e09d004b598a98be62e857708719fc33")},
            	}
            }
        };

        chainTxData = ChainTxData{
            // Update as we know more about the contents of the Points chain from rpc: getchaintxstats 50000
        	1701429301, // * UNIX timestamp of last known number of transactions
            0,      // * total number of transactions between genesis and that timestamp
                        // * (the tx=... number in the SetBestChain debug.log lines)
            0.01 // * estimated number of transactions per second after that timestamp
        };


        // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;
        nIssueMsgChannelAssetBurnAmount = 100 * COIN;
        nIssueQualifierAssetBurnAmount = 1000 * COIN;
        nIssueSubQualifierAssetBurnAmount = 100 * COIN;
        nIssueRestrictedAssetBurnAmount = 1500 * COIN;
        nAddNullQualifierTagBurnAmount = .1 * COIN;
		
        // 2% of 5000 COIN to Donation
	    nCommunityAutonomousAmount = 5;
        nNodesPercentage = 3;

        // Burn Addresses
	    strIssueAssetBurnAddress = "PissueAssetXXXXXXXXXXXXXXXXa1oUfD";
        strReissueAssetBurnAddress = "PReissueAssetXXXXXXXXXXXXXXUdjigq";
        strIssueSubAssetBurnAddress = "PissueSubAssetXXXXXXXXXXXXXbCnNFk";
        strIssueUniqueAssetBurnAddress = "PissueUniqueAssetXXXXXXXXXXSVUgF5";
        strIssueMsgChannelAssetBurnAddress = "PissueMsgChanneLAssetXXXXXXUe6Pvr";
        strIssueQualifierAssetBurnAddress = "PissueQuaLifierXXXXXXXXXXXXWLyvs5";
        strIssueSubQualifierAssetBurnAddress = "PissueSubQuaLifierXXXXXXXXXVHmaXW";
        strIssueRestrictedAssetBurnAddress = "PissueRestrictedXXXXXXXXXXXXfEYLU";
        strAddNullQualifierTagBurnAddress = "PaddTagBurnXXXXXXXXXXXXXXXXUrKr7b";
        
        //Global Burn Address
        strGlobalBurnAddress = "PBurnXXXXXXXXXXXXXXXXXXXXXXUkdzqy";

        // Donation Address
        strCommunityAutonomousAddress = "PMusU6LgjQ3Yp947M7mm5Nca7avLJgvxfL";
        strNodes = "PMusU6LgjQ3Yp947M7mm5Nca7avLJgvxfL";

        // DGW Activation
        nDGWActivationBlock = 1;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours

        nAssetActivationHeight = 1; // Asset activated block height
        nMessagingActivationBlock = 1; // Messaging activated block height
        nRestrictedActivationBlock = 1; // Restricted activated block height

        nKAAAWWWPOWActivationTime = 1701434110;
        nKAWPOWActivationTime = nKAAAWWWPOWActivationTime;
    }
};

/**
 * Testnet (v7)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 2100000;  //~ 4 yrs at 1 min block time
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; // 
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled 	= true;
        consensus.powLimit 	= uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.kawpowLimit 	= uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Estimated starting diff for first 180 kawpow blocks
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
	    consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1613; // Approx 80% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1658055600; // Sunday 17 July 2022 12:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1659178800; // Saturday, 30 July 2022 11:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;  //Assets (HIP2)
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1658055600; // Sunday 17 July 2022 12:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1659178800; // Saturday, 30 July 2022 11:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;  // Assets (HIP5)
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 1658055600; // Sunday 17 July 2022 12:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1659178800; // Saturday, 30 July 2022 11:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 1714; // Approx 85% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 1658055600; // Sunday 17 July 2022 12:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 1659178800; // Saturday, 30 July 2022 11:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 1714; // Approx 85% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 1658055600; // Sunday 17 July 2022 12:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1659178800; // Saturday, 30 July 2022 11:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 1411; // Approx 70% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 1658055600; // Sunday 17 July 2022 12:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 1659178800; // Saturday, 30 July 2022 11:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 1411; // Approx 70% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 2016;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000000eaab417d6dfe9bd75119972e1d07ecfe8ff655bef7c2acb3d9a0eeed81");


        pchMessageStart[0] = 0x6d;
        pchMessageStart[1] = 0x65;
        pchMessageStart[2] = 0x77;
        pchMessageStart[3] = 0x63;
        nDefaultPort = 4568;
        nPruneAfterHeight = 1000;
		
		uint32_t nGenesisTime = 1701434110;	

        // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
		/////////////////////////////////////////////////////////////////
		
        // arith_uint256 test;
        // bool fNegative;    
        // bool fOverflow;
        // test.SetCompact(0x1e00ffff, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1e00ffff, 4, 5000 * COIN);
        //     genesis.hashPrevBlock = TempHashHolding;
		// 	// Depending on when the timestamp is on the genesis block. You will need to use GetX16RHash or GetX16RV2Hash. Replace GetHash() with these below
        //     consensus.hashGenesisBlock = genesis.GetX16RHash();

        //     arith_uint256 BestBlockHashArith = UintToArith256(BestBlockHash);
        //     if (UintToArith256(consensus.hashGenesisBlock) < BestBlockHashArith) {
        //         BestBlockHash = consensus.hashGenesisBlock;
        //         std::cout << "CHOOSE: consensus.hashGenesisBlock.GetHex(): " << consensus.hashGenesisBlock.GetHex() << " Nonce: " << i << " nGenesisTime: " << nGenesisTime << "\n";
        //         std::cout << "CHOOSE: BestBlockHash.GetHex(): " << BestBlockHash.GetHex() << " Nonce: " << i << " nGenesisTime: " << nGenesisTime << "\n";
        //         std::cout << "CHOOSE: genesis.GetX16RHash().GetHex(): " << genesis.GetX16RHash().GetHex() << " Nonce: " << i << " nGenesisTime: " << nGenesisTime << "\n";
        //         std::cout << "CHOOSE: PrevBlockHash: " << genesis.hashPrevBlock.GetHex() << "\n";
        //     }

        //     //TempHashHolding = consensus.hashGenesisBlock;

        //     if (BestBlockHashArith < test) {
        //         genesisNonce = i - 1;
        //         break;
        //     }
        //     std::cout << "	 consensus.hashGenesisBlock.GetHex(): " << consensus.hashGenesisBlock.GetHex() << " Nonce: " << i << "\n";
        // }
        // std::cout << "\n";
        // std::cout << "\n";
        // std::cout << "\n";

        // std::cout << "BestBlockHash.GetHex() to 0x" << BestBlockHash.GetHex() << std::endl;
        // std::cout << "genesis.GetX16RHash().GetHex() to 0x" << genesis.GetX16RHash().GetHex() << std::endl;
        // std::cout << "Genesis Nonce to " << genesisNonce << std::endl;
        // std::cout << "Genesis Merkle " << genesis.hashMerkleRoot.GetHex() << std::endl;

        // std::cout << "\n";
        // std::cout << "\n";
        // int totalHits = 0;
        // double totalTime = 0.0;

        // for(int x = 0; x < 16; x++) {
        //     totalHits += algoHashHits[x];
        //     totalTime += algoHashTotal[x];
        //     std::cout << "hash algo " << x << " hits " << algoHashHits[x] << " total " << algoHashTotal[x] << " avg " << algoHashTotal[x]/algoHashHits[x] << std::endl;
        // }

        // std::cout << "Totals: hash algo " <<  " hits " << totalHits << " total " << totalTime << " avg " << totalTime/totalHits << std::endl;

        // genesis.hashPrevBlock = TempHashHolding;

        // return;
		
		/////////////////////////////////////////////////////////////////

		genesis = CreateGenesisBlock(nGenesisTime, 0, 0x1e00ffff, 4, 1000 * COIN);
        consensus.hashGenesisBlock = genesis.GetX16RHash();	
		std::cout << "consensus.hashGenesisBlock.GetHex() " << consensus.hashGenesisBlock.GetHex() << std::endl;
		std::cout << "genesis.hashPrevBlock().GetHex() " << genesis.hashPrevBlock.GetHex() << std::endl;		
		assert(consensus.hashGenesisBlock == uint256S("0x00"));
        assert(genesis.hashMerkleRoot == uint256S("0x00"));
	
		
        vFixedSeeds.clear();
        vSeeds.clear();
	    vSeeds.emplace_back("seed-testnet-pnt.points.cc", false);
		
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,55);  
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,117); 
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,107); 
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x86, 0xF4, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x8F, 0xD6, 0x54};

        // Points BIP44 cointype in testnet
        nExtCoinType = 1;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0x")},
            }
        };

        chainTxData = ChainTxData{
            // Update as we know more about the contents of the Points chain
            1661734222, // * UNIX timestamp of last known number of transactions
            0,     // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.0        // * estimated number of transactions per second after that timestamp
        };

        /** MEOWCOIN Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;
        nIssueMsgChannelAssetBurnAmount = 100 * COIN;
        nIssueQualifierAssetBurnAmount = 1000 * COIN;
        nIssueSubQualifierAssetBurnAmount = 100 * COIN;
        nIssueRestrictedAssetBurnAmount = 1500 * COIN;
        nAddNullQualifierTagBurnAmount = .1 * COIN;
		
	    // 15% of 5000 COIN to Donation
	    nCommunityAutonomousAmount = 15;

        // Burn Addresses
	    strIssueAssetBurnAddress = "mCissueAssetXXXXXXXXXXXXXXXXauYgzW";
        strReissueAssetBurnAddress = "mCReissueAssetXXXXXXXXXXXXXXViYbet";
        strIssueSubAssetBurnAddress = "mCissueSubAssetXXXXXXXXXXXXXb41gMc";
        strIssueUniqueAssetBurnAddress = "mCissueUniqueAssetXXXXXXXXXXWguvk3";
        strIssueMsgChannelAssetBurnAddress = "mCissueMsgChanneLAssetXXXXXXWPw4W6";
        strIssueQualifierAssetBurnAddress = "mCissueQuaLifierXXXXXXXXXXXXW2VtZy";
        strIssueSubQualifierAssetBurnAddress = "mCissueSubQuaLifierXXXXXXXXXTj8yy8";
        strIssueRestrictedAssetBurnAddress = "mCissueRestrictedXXXXXXXXXXXX3xpZV";
        strAddNullQualifierTagBurnAddress = "mCaddTagBurnXXXXXXXXXXXXXXXXapsVx8";

	    //Global Burn Address
        strGlobalBurnAddress = "mCBurnXXXXXXXXXXXXXXXXXXXXXXUDUcus";
		
	    //CommunityAutonomousAddress
        strCommunityAutonomousAddress = "m1aNrki9MUb7FshxGiph6rR3eCmS9wU3rw";

        // DGW Activation
        nDGWActivationBlock = 1;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours

        nAssetActivationHeight = 1; // Asset activated block height
        nMessagingActivationBlock = 1; // Messaging activated block height
        nRestrictedActivationBlock = 1; // Restricted activated block height

        nKAAAWWWPOWActivationTime = 1661833868;
        nKAWPOWActivationTime = nKAAAWWWPOWActivationTime;
        /** MEOWCOIN End **/
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.kawpowLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;  // Assets (HIP5)
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 0; // GMT: Sun Mar 3, 2019 5:00:00 PM
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 999999999999ULL; // UTC: Wed Dec 25 2019 07:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 208;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 288;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 400;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 500;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x44;
        pchMessageStart[1] = 0x52; 
        pchMessageStart[2] = 0x4F; 
        pchMessageStart[3] = 0x57; 
        nDefaultPort = 19444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1661734578, 1, 0x207fffff, 4, 5000 * COIN);
        consensus.hashGenesisBlock = genesis.GetX16RHash();

        //assert(consensus.hashGenesisBlock == uint256S("0x0b2c703dc93bb63a36c4e33b85be4855ddbca2ac951a7a0a29b8de0408200a3c"));
        //assert(genesis.hashMerkleRoot == uint256S("e8916cf6592c8433d598c3a5fe60a9741fd2a997b39d93af2d789cdd9d9a7390"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            {
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };
		
		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,42);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,124);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,114);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        // Points BIP44 cointype in regtest
        nExtCoinType = 1;

        /** MEOWCOIN Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;
        nIssueMsgChannelAssetBurnAmount = 100 * COIN;
        nIssueQualifierAssetBurnAmount = 1000 * COIN;
        nIssueSubQualifierAssetBurnAmount = 100 * COIN;
        nIssueRestrictedAssetBurnAmount = 1500 * COIN;
        nAddNullQualifierTagBurnAmount = .1 * COIN;
		
	//10% of 5000 COIN to ASSIGN
	nCommunityAutonomousAmount = 10;

        // Burn Addresses
	strIssueAssetBurnAddress = "J1VQJKLSLVZ4syiCAx5hEPq8BrkFaxAXAi";
        strReissueAssetBurnAddress = "J2yh4DiLETuVVDvpvBNSq3QCmHcdMmNEdp";
        strIssueSubAssetBurnAddress = "J3PE3FsHqfszvz7nhwK2Gc32wykrc7pNMA";
        strIssueUniqueAssetBurnAddress = "J4yKRTYF2nRryYEnupsNnQQmRKsQhdspYB";
        strIssueMsgChannelAssetBurnAddress = "J58ndjHjLYKHMszr4ehUg9YMWPAiXNEepa";
        strIssueQualifierAssetBurnAddress = "J68wpmVvdE6bMSkiCEDQWCHCKZs4VVdE2G";
        strIssueSubQualifierAssetBurnAddress = "J7MSidYgNJrPE15ouEsXPYXFYH2AAPXmhr";
        strIssueRestrictedAssetBurnAddress = "J8uX8jfZn14P1VNzh6YjSzLaRTQAdoFSHn";
        strAddNullQualifierTagBurnAddress = "J9CrKy8m548AvSbcv1mcn7tyJQkgcwVfj6";		
	//Global Burn Address
        strGlobalBurnAddress = "JGYQBki6wWWnJLp2dcgdtNZWs9a2e1nXM3";
		
	//CommunityAutonomousAddress
        strCommunityAutonomousAddress = "JCPncGFawSDgP3CmG19MB6cbKP5XuhXY4u";

        // DGW Activation
        nDGWActivationBlock = 200;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours

        nAssetActivationHeight = 0; // Asset activated block height
        nMessagingActivationBlock = 0; // Messaging activated block height
        nRestrictedActivationBlock = 0; // Restricted activated block height

        // TODO, we need to figure out what to do with this for regtest. This effects the unit tests
        // For now we can use a timestamp very far away
        // If you are looking to test the kawpow hashing function in regtest. You will need to change this number
        nKAAAWWWPOWActivationTime = 3582830167;
        nKAWPOWActivationTime = nKAAAWWWPOWActivationTime;
        /** MEOWCOIN End **/
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &GetParams() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network, bool fForceBlockNetwork)
{
    SelectBaseParams(network);
    if (fForceBlockNetwork) {
        bNetwork.SetNetwork(network);
    }
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}

void TurnOffSegwit(){
	globalChainParams->TurnOffSegwit();
}

void TurnOffCSV() {
	globalChainParams->TurnOffCSV();
}

void TurnOffBIP34() {
	globalChainParams->TurnOffBIP34();
}

void TurnOffBIP65() {
	globalChainParams->TurnOffBIP65();
}

void TurnOffBIP66() {
	globalChainParams->TurnOffBIP66();
}
