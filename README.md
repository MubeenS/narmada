# Introduction

This project involves developing an Enterprise Service Bus (ESB) in C.

## Setting up the environment for running the app

The following instructions assume that you are working on an Ubuntu machine, and are in the sudoers group (or have root-access).

### Installing essential libraries that you will need

1. Open a shell and run `sudo apt update`
1. Ensure that you have installed the essential headers and libraries: `sudo apt install build-essential`
1. Install the XML library ([libxml2](https://askubuntu.com/questions/733169/how-to-install-libxml2-in-ubuntu-15-10)) which will be used for parsing and handling xml files(BMD requests) received via HTTP.
1. The app uses MySQL database. Install [MySQL](https://www.digitalocean.com/community/tutorials/how-to-install-mysql-on-ubuntu-18-04) on your machine.
1. Install [cURL](https://www.cyberciti.biz/faq/how-to-install-curl-command-on-a-ubuntu-linux/). The modules that send data over different protocols use cURL.
1. Install required modules for creating SFTP server and create a local [SFTP server](https://linuxconfig.org/how-to-setup-sftp-server-on-ubuntu-20-04-focal-fossa-linux#:~:text=You%20can%20use%20your%20preferred,the%20window%20and%20click%20connect.).(More details in setup)
1. Install Kore Web framework as [described here](https://docs.kore.io/3.3.1/install.html). This will be used for creating an HTTP endpoint for receiving the requests for the ESB.
1. The app comes along with a unit testing framework [munit](https://nemequ.github.io/munit/#getting-started). You don't need to install any.

### Customized setup

The app uses the default setup. Feel free to customize them to your convenience.
##### 1. MYSQL

 Default USER: root
 
 Default PASS:
 
 (No password set for convenience. You can either remove the password in your machine or change source.)
 
 To change password and other configurations goto `narmada/esb_app/src/db_access/connection.h`
#### 2.SFTP

Default USER: narmadasftp

Default PASS: narmada1

To be able to upload over SFTP with default settings, you should create the above user with the given password at the localhost.
```
$ sudo useradd -m narmadasftp -g sftp
$ sudo passwd sftpuser
New password: 
Retype new password: 
passwd: password updated successfully
```
To change the change configurations, please goto `narmada/esb_app/src/adapter/sftp_upload.c` and edit as required.

## Creating a workspace with the sample code

You can execute the following steps on a shell (on Ubuntu):
```bash
# Install required libraries
sudo apt update
sudo apt install build-essential
sudo apt install libssl-dev
sudo apt install wget
sudo apt install curl

# Download the kodev sources
wget https://kore.io/releases/kore-3.2.0.tar.gz
tar -xf kore-3.2.0.tar.gz
cd kore-3.2.0/

# Build and install kodev
make
sudo make install

# Change directories into a working folder
cd /path/to/where/you/want/to/work

# Fetch the code from this repository
git clone https://github.com/nho2020/narmada.git

# Build and run the kodev application
cd narmada/esb_app
#Within esb_app run the following.
kodev build
kodev run
```

Open another shell window and run:
Within narmada/esb_app/src/bmd_files/
Run the following command sends the requests.
`curl --insecure -F "bmd_file=@bmd1.xml" https://localhost:8888/bmd`
narmada/esb_app/src/bmd_files/ has bmd[1-18].xml

1 to 9 files contain  payload of IFSC code of Indian banks. 
10 to 18 files contain payload details of country code for currency.

Check the logs in the first shell; the log shows how BMD is received and being processed.


