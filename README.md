# spring-launcher
Bootstrap and launcher for Spring projects

# Compilation
This project is still in WIP, so the instructions and setup here is still poor, and the project is messy.

That said, here are the things one should keep in mind:
1) We only really use the glfw3 folder. The default (QT5) setup isn't used as cross-compiling this is very complicated apparently.
2) We use mxe for cross-compilation as it helps create windows binaries.
3) It requires mxe to be setup with posix threads (`make MXE_TARGETS=i686-w64-mingw32.static.posix`) and curl compiled with the following version of curl in curl.mk:
```
# This file is part of MXE. See LICENSE.md for licensing information.

PKG             := curl
$(PKG)_WEBSITE  := https://curl.haxx.se/libcurl/
$(PKG)_DESCR    := cURL
$(PKG)_IGNORE   :=
$(PKG)_VERSION  := 7.55.1
$(PKG)_CHECKSUM := 3eafca6e84ecb4af5f35795dee84e643d5428287e88c041122bb8dac18676bb7
$(PKG)_SUBDIR   := curl-$($(PKG)_VERSION)
$(PKG)_FILE     := curl-$($(PKG)_VERSION).tar.xz
$(PKG)_URL      := https://curl.haxx.se/download/$($(PKG)_FILE)
$(PKG)_DEPS     := gcc openssl pthreads

define $(PKG)_UPDATE
    $(WGET) -q -O- 'https://curl.haxx.se/download/?C=M;O=D' | \
    $(SED) -n 's,.*curl-\([0-9][^"]*\)\.tar.*,\1,p' | \
    head -1
endef

define $(PKG)_BUILD
    cd '$(1)' && ./configure \
        $(MXE_CONFIGURE_OPTS) \
        --without-libidn2 \
		--without-libssh2 \
		--disable-ftp --disable-dict --disable-imap --disable-pop3 \
		--disable-smtp --disable-telnet --disable-tftp --disable-ldap \
		--disable-rtsp --disable-manual --disable-shared \
        LIBS=`'$(TARGET)-pkg-config' pthreads --libs`
    $(MAKE) -C '$(1)' -j '$(JOBS)' install $(MXE_DISABLE_DOCS)
    ln -sf '$(PREFIX)/$(TARGET)/bin/curl-config' '$(PREFIX)/bin/$(TARGET)-curl-config'

    '$(TARGET)-gcc' \
        -W -Wall -Werror -ansi -pedantic \
        '$(TEST_FILE)' -o '$(PREFIX)/$(TARGET)/bin/test-curl.exe' \
        `'$(TARGET)-pkg-config' libcurl --cflags --libs`
endef
```
4) To link `spring-launcher.exe` it's necessary to add additional link flags (`-lpthread -lssl -lnettle -lcrypto -lwldap32 -lws2_32 -lgdi32`). They should be added in the similar manner to the `extra_build.sh` (the script's there for reference, and shouldn't be executed directly). This is probably a result of poor cmake setup

# Setup

Once the above (complicated) compilation is done, it's possible to customize the launcher by just editing the `res/config.json` and specified required games, maps, engines as well as launch options.
