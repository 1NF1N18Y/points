# Copyright (c) 2013-2016 The Bitcoin Core developers
# Copyright (c) 2017-2019 The Raven Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(ERROR_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

POINTS_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

POINTS_INCLUDES += -I$(srcdir)/secp256k1/include
POINTS_INCLUDES += $(UNIVALUE_CFLAGS)

LIBPOINTS_SERVER=libpoints_server.a
LIBPOINTS_COMMON=libpoints_common.a
LIBPOINTS_CONSENSUS=libpoints_consensus.a
LIBpoints_cli=libpoints_cli.a
LIBPOINTS_UTIL=libpoints_util.a
LIBPOINTS_CRYPTO=crypto/libpoints_crypto.a
LIBPOINTSQT=qt/libpointsqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBPOINTS_ZMQ=libpoints_zmq.a
endif
if BUILD_POINTS_LIBS
LIBPOINTSCONSENSUS=libpointsconsensus.la
endif
if ENABLE_WALLET
LIBPOINTS_WALLET=libpoints_wallet.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBPOINTS_CRYPTO) \
  $(LIBPOINTS_UTIL) \
  $(LIBPOINTS_COMMON) \
  $(LIBPOINTS_CONSENSUS) \
  $(LIBPOINTS_SERVER) \
  $(LIBpoints_cli) \
  $(LIBPOINTS_WALLET) \
  $(LIBPOINTS_ZMQ)

