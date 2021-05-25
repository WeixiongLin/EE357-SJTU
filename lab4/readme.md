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


### Iperf



