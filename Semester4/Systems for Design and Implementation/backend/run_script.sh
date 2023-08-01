#!/bin/bash
cd /home/ubuntu/lab-5x-georgerapeanu/backend

if [ -f .env ] ; then
  source .env;
fi;

if [ -z $WEBHOOK_URL ] ; then
  echo '$WEBHOOK_URL should be set!'
  exit 1;
fi;

git pull
mkdir target;

RELEASE_URL=$(curl -Ls -o /dev/null -w %{url_effective} https://github.com/UBB-SDI-23/lab-5x-georgerapeanu/releases/latest)
PACKAGE_URL=$(echo $RELEASE_URL | sed -E "s/(\/tag)(\/[^/]*)$/\/download\2/")
curl -sL --output ./target/sdi.war $PACKAGE_URL/sdi.war

docker-compose up -d

#curl -X POST -d "https://$(curl -s http://metadata.google.internal/computeMetadata/v1/instance/network-interfaces/0/access-configs/0/external-ip -H "Metadata-Flavor: Google"):443" $WEBHOOK_URL