lib_LTLIBRARIES = $(LIBPOINTSCONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_POINTSD
  bin_PROGRAMS += pointsd
endif

if BUILD_POINTS_CLI
  bin_PROGRAMS += points-cli
endif

if BUILD_POINTS_TX
  bin_PROGRAMS += points-tx
endif

.PHONY: FORCE check-symbols check-security
# points core #
POINTS_CORE_H = \
  addrdb.h \
  addressindex.h \
  algo/sph_groestl.h \
  algo/sph_types.h \
  algo/sph_blake.h \
  algo/sph_bmw.h \
  algo/sph_jh.h \
  algo/sph_keccak.h \
  algo/sph_skein.h \
  algo/sph_luffa.h \
  algo/sph_cubehash.h \
  algo/sph_simd.h \
  algo/sph_echo.h \
  algo/sph_shavite.h \
  algo/sph_sha2.h \
  algo/sph_haval.h \
  algo/sph_tiger.h \
  algo/lyra2.h \
  algo/sponge.h \
  algo/gost_streebog.h \
  algo/groestl.c \
  algo/blake.c \
  algo/bmw.c \
  algo/cubehash.c \
  algo/echo.c \
  algo/jh.c \
  algo/keccak.c \
  algo/luffa.c \
  algo/shavite.c \
  algo/simd.c \
  algo/skein.c \
  algo/hamsi.c \
  algo/whirlpool.c \
  algo/shabal.c \
  algo/fugue.c \
  algo/sha2.c \
  algo/extra.c \
  algo/extra.h \
  algo/sph_sha2big.c \
  algo/haval.c \
  algo/tiger.cpp \
  algo/lyra2.cpp \
  algo/sponge.cpp \
  algo/sph_sha2.c \
  algo/gost_streebog.c \
  spentindex.h \
  timestampindex.h \
  addrman.h \
  assets/assets.h \
  assets/assetdb.h \
  assets/assettypes.h \
  assets/messages.h \
  assets/myassetsdb.h \
  assets/restricteddb.h \
  assets/snapshotrequestdb.h \
  assets/assetsnapshotdb.h \
  assets/rewards.h \
  base58.h \
  bloom.h \
  blockencodings.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  noui.h \
  policy/feerate.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  protocol.h \
  random.h \
  reverse_iterator.h \
  reverselock.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/mining.h \
  rpc/protocol.h \
  rpc/safemode.h \
  rpc/server.h \
  rpc/register.h \
  scheduler.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utiltime.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/init.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/bip39.h \
  wallet/bip39_english.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libpoints_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between pointsd and points-qt
libpoints_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(POINTS_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libpoints_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libpoints_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  consensus/consensus.cpp \
  consensus/tx_verify.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  noui.cpp \
  assets/assets.cpp \
  assets/assetdb.cpp \
  assets/assettypes.cpp \
  assets/messages.cpp \
  assets/myassetsdb.cpp \
  assets/restricteddb.cpp \
  assets/snapshotrequestdb.cpp \
  assets/assetsnapshotdb.cpp \
  assets/rewards.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  policy/rbf.cpp \
  pow.cpp \
  rest.cpp \
  rpc/assets.cpp \
  rpc/blockchain.cpp \
  rpc/messages.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/rewards.cpp \
  rpc/safemode.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(POINTS_CORE_H)

if ENABLE_ZMQ
libpoints_zmq_a_CPPFLAGS = $(POINTS_INCLUDES) $(ZMQ_CFLAGS)
libpoints_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libpoints_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between pointsd and points-qt, but only linked
# when wallet enabled
libpoints_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(POINTS_INCLUDES)
libpoints_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libpoints_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/feebumper.cpp \
  wallet/fees.cpp \
  wallet/init.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/bip39.cpp \
  $(POINTS_CORE_H)

# crypto primitives library
crypto_libpoints_crypto_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libpoints_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libpoints_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.h \
  crypto/sha512.cpp \
  crypto/ethash/include/ethash/ethash.h \
  crypto/ethash/include/ethash/ethash.hpp \
  crypto/ethash/include/ethash/hash_types.h \
  crypto/ethash/include/ethash/hash_types.hpp \
  crypto/ethash/include/ethash/keccak.h \
  crypto/ethash/include/ethash/keccak.hpp \
  crypto/ethash/include/ethash/progpow.hpp \
  crypto/ethash/include/ethash/version.h \
  crypto/ethash/lib/ethash/bit_manipulation.h \
  crypto/ethash/lib/ethash/builtins.h \
  crypto/ethash/lib/ethash/endianness.hpp \
  crypto/ethash/lib/ethash/ethash.cpp \
  crypto/ethash/lib/ethash/ethash-internal.hpp \
  crypto/ethash/lib/ethash/kiss99.hpp \
  crypto/ethash/lib/ethash/managed.cpp \
  crypto/ethash/lib/ethash/primes.c \
  crypto/ethash/lib/ethash/primes.h \
  crypto/ethash/lib/ethash/progpow.cpp \
  crypto/ethash/lib/keccak/keccak.c \
  crypto/ethash/lib/keccak/keccakf1600.c \
  crypto/ethash/lib/keccak/keccakf800.c \
  crypto/ethash/lib/support/attributes.h \
  crypto/ethash/helpers.hpp \
  crypto/ethash/progpow_test_vectors.hpp

if USE_ASM
crypto_libpoints_crypto_a_SOURCES += crypto/sha256_sse4.cpp
endif

# consensus: shared between all executables that validate any consensus rules.
libpoints_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(POINTS_INCLUDES)
libpoints_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libpoints_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/pointsconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  support/cleanse.h \
  support/cleanse.cpp \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h \
  LibBoolEE.cpp \
  LibBoolEE.h \
  $(POINTS_CORE_H)

# common: shared between pointsd, and points-qt and non-server tools
libpoints_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(POINTS_INCLUDES)
libpoints_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libpoints_common_a_SOURCES = \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  keystore.cpp \
  netaddress.cpp \
  netbase.cpp \
  policy/feerate.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  warnings.cpp \
  $(POINTS_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libpoints_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(POINTS_INCLUDES)
libpoints_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libpoints_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  fs.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(POINTS_CORE_H)

if GLIBC_BACK_COMPAT
libpoints_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between points-cli and points-qt
libpoints_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(POINTS_INCLUDES)
libpoints_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libpoints_cli_a_SOURCES = \
  rpc/client.cpp \
  $(POINTS_CORE_H)

nodist_libpoints_util_a_SOURCES = $(srcdir)/obj/build.h
#

# pointsd binary #
pointsd_SOURCES = pointsd.cpp
pointsd_CPPFLAGS = $(AM_CPPFLAGS) $(POINTS_INCLUDES)
pointsd_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
pointsd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
pointsd_SOURCES += pointsd-res.rc
endif

pointsd_LDADD = \
  $(LIBPOINTS_SERVER) \
  $(LIBPOINTS_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBPOINTS_UTIL) \
  $(LIBPOINTS_WALLET) \
  $(LIBPOINTS_ZMQ) \
  $(LIBPOINTS_CONSENSUS) \
  $(LIBPOINTS_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

pointsd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# points-cli binary #
points_cli_SOURCES = points-cli.cpp
points_cli_CPPFLAGS = $(AM_CPPFLAGS) $(POINTS_INCLUDES) $(EVENT_CFLAGS)
points_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
points_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
points_cli_SOURCES += points-cli-res.rc
endif

points_cli_LDADD = \
  $(LIBpoints_cli) \
  $(LIBUNIVALUE) \
  $(LIBPOINTS_UTIL) \
  $(LIBPOINTS_CRYPTO)

points_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# points-tx binary #
points_tx_SOURCES = points-tx.cpp
points_tx_CPPFLAGS = $(AM_CPPFLAGS) $(POINTS_INCLUDES)
points_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
points_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
points_tx_SOURCES += points-tx-res.rc
endif

points_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBPOINTS_COMMON) \
  $(LIBPOINTS_UTIL) \
  $(LIBPOINTS_CONSENSUS) \
  $(LIBPOINTS_CRYPTO) \
  $(LIBSECP256K1)

points_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# pointsconsensus library #
if BUILD_POINTS_LIBS
include_HEADERS = script/pointsconsensus.h
libpointsconsensus_la_SOURCES = $(crypto_libpoints_crypto_a_SOURCES) $(libpoints_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libpointsconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libpointsconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libpointsconsensus_la_LIBADD = $(LIBSECP256K1) $(BOOST_LIBS)
libpointsconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_POINTS_INTERNAL
libpointsconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/points-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/points-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/points-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/points-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
