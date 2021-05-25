## Experiment

### 配置环境
```bash
sudo apt install net-tools
sudo apt install openssh-server
sudo apt install traceroute
sudo apt install git
sudo apt-get install -y iperf3

git clone https://github.com/mininet/mininet.git
mininet/util/install.sh -fnv

cd mininet/examples/
sudo python linuxrouter.py
help
pingall
nodes
exit

ifconfig
sudo ovs-vsctl show
sudo ovs-ofctl dump-flows s1

```

### 建立网络

这个配置 VM 的 IP 不知道是干什么用的, 先不做试试看
```bash
VM1: tuntun
ifconfig eth0 192.168.56.101 netmask 255.255.255.0
VM2: dongge
ifconfig eth0 192.168.56.102
```

### Wireshark
```bash
sudo add-apt-repository universe
sudo apt install wireshark
```

### GIT Config
```bash
ssh-keygen -t rsa -C "wx_lin@outlook.com"

ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQCpemyprpicd2AINMe2ELh33eFAH3Qrc3ijf9ogF0fI10mJ1rc+8S37LOdmLF1QUyWe4iPLTqJPGaz01pGVAx/YJt//0KWih/ih+W8sDeSCbrViG/WxxtzjYM7VV0VumCLii57y8yozrRIPySaz0wIKxU7S65s31pfBhgVYErAHAMC7dgL0cPD0W3Awtiw6DdpLkY79oTpyYBFUPsWD3yl8JrvNJY106AaLdqh6J3s+Kpm9gF/3zbUIe2ipjDKHd5hYK5izgqTqNkzRwuy+Rco2bf1vzZQKUk6Rxa9+E6r3HnkLYPewXnVhPUQN9B7CETHzJPCxRchHFJgdzMzY7n2f wx_lin@outlook.com
```

### Run the code

以 server:tuntun 为 VM1 `python net1.py`, server:dongge 为 VM2. `python net2.py`

#### Q1


#### Q2


#### Q3


