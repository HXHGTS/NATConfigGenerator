# NATConfigGenerator

NAT转发服务器，流量中转，基于firewalld，效率高

运行方式(CentOS7)：

`yum install -y wget gcc && wget https://cdn.jsdelivr.net/gh/HXHGTS/NATConfigGenerator@3.0/NATGenerator.c -O NATGenerator.c && gcc -o NATGenerator NATGenerator.c && chmod +x NATGenerator && sudo ./NATGenerator`

如需基于iptables转发请使用[这个](https://hxhgts.ml/NATConfigGenerator-iptables)
