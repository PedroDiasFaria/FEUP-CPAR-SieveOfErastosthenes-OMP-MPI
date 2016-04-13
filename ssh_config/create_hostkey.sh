#!/bin/bash
this_dir=$(pwd)

mkdir -p ~/.ssh
cd ~/.ssh
ssh-keygen -t dsa

cat id_dsa.pub >> authorized_keys

cp authorized_keys $this_dir/authorized_keys
cp id_dsa.pub $this_dir/id_dsa.pub