// Copyright (c) 2009-2021 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 10;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (      0,      hashGenesisBlock )
        (     10, uint256("0x0000071f29755f306abba9547217ef13b25d7fd29a453e705ef142faf6f7dd35"))
        (    100, uint256("0x0000000f151409a7ba469d3835eaee5dbf1b2d4fb515c6532724cdf80c2a0da3"))
        (   1000, uint256("0x09dfbbd8682436db7bf0f3e63fa93893bf0c3ae593a6ac666336737ee13e55f8"))
        (  10000, uint256("0x00000000030222fb0ea1c58a13cecede543c57cdaae4811894d4b79ca5e8eef2"))
        (  20000, uint256("0x09f992413e47c39c32c90ba6ff3bd5419137a98a526721ead6cf97f09bafc819"))
        (  50000, uint256("0x2c28d0f4b70f40560c94bd157c2fccd82db1406f05e66e4dac814d5945ded03c"))
        ( 337902, uint256("0xcb0566fb790fa24e41d91d73f0a30f1094b41fe11fb9d240e5c952f5c895cd39"))
        ( 598476, uint256("0x1f28ebec18ff614e7304a58fa4acd742dde5a4fb5eb64985e1a22cb8dac0d542"))
        ( 598477, uint256("0xeda318e8ee919d3fb2cc38504fc1065ee371f5a6152af93dd022fb1b3bd2c3b5"))
        ( 707039, uint256("0xe3d990c569b00cc4d60e1fb278c4f43991b14c90c9e28f6863c07dbca1c31524"))
        ( 750000, uint256("0x329d41c9a4e8438ef5303667060872fc4a7e232ceeac5fcb53fce85e9a469e7d"))
        ( 766370, uint256("0x8f709711dfa67e56b797595ecdb5b036789f77be7abac0610ba59176d522ac5c"))
        ( 800000, uint256("0x24d9d97c7caaf666ef3fa26cfab2be0a9b5183ebb8377482090ece7c3a49e61f"))
        ( 850000, uint256("0xbdd82968ad30705f5fe29f6ad5e0706d5878d765f74418a46fc1e7c200e5dee6"))
        ( 900000, uint256("0x93ada7180d3a073d95ff7e421b257935caa2fbdc28bee10654f82a9b26765891"))
        ( 905233, uint256("0x1eda1df57629aca56f984e934d2e9c9d9c8b816e288b1eed3b8473e99bc26ca9"))
        (1005000, uint256("0x6db6044a7066c38fe81025174cc1dc5023eafd2bc0588e94b73d0481b5666ceb"))
        (1049288, uint256("0xee9e34441ee6a338f060a6685e348dca9594359e477bdaca03c7e131683fcadc"))
        (1149997, uint256("0xf623e6c803005f2e4469d15b59af2c7bc38e40e01d4f2de665d2cd865e23f740"))
        (1351600, uint256("0xbffe68798afd28133ce10636d1d4390177f8532e3807742b58b2527ab1ed2b95"))
        (1580000, uint256("0x189fbe97e61adf3a3e724dcab7999c51f4dc496429704897d52ca541285fa22c"))
        (1600000, uint256("0xd7a4e8551751479aab5d677b1e7f169ca6e20468792775ec8b5f316561448aee"))
        (1700000, uint256("0x6055fc864e4b5c48b5507d9901ccd4a9df70d98fe34d76aa892507456dd1354f"))
        (1800000, uint256("0x5d5dc53fe8d4468704c62db25f8932951517bc4af3167f744595f199a8a4e698"))
        (1900000, uint256("0x37866b7a21871d0275e1d11d206afe4afe5ad7b2a8ed88083e38b0beaa3c10a5"))
        (2000000, uint256("0x9080d2fe37b26ddd4e4192b2c20db757ce81cdc4140222e88e6204855311244a"))
        (2100000, uint256("0xd91190f8e26877cdc9c12ee33e76d1f8c2544c7a7fc87600f4aae03fb5fcb41c"))
        (2200000, uint256("0x2373d5bc83c42d6a408f7bb42c550963280e4e79470279e97b9987d67e77d003"))
        (2300000, uint256("0x8292c711e31ed00b82ce8d9395b3d76787f92d2e5dd8a9425f003b9df3a94f7a"))
        (2400000, uint256("0x98a9e656db642d45e75825ef0d0e5756a85847fa631252f7a9463f2d35107b7d"))
        (2500000, uint256("0x662055f92c47af2116108b430c504f4459a08043b5cc36af662ea6c7d8331128"))
        (2600000, uint256("0x81a0330e07d9a9dc0faf65953e3a5d942b8f53cdc86a23554d40e05f91c1c7a3"))
        (2700000, uint256("0xa2b8bf7879ab7d7133cf5f8d178c138cd4eee4afa94317bf783b488d23a72d45"))
        (2800000, uint256("0x7f221bb194d887db55fa5a0b96d71cca7d7185da1e6f5e1013e4f35af65121da"))
        (2900000, uint256("0x617a62cbe2b465cfed92b243ae5967501a2a37122d5bb9a1d91e219f22624be3"))
        (3000000, uint256("0x4e25e4b1fa83bdde537772c97279a93677ce666748e520c7a80c5b002a9a32d2"))
        (3050000, uint256("0x0e8122b50f5a502a5509be67a4d93f84a4c32d7c506d125e5c92b13cdebdb5d3"))
        (3060000, uint256("0xa1250ab3e6f9d2dbd202882e09215ac06f5595090ada4d8ed0888cfe9ac80804"))
        (3070000, uint256("0x604f871cb3304657e8e9d48348d63d5e4ef0cc80781335ad28365b9a126a3c4c"))
        (3079866, uint256("0x4e251d8ce41f57696c82c935d1bed414a44975e9f4e4104b525854a11aabbebf"))   //micro fork , just enough to stop some users from getting the chain
        (3079900, uint256("0x54a142f4444a824ae49ee7704023f5c56eb06e9fd1b289a0d809582a7428ce3e"))
        (3079950, uint256("0x4103583670b50357afaa32d4575674672bba2ea737d22e0666f4f827f4eb69b7"))
        (3080000, uint256("0xb91a515736592bd54be70693e51c2803d39fc1486bc2d51e497435f6366eda5f"))
        (3090000, uint256("0xdd79133d8c0a68d08e61a903adb244913c7ac82e714682e718c3ae679570299a"))
        (3092500, uint256("0xe6d84229e8dc90d05feff0f93908feb8676af4197f75a7bc689528bd0cb7992d"))
        (3095000, uint256("0x3931f58411041b0d37556fe3f0c7c1c92a8a88b39b57477221484638e412e39a"))
        (3097500, uint256("0x0d83752da1b5b97fd4dd915f90e2247b47b84bfbd0b1cabf6e6858c9ed041f49"))
        (3100000, uint256("0x1f8bddb3e5f72d2df52a99066261a0c3416a8f7da6065492fd542faca761e191"))
        (3110000, uint256("0x928c76ac7267e1d2e0f987bcfef3e30da021fece61b7f758f3050009ce83e694"))
        (3111000, uint256("0xfe9f6468baab70eb0fb7817c89ffb2bb23a7b65dd8d324d5ad5ce49cc141b00f"))








    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, hashGenesisBlockTestNet )
    ;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // ppcoin: synchronized checkpoint (centrally broadcasted)
    uint256 hashSyncCheckpoint = 0;
    uint256 hashPendingCheckpoint = 0;
    CSyncCheckpoint checkpointMessage;
    CSyncCheckpoint checkpointMessagePending;
    uint256 hashInvalidCheckpoint = 0;
    CCriticalSection cs_hashSyncCheckpoint;

    // ppcoin: get last synchronized checkpoint
    CBlockIndex* GetLastSyncCheckpoint()
    {
        LOCK(cs_hashSyncCheckpoint);
        if (!mapBlockIndex.count(hashSyncCheckpoint))
            error("GetSyncCheckpoint: block index missing for current sync-checkpoint %s", hashSyncCheckpoint.ToString().c_str());
        else
            return mapBlockIndex[hashSyncCheckpoint];
        return NULL;
    }

    // ppcoin: only descendant of current sync-checkpoint is allowed
    bool ValidateSyncCheckpoint(uint256 hashCheckpoint)
    {
        if (!mapBlockIndex.count(hashSyncCheckpoint))
            return error("ValidateSyncCheckpoint: block index missing for current sync-checkpoint %s", hashSyncCheckpoint.ToString().c_str());
        if (!mapBlockIndex.count(hashCheckpoint))
            return error("ValidateSyncCheckpoint: block index missing for received sync-checkpoint %s", hashCheckpoint.ToString().c_str());

        CBlockIndex* pindexSyncCheckpoint = mapBlockIndex[hashSyncCheckpoint];
        CBlockIndex* pindexCheckpointRecv = mapBlockIndex[hashCheckpoint];

        if (pindexCheckpointRecv->nHeight <= pindexSyncCheckpoint->nHeight)
        {
            // Received an older checkpoint, trace back from current checkpoint
            // to the same height of the received checkpoint to verify
            // that current checkpoint should be a descendant block
            CBlockIndex* pindex = pindexSyncCheckpoint;
            while (pindex->nHeight > pindexCheckpointRecv->nHeight)
                if (!(pindex = pindex->pprev))
                    return error("ValidateSyncCheckpoint: pprev null - block index structure failure");
            if (pindex->GetBlockHash() != hashCheckpoint)
            {
                hashInvalidCheckpoint = hashCheckpoint;
                return error("ValidateSyncCheckpoint: new sync-checkpoint %s is conflicting with current sync-checkpoint %s", hashCheckpoint.ToString().c_str(), hashSyncCheckpoint.ToString().c_str());
            }
            return false; // ignore older checkpoint
        }

        // Received checkpoint should be a descendant block of the current
        // checkpoint. Trace back to the same height of current checkpoint
        // to verify.
        CBlockIndex* pindex = pindexCheckpointRecv;
        while (pindex->nHeight > pindexSyncCheckpoint->nHeight)
            if (!(pindex = pindex->pprev))
                return error("ValidateSyncCheckpoint: pprev2 null - block index structure failure");
        if (pindex->GetBlockHash() != hashSyncCheckpoint)
        {
            hashInvalidCheckpoint = hashCheckpoint;
            return error("ValidateSyncCheckpoint: new sync-checkpoint %s is not a descendant of current sync-checkpoint %s", hashCheckpoint.ToString().c_str(), hashSyncCheckpoint.ToString().c_str());
        }
        return true;
    }

    bool WriteSyncCheckpoint(const uint256& hashCheckpoint)
    {
        CTxDB txdb;
        txdb.TxnBegin();
        if (!txdb.WriteSyncCheckpoint(hashCheckpoint))
        {
            txdb.TxnAbort();
            return error("WriteSyncCheckpoint(): failed to write to db sync checkpoint %s", hashCheckpoint.ToString().c_str());
        }
        if (!txdb.TxnCommit())
            return error("WriteSyncCheckpoint(): failed to commit to db sync checkpoint %s", hashCheckpoint.ToString().c_str());

        Checkpoints::hashSyncCheckpoint = hashCheckpoint;
        return true;
    }

    bool AcceptPendingSyncCheckpoint()
    {
        LOCK(cs_hashSyncCheckpoint);
        if (hashPendingCheckpoint != 0 && mapBlockIndex.count(hashPendingCheckpoint))
        {
            if (!ValidateSyncCheckpoint(hashPendingCheckpoint))
            {
                hashPendingCheckpoint = 0;
                checkpointMessagePending.SetNull();
                return false;
            }

            CTxDB txdb;
            CBlockIndex* pindexCheckpoint = mapBlockIndex[hashPendingCheckpoint];
            if (!pindexCheckpoint->IsInMainChain())
            {
                CBlock block;
                if (!block.ReadFromDisk(pindexCheckpoint))
                    return error("AcceptPendingSyncCheckpoint: ReadFromDisk failed for sync checkpoint %s", hashPendingCheckpoint.ToString().c_str());
                if (!block.SetBestChain(txdb, pindexCheckpoint))
                {
                    hashInvalidCheckpoint = hashPendingCheckpoint;
                    return error("AcceptPendingSyncCheckpoint: SetBestChain failed for sync checkpoint %s", hashPendingCheckpoint.ToString().c_str());
                }
            }

            if (!WriteSyncCheckpoint(hashPendingCheckpoint))
                return error("AcceptPendingSyncCheckpoint(): failed to write sync checkpoint %s", hashPendingCheckpoint.ToString().c_str());
            hashPendingCheckpoint = 0;
            checkpointMessage = checkpointMessagePending;
            checkpointMessagePending.SetNull();
            printf("AcceptPendingSyncCheckpoint : sync-checkpoint at %s\n", hashSyncCheckpoint.ToString().c_str());
            // relay the checkpoint
            if (!checkpointMessage.IsNull())
            {
                BOOST_FOREACH(CNode* pnode, vNodes)
                    checkpointMessage.RelayTo(pnode);
            }
            return true;
        }
        return false;
    }

    // Automatically select a suitable sync-checkpoint
    uint256 AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && (pindex->GetBlockTime() + nCheckpointSpan * nTargetSpacing > pindexBest->GetBlockTime() || pindex->nHeight + nCheckpointSpan > pindexBest->nHeight))
            pindex = pindex->pprev;
        return pindex->GetBlockHash();
    }

    // Check against synchronized checkpoint
    bool CheckSync(const uint256& hashBlock, const CBlockIndex* pindexPrev)
    {
        if (fTestNet) return true; // Testnet has no checkpoints
        int nHeight = pindexPrev->nHeight + 1;

        LOCK(cs_hashSyncCheckpoint);
        // sync-checkpoint should always be accepted block
        assert(mapBlockIndex.count(hashSyncCheckpoint));
        const CBlockIndex* pindexSync = mapBlockIndex[hashSyncCheckpoint];

        if (nHeight > pindexSync->nHeight)
        {
            // trace back to same height as sync-checkpoint
            const CBlockIndex* pindex = pindexPrev;
            while (pindex->nHeight > pindexSync->nHeight)
                if (!(pindex = pindex->pprev))
                    return error("CheckSync: pprev null - block index structure failure");
            if (pindex->nHeight < pindexSync->nHeight || pindex->GetBlockHash() != hashSyncCheckpoint)
                return false; // only descendant of sync-checkpoint can pass check
        }
        if (nHeight == pindexSync->nHeight && hashBlock != hashSyncCheckpoint)
            return false; // same height with sync-checkpoint
        if (nHeight < pindexSync->nHeight && !mapBlockIndex.count(hashBlock))
            return false; // lower height than sync-checkpoint
        return true;
    }

    bool WantedByPendingSyncCheckpoint(uint256 hashBlock)
    {
        LOCK(cs_hashSyncCheckpoint);
        if (hashPendingCheckpoint == 0)
            return false;
        if (hashBlock == hashPendingCheckpoint)
            return true;
        if (mapOrphanBlocks.count(hashPendingCheckpoint)
            && hashBlock == WantedByOrphan(mapOrphanBlocks[hashPendingCheckpoint]))
            return true;
        return false;
    }

    // ppcoin: reset synchronized checkpoint to last hardened checkpoint
    bool ResetSyncCheckpoint()
    {
        LOCK(cs_hashSyncCheckpoint);
        const uint256& hash = mapCheckpoints.rbegin()->second;
        if (mapBlockIndex.count(hash) && !mapBlockIndex[hash]->IsInMainChain())
        {
            // checkpoint block accepted but not yet in main chain
            printf("ResetSyncCheckpoint: SetBestChain to hardened checkpoint %s\n", hash.ToString().c_str());
            CTxDB txdb;
            CBlock block;
            if (!block.ReadFromDisk(mapBlockIndex[hash]))
                return error("ResetSyncCheckpoint: ReadFromDisk failed for hardened checkpoint %s", hash.ToString().c_str());
            if (!block.SetBestChain(txdb, mapBlockIndex[hash]))
            {
                return error("ResetSyncCheckpoint: SetBestChain failed for hardened checkpoint %s", hash.ToString().c_str());
            }
        }
        else if(!mapBlockIndex.count(hash))
        {
            // checkpoint block not yet accepted
            hashPendingCheckpoint = hash;
            checkpointMessagePending.SetNull();
            printf("ResetSyncCheckpoint: pending for sync-checkpoint %s\n", hashPendingCheckpoint.ToString().c_str());
        }

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            if (mapBlockIndex.count(hash) && mapBlockIndex[hash]->IsInMainChain())
            {
                if (!WriteSyncCheckpoint(hash))
                    return error("ResetSyncCheckpoint: failed to write sync checkpoint %s", hash.ToString().c_str());
                printf("ResetSyncCheckpoint: sync-checkpoint reset to %s\n", hashSyncCheckpoint.ToString().c_str());
                return true;
            }
        }

        return false;
    }

    void AskForPendingSyncCheckpoint(CNode* pfrom)
    {
        LOCK(cs_hashSyncCheckpoint);
        if (pfrom && hashPendingCheckpoint != 0 && (!mapBlockIndex.count(hashPendingCheckpoint)) && (!mapOrphanBlocks.count(hashPendingCheckpoint)))
            pfrom->AskFor(CInv(MSG_BLOCK, hashPendingCheckpoint));
    }

    bool SetCheckpointPrivKey(std::string strPrivKey)
    {
        // Test signing a sync-checkpoint with genesis block
        CSyncCheckpoint checkpoint;
        checkpoint.hashCheckpoint = !fTestNet ? hashGenesisBlock : hashGenesisBlockTestNet;
        CDataStream sMsg(SER_NETWORK, PROTOCOL_VERSION);
        sMsg << (CUnsignedSyncCheckpoint)checkpoint;
        checkpoint.vchMsg = std::vector<unsigned char>(sMsg.begin(), sMsg.end());

        std::vector<unsigned char> vchPrivKey = ParseHex(strPrivKey);
        CKey key;
        key.SetPrivKey(CPrivKey(vchPrivKey.begin(), vchPrivKey.end())); // if key is not correct openssl may crash
        if (!key.Sign(Hash(checkpoint.vchMsg.begin(), checkpoint.vchMsg.end()), checkpoint.vchSig))
            return false;

        // Test signing successful, proceed
        CSyncCheckpoint::strMasterPrivKey = strPrivKey;
        return true;
    }

    bool SendSyncCheckpoint(uint256 hashCheckpoint)
    {
        CSyncCheckpoint checkpoint;
        checkpoint.hashCheckpoint = hashCheckpoint;
        CDataStream sMsg(SER_NETWORK, PROTOCOL_VERSION);
        sMsg << (CUnsignedSyncCheckpoint)checkpoint;
        checkpoint.vchMsg = std::vector<unsigned char>(sMsg.begin(), sMsg.end());

        if (CSyncCheckpoint::strMasterPrivKey.empty())
            return error("SendSyncCheckpoint: Checkpoint master key unavailable.");
        std::vector<unsigned char> vchPrivKey = ParseHex(CSyncCheckpoint::strMasterPrivKey);
        CKey key;
        key.SetPrivKey(CPrivKey(vchPrivKey.begin(), vchPrivKey.end())); // if key is not correct openssl may crash
        if (!key.Sign(Hash(checkpoint.vchMsg.begin(), checkpoint.vchMsg.end()), checkpoint.vchSig))
            return error("SendSyncCheckpoint: Unable to sign checkpoint, check private key?");

        if(!checkpoint.ProcessSyncCheckpoint(NULL))
        {
            printf("WARNING: SendSyncCheckpoint: Failed to process checkpoint.\n");
            return false;
        }

        // Relay checkpoint
        {
            LOCK(cs_vNodes);
            BOOST_FOREACH(CNode* pnode, vNodes)
                checkpoint.RelayTo(pnode);
        }
        return true;
    }

    // Is the sync-checkpoint outside maturity window?
    bool IsMatureSyncCheckpoint()
    {
        LOCK(cs_hashSyncCheckpoint);
        // sync-checkpoint should always be accepted block
        assert(mapBlockIndex.count(hashSyncCheckpoint));
        const CBlockIndex* pindexSync = mapBlockIndex[hashSyncCheckpoint];
        return (nBestHeight >= pindexSync->nHeight + nCoinbaseMaturity ||
                pindexSync->GetBlockTime() + nStakeMinAge < GetAdjustedTime());
    }
}

