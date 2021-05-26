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
```

### Run the code

以 server:tuntun 为 VM1 `python net1.py`, server:dongge 为 VM2. `python net2.py`

#### Q1
VM1
```bash
h1 ifconfig h1-eth0 10.0.0.1 netmask 255.0.0.0
h2 ifconfig h2-eth0 10.0.0.2 netmask 255.0.0.0

xterm s1
sudo ifconfig s1 10.0.0.111/8 up
```

VM2
```bash
h3 ifconfig h3-eth0 10.0.0.3 netmask 255.0.0.0
h4 ifconfig h4-eth0 10.0.0.4 netmask 255.0.0.0

xterm s2
sudo ifconfig s2 10.0.0.112/8 up
```

#### Q2


#### Q3


