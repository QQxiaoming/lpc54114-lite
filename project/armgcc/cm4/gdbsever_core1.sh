#!/bin/sh
JLinkGDBServer -port 2341 -SWOPort 2342 -TelnetPort 2343 -device LPC54114J256_M0 -endian little -if SWD -speed 4000 -noir -noLocalhostOnly