// ppcoin: sync-checkpoint master key
const std::string CSyncCheckpoint::strMasterPubKey = "0446d5e358df4936adfedbbe4f01e624770d16c79cc96d0b068bba677a2217ba55fb24a637d0d04adcafce8e9b2c53db65d684e308ff402fe2be5dbfe569de11f2";

std::string CSyncCheckpoint::strMasterPrivKey = "";

// ppcoin: verify signature of sync-checkpoint message
bool CSyncCheckpoint::CheckSignature()
{
    CKey key;
    if (!key.SetPubKey(ParseHex(CSyncCheckpoint::strMasterPubKey)))
        return error("CSyncCheckpoint::CheckSignature() : SetPubKey failed");
    if (!key.Verify(Hash(vchMsg.begin(), vchMsg.end()), vchSig))
        return error("CSyncCheckpoint::CheckSignature() : verify signature failed");

    // Now unserialize the data
    CDataStream sMsg(vchMsg, SER_NETWORK, PROTOCOL_VERSION);
    sMsg >> *(CUnsignedSyncCheckpoint*)this;
    return true;
}

// ppcoin: process synchronized checkpoint
bool CSyncCheckpoint::ProcessSyncCheckpoint(CNode* pfrom)
{
    if (!CheckSignature())
        return false;

    LOCK(Checkpoints::cs_hashSyncCheckpoint);
    if (!mapBlockIndex.count(hashCheckpoint))
    {
        // We haven't received the checkpoint chain, keep the checkpoint as pending
        Checkpoints::hashPendingCheckpoint = hashCheckpoint;
        Checkpoints::checkpointMessagePending = *this;
        printf("ProcessSyncCheckpoint: pending for sync-checkpoint %s\n", hashCheckpoint.ToString().c_str());
        // Ask this guy to fill in what we're missing
        if (pfrom)
        {
            pfrom->PushGetBlocks(pindexBest, hashCheckpoint);
            // ask directly as well in case rejected earlier by duplicate
            // proof-of-stake because getblocks may not get it this time
            pfrom->AskFor(CInv(MSG_BLOCK, mapOrphanBlocks.count(hashCheckpoint)? WantedByOrphan(mapOrphanBlocks[hashCheckpoint]) : hashCheckpoint));
        }
        return false;
    }

    if (!Checkpoints::ValidateSyncCheckpoint(hashCheckpoint))
        return false;

    CTxDB txdb;
    CBlockIndex* pindexCheckpoint = mapBlockIndex[hashCheckpoint];
    if (!pindexCheckpoint->IsInMainChain())
    {
        // checkpoint chain received but not yet main chain
        CBlock block;
        if (!block.ReadFromDisk(pindexCheckpoint))
            return error("ProcessSyncCheckpoint: ReadFromDisk failed for sync checkpoint %s", hashCheckpoint.ToString().c_str());
        if (!block.SetBestChain(txdb, pindexCheckpoint))
        {
            Checkpoints::hashInvalidCheckpoint = hashCheckpoint;
            return error("ProcessSyncCheckpoint: SetBestChain failed for sync checkpoint %s", hashCheckpoint.ToString().c_str());
        }
    }

    if (!Checkpoints::WriteSyncCheckpoint(hashCheckpoint))
        return error("ProcessSyncCheckpoint(): failed to write sync checkpoint %s", hashCheckpoint.ToString().c_str());
    Checkpoints::checkpointMessage = *this;
    Checkpoints::hashPendingCheckpoint = 0;
    Checkpoints::checkpointMessagePending.SetNull();
    printf("ProcessSyncCheckpoint: sync-checkpoint at %s\n", hashCheckpoint.ToString().c_str());
    return true;
}
