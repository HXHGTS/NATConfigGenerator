# NATConfigGenerator

NAT跳转服务器，流量中转，基于firewalld，效率高

运行方式(CentOS7)：
```
yum install -y wget gcc && echo "151.101.108.133 raw.githubusercontent.com" > /etc/hosts && wget https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator/master/NATGenerator.c -O NATGenerator.c && chmod +x NATGenerator.c && gcc -o NATGenerator NATGenerator.c && ./NATGenerator
```
