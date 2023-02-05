#!/bin/bash
conf='/etc/apache2/mods-available/userdir.conf'
sed -i 's/public_html/./g' $conf
sed -i 's/.*disabled.*//g' $conf

a2enmod userdir
systemctl restart apache2
ln -s /var/log /home/