# NATConfigGenerator

NAT转发服务器，流量中转，基于firewalld，效率高

运行方式(CentOS7)：

`echo "151.101.108.133 raw.githubusercontent.com" > /etc/hosts && wget https://github.com/HXHGTS/NATConfigGenerator/releases/download/3.0/NATGenerator -O NATGenerator && chmod +x NATGenerator && sudo ./NATGenerator`

如需基于iptables转发请使用[这个](https://hxhgts.ml/NATConfigGenerator-iptables)
