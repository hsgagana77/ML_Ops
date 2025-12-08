#!/bin/bash
set -e

SRC_DIR = "$WORKSPACE"
DEST_DIR = "/var/www/html/cafestatic"
APACHE_CONF = "/etc/apache2/sites-available/000-default.conf"

sudo cp -r "$SRC_DIR"/* "$DEST_DIR"/

sudo sed -i "s|DocumentRoot .*|DocumentRoot $DEST_DIR|g" "$APACHE_CONF"

sudo systemctl restart apache2

echo "Deployment completed successful"
