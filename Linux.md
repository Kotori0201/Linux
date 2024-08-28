# Tạo User and Group
- Tạo một user mới: **useradd -m -d /home/new_user -c "desciption" new_user**
Trong đó:   

            -m: tạo home 
            -d: tạo một home dir
            -c:
            -g: 
            -u:

- Tạo group: **sudo groupadd groupname**
- Để hiện user&host: **sudo usermod username -s /bin/bash**
- Swap user: **sudo su - username**
- Đổi password của user: **passwd username**
- Thêm user vào các group: **usermod -aG groupname1,groupname2,... username**
- Xóa user: **userdel -r username**
- Xóa group: **sudo groupdel groupname**
- Xóa user khỏi group: **sudo gpasswd -d username groupname**
- Thay đổi người tạo và group thư mục: **chown username:usergroup /.../...**
- Thay đổi người tạo: **chown username /.../...**
- Thay đổi group: **chown :usergroup /.../...**
- Thay đổi quyền: **chmod xxx /.../...**
- Muốn adm1n == root: sửa file: **sudo nano /etc/passwd**
- Thay đổi group chính của user: **sudo usermod -g groupname username**
- Tạo và gán user vào group: **sudo useradd -g users -G wheel,developers username**
- List all user: **cut -d: -f1 /etc/passwd** or **getent passwd** or **getent group** or **getent passwd username**
- Change name: 
    ```
    sudo usermod -l newUsername oldUsername
    sudo groupmod -n newUsername oldUsername
    ```
- Change home folder:
    - **sudo usermod -d /home/newHomeDir -m newUsername**
## **Password**: 
### Policy password
- **nano /etc/pam.d/common-password** phải cài thêm thư viện

    - password [success=1 default=ignore] pam_unix.so minlen=8 ... obscure yescrypt
- **password expirations**: /etc/login.defs
    - **PASS_MAX_DAYS**: How many days the password is active before it expires.
    - **PASS_MIN_DAYS**: How many days a password must be active before it can be changed by a user.
    - **PASS_WARN_AGE**: The number of days a warning is issued to the user before an impending password expiry.
- **Enforce_for_root**: sudo nano /etc/security/pwqua...
### Su and Sudo
- Chặn su và sudo su để ko cho user swap sang user khác: **nano /etc/pam.d/su**
    - Cách 1: Thêm nó vào group nosu
    - Cách 2: Chặn từng group
    - Cách 3: Chặn tất cả su và chỉ cho dùng sudo su với những user có quyền root
- Muốn có quyền sudo thì cho vào group sudo/root/admin

- Để gõ sudo với user adm1n mà ko cần nhập pass: **username ALL=(ALL) NOPASSWD: ALL**

- Change **hostname**: **sudo hostnamectl set-hostname newNameHere**
                     then **sudo nano /etc/hosts** thay tên mới vào
                     then **reboot**

- Change timzone: **sudo timedatectl set-timezone <Tên time zone>/Asia/Ho_Chi_Minh**
# SSH
![SSH](image-11.png)

