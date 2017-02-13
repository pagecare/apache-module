#!/bin/bash

function compile() {
  make clean && \
  make && \
  sudo make install && \
  sudo apxs -i -a -c ${FILE}
}

FILE="${1}"
DIR="${2}"
cd "${DIR}"
LAST=$(md5sum "${DIR}/${FILE}")
compile
sudo service apache2 restart > /dev/null 3>&1 2>&1 > /dev/null
livereloadx --include 'apache2.pid' /var/run/apache2/ &
while true; do
  sleep 1
  NEW=$(md5sum "${DIR}/${FILE}")
  if [ "$NEW" != "$LAST" ]; then
      LAST="$NEW"
      compile && \
      sudo service apache2 restart > /dev/null 3>&1 2>&1 > /dev/null && \
      echo "Apache restarted as ${FILE} changed"
  fi
done

