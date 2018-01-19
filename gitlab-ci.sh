#!/bin/bash

echo "Importing Horizon MySQL Data..."
mysql --user=${MYSQL_USER} --password=${MYSQL_PASSWORD} --host=mysql horizon < sql-files/horizon.sql
mkdir build
cd build
rm -rf ./*
cmake ../
make install -j 4
cd ../bin
./auth --test-run
./char --test-run