![SSH](https://download.huawei.com/mdl/image/download?uuid=e355b8540acb4688ae03e7f880cb0948)
- Change port ssh: **nano /etc/ssh/ssh_config**
- Restart sshd: **sudo systemctl restart sshd** or **sudo service ssh restart**
- Để ssh từ máy A sang máy B với ssh_key thì:
    - gen key ở A: **ssh-keygen -t rsa**
    - copy public key sang B
    - Thay thế public key sang file authorized_keys của B
    - Tạo NAT Network của Virtual Box
    - Thêm rule cho NAT Network để ssh từ window sang 2 máy A,B

- Diable SSH: Open file **/etc/ssh/sshd_config** in any text editor, **DenyUsers	username**
- Chuyển key:

    ``**ssh-copy-id username@remote-server**``

    ``**scp -r -P xxxx /home/d3v/.ssh/ d3v@server-x:/home/d3v/.ssh/**``
# Vi
- **v**: chọn kí tự
- **yy**: sao chép 
- **p**: paste dưới dong hien tai
- **P**: paste trên dòng hien tai
- **nG**: n là số dòng
- **H** lên dòng đầu đang hiển thị của màn hình
- **T**: xuống dòng cuối đang hiển thị trên màn hình
- **n** và **N** tìm kiếm lùi lại hoặc tiếp theo
- replace: 
    - **:startline,endline s/pattern/replacement/g**
    - **:%s/chu_cu/chu_moi/g**
# Nano
**F1: Xem các shortcut khác**
## Search
- Ctrl + W : search
- Ctrl + /: nhập số dòng để đến dòng đó
- Để xem kết quả tìm kiếm: Alt + W/Q    (tiến/lùi)
# File
- Xem chi tiết file: stat 
## Type of files
![File Types](image-8.png)
## Permission file
![Permissions File](https://www.pluralsight.com/content/dam/pluralsight2/b2c-blog-files/seo-refresh/linux-file-permissions/Linux-File-Permissions-2.webp)

![alt text](image.png)

- Thay đổi quyền: **chmod permissions filename**
### Symbolic mode
- This method uses symbols like u, g, o to represent users, groups, and others. Permissions are represented as r, w, x for read write and execute, respectively. You can modify permissions using +, - and =.

![alt text](image-1.png)

![alt text](image-2.png)

- To add execution rights (x) to owner (u) using symbolic mode, we can use the command below: **chmod u+x mymotd.sh**
- Removing read and write permission for group and others: **chmod go-rw**
- Removing read permissions for others: **chmod o-r**
- Assigning write permission to group and overriding existing permission: **chmod g=w**
### Absolute mode

![alt text](image-3.png)

![alt text](image-4.png)

- Set read (add 4) for user, read (add 4) and execute (add 1) for group, and only execute (add 1) for others: **chmod 451 file-name**
![alt text](image-5.png)
- Remove execution rights from other and group
![alt text](image-6.png)
- Assign read, write and execute to user, read and execute to group and only read to others.
![alt text](image-7.png)

## Find File
- Tìm file theo size: **https://linuxconfig.org/how-to-use-find-command-to-search-for-files-based-on-file-size**
    - chính xác: **find . -size (X)M**
    - bé hơn: **find . -size -(X)M**
    - lớn hơn: **find . -size +(X)M**
    - kết hợp: **find . -size +(A)M -size -(B)M**
    - **sudo find /etc -size +1k | tail/head -3**
- Các tag khi find:
    - **-type**: f/d
    - **-name**: -name "file1"
    - **-newer**: mới hơn file nào đó
- Muốn lưu kết quả find vào một file:   **find ... > filename.txt**
- Xóa nhiều file cùng một dir, mà các file đó bao gồm một đoạn string giống nhau: **rm *str***
- Muốn chạy file bash mà không cần bash trước thì cấp quyền thực thi cho nó: **chmod +x**

## / tree file
![/ dir ](image-9.png)

![des](image-10.png)
# IP
## Change IP
- **sudo nano /etc/netplan/00-installer-config.yaml** then **sudo netplan apply**

- Có thể gây mất mạng nếu mà set ip tĩnh, phải set lại gateway4
- Xem route: **ip r**

- DHCP cấp IP khác nhau theo mac: thêm **dhcp-identifier: mac**
# Tomcat
```
## Bước 1
- **sudo apt update**
- **sudo apt install default-jdk -y**: cài đặt java
## Bước 2: tải tomcat-version 9
```wget --no-check-certificate https://dlcdn.apache.org/tomcat/tomcat-9/v9.0.93/bin/apache-tomcat-9.0.93.tar.gz```

## Bước 3: tạo directory cho service tomcat
**sudo mkdir /opt/tomcat**

## Bước 4: Giải nén file gz (ở bước 2) -> directory vừa tạo (ở bước 3)
**sudo tar xzf /home/d3v/apache-tomcat-9.0.93.tar.gz -C /opt/tomcat --strip-components=1**

## Bước 5: Đổi owner sang d3v và cấp quyền thực thi
sudo chown -R d3v:d3v /opt/tomcat/

sudo chmod -R u+x /opt/tomcat/bin

## Bước 6: chỉnh sửa cấu hình trong tệp
sudo nano /opt/tomcat/conf/tomcat-users.xml

``<role rolename="manager-gui" />
<user username="manager" password="123" roles="manager-gui" />
<role rolename="admin-gui" />
<user username="admin" password="123" roles="manager-gui,admin-gui" />``

## Bước 7: chỉnh sửa cấu hình trong thư tệp 
sudo nano /opt/tomcat/webapps/manager/META-INF/context.xml
--> comment tag <Valve></>
sudo nano /opt/tomcat/webapps/host-manager/META-INF/context.xml
--> comment tag <Valve></>

## Bước 8: lấy link đến jdk và gắn vào JAVA_HOME
update-java-alternatives -l

## Bước 9: chỉnh sửa tệp
sudo nano /etc/systemd/system/tomcat.service

[Unit]
Description=Tomcat
After=network.target

[Service]
Type=forking

User=d3v
Group=d3v

Environment="JAVA_HOME=/usr/lib/jvm/java-1.11.0-openjdk-amd64"
Environment="JAVA_OPTS=-Djava.security.egd=file:///dev/urandom"
Environment="CATALINA_BASE=/opt/tomcat"
Environment="CATALINA_HOME=/opt/tomcat"
Environment="CATALINA_PID=/opt/tomcat/temp/tomcat.pid"
Environment="CATALINA_OPTS=-Xms512M -Xmx1024M -server -XX:+UseParallelGC"

ExecStart=/opt/tomcat/bin/startup.sh
ExecStop=/opt/tomcat/bin/shutdown.sh

RestartSec=10
Restart=on-failure

[Install]
WantedBy=multi-user.target

## Bước 10: reload và hưởng thụ
sudo systemctl daemon-reload
sudo systemctl restart tomcat.service
sudo systemctl status tomcat.service
curl localhost:8080

## Đổi port:
sudo nano /opt/tomcat/conf/server.xml

## Có thể start and shutdown tomcat:
bash /opt/tomcat/bin/shutdown.sh
bash /opt/tomcat/bin/startup.sh
```

# MYSQL
```
re: https://www.digitalocean.com/community/tutorials/how-to-allow-remote-access-to-mysql

dowload mysql-client in tomcat machine: sudo apt-get install mysql-client -y
dowload mysql-server in database machine: sudo apt-get install mysql-server -y

In db machine: 
	- $ sudo nano /etc/mysql/mysql.conf.d/mysqld.cnf
	- change bind-address: 127.0.0.1 -> 0.0.0.0
	- $ sudo systemctl restart mysql
	- $ sudo mysql
	- $ mysql -u root -p
	- $ mysql> RENAME USER 'sammy'@'localhost' TO 'sammy'@'<tomcat_machine_ip>';
	- $ mysql> CREATE USER 'sammy'@'<tomcat_machine_ip>' IDENTIFIED BY 'password';
	- $ mysql> GRANT CREATE, ALTER, DROP, INSERT, UPDATE, DELETE, SELECT, REFERENCES, RELOAD on *.* TO 'sammy'@'10.111.1.100' WITH GRANT OPTION;
	- $ mysql> FLUSH PRIVILEGES;
	- $ mysql> exit
	- $ sudo ufw allow from <tomcat_machine_ip> to any port 3306
	- $ sudo ufw allow 3306
In tomcat machine:
 	- $ mysql -u user -h database_server_ip -p
	- type pw
	- login to sql server success
Change port mysql: sudo nano /etc/mysql/mysql.cnf thêm 
[mysqld]
port xxxx

```

# Display process and Kill process
## Display process
**ps aux**: display all processes
- Running this command will display a table of process information, including columns for:

- USER: The username of the owner of the process.
- PID: The process ID (PID) of the process.
- %CPU: The percentage of CPU time used by the process.
- %MEM: The percentage of physical memory used by the process.
- VSZ: The virtual memory size of the process.
- RSS: The resident set size (the non-swapped physical memory) used by the process.
- TTY: The controlling terminal of the process.
- STAT: The process state (e.g., running, sleeping, etc.).
- START: The time when the process started.
- TIME: The cumulative CPU time used by the process.
- COMMAND: The command used to start the process.

**You can customize the output of the ps command by specifying different options and arguments. Some common options include:**

- -e: Select all processes.
- -f: Provide a full-format listing.
- -u: Select the processes owned by the specified user.
- -l: Provide a long listing format.

## Kill process
- **kill PID**

## Run background process
- Thêm **&** vào cuối. Ví dụ **bash bash.sh &**
- **jobs**: show list background process
- **fg %1**: bring process 1 to foreground

# Write a bash file using loop to print CPU, RAM, DISK information every 20 secs
- Display number process of VM: **nproc**
- Display RAM: **free -h**
![RAM](https://green.cloud/docs/wp-content/uploads/2022/08/RAM1-750x235.png)
The results show that my VPS has the following RAM memory parameters:

- (1) Total memory capacity is 1.9 GB (total)
- (2) Used 68 MB (used)i
- (3) Free space equal to 1.6 iGB (free)
- (4) The amount of memory used for caching is 293 MB (buff/cache
- More Display RAM: **egrep --color 'Mem|Cache' /proc/meminfo**
- Display Disk information: **df -h**