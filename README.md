# NATConfigGenerator
NAT跳转服务器端口转发配置工具，适用于流量中转，基于firewalld，NAT服务器系统必须为CentOS7+系统！

运行方式：
```
yum install -y wget gcc && echo "151.101.108.133 raw.githubusercontent.com" >> /etc/hosts && wget https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator/master/NATGenerator.c -O NATGenerator.c && chmod +x NATGenerator.c && gcc -o NATGenerator NATGenerator.c && ./NATGenerator
```
