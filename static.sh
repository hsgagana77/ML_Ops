#Baremetal

#!/bin/bash
set -e

SRC_DIR="$WORKSPACE"
DEST_DIR="/var/www/html/cafestatic"
APACHE_CONF="/etc/apache2/sites-available/000-default.conf"

sudo cp -r "$SRC_DIR"/* "$DEST_DIR"/

sudo sed -i "s|DocumentRoot .*|DocumentRoot $DEST_DIR|g" "$APACHE_CONF"

sudo systemctl restart apache2

echo "Deployment completed successfully"

#sudo visudo
#Add:   jenkins ALL=(ALL) NOPASSWD:ALL


#Dockerfile

#cafe-static
FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y apache2

COPY . /var/www/html/

EXPOSE 80

CMD ["apachectl", "-D", "FOREGROUND"]


#php-website
FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y apache2 php libapache2-mod-php

COPY . /var/www/html/

EXPOSE 80

CMD ["apachectl", "-D", "FOREGROUND"]


#Deployment file

apiVersion: apps/v1
kind: Deployment

metadata:
  name: book

spec:
  replicas: 1

  selector:
    matchLabels:
      app: book

  template:
    metadata:
      labels:
        app: book

    spec:
      containers:
      - name: book
        image: gaganahs/phpapp:latest
        ports:
        - containerPort: 80


#service file

apiVersion: v1
kind: Service
metadata:
  labels:
    app: book
  name: book
spec:
  type: NodePort
  ports:
    - port: 80
      targetPort: 80
      protocol: TCP
  selector:
    app: book
