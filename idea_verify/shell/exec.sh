#!/bin/sh


LOG_DIR=./log
exec 1>>${LOG_DIR}

echo "this is a test"
ls

