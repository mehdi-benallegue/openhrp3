#!/bin/sh

openhrp-controller-bridge \
--server-name SampleHGController \
--in-port angle:JOINT_VALUE \
--in-port vel:JOINT_VELOCITY \
--in-port acc:JOINT_ACCELERATION \
--connection angle:SampleHG0:angle \
--connection vel:SampleHG0:vel \
--connection acc:SampleHG0:acc
