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

./mvnw -B package -DskipTests=true --file pom.xml 
mv target/sdi-latest.war target/sdi.war

docker-compose -f docker-compose-dev.yml up -d
