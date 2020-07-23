# NATConfigGenerator
NAT跳转服务器端口转发配置工具，适用于流量中转，基于firewalld，NAT服务器系统必须为CentOS7+系统！

运行方式：

yum install -y wget gcc

wget https://github.com/HXHGTS/NATConfigGenerator/raw/master/NATGenerator.c

gcc -o NATGenerator NATGenerator.c

./NATGenerator

将考虑加入iptables支持
