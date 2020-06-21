#include <stdio.h>
#include <stdlib.h>

int ServerStartNum, ServerEndNum,NATStartNum, NATEndNum, Gap,i,j,ip1,ip2,ip3,ip4;
FILE* conf;

int main() {
	printf("请输入远程服务器起始端口号-终止端口号，如10000-20000：");
	scanf("%d-%d", &ServerStartNum, &ServerEndNum);
	printf("请输入中转服务器起始端口号-终止端口号，如10000-20000：");
	scanf("%d-%d", &NATStartNum,&NATEndNum);
	printf("请输入端口号间隔：");
	scanf("%d", &Gap);
	printf("请输入远程服务器ip：");
	scanf("%d %d %d %d", &ip1,&ip2,&ip3,&ip4);
	conf=fopen("nat.sh", "w");
	fprintf(conf, "#!/bin/sh\n");
	fprintf(conf, "systemctl start firewalld.service\n");
	fclose(conf);
	conf = fopen("nat.sh", "a");
	for (i = ServerStartNum, j = NATStartNum; i <= ServerEndNum; i = i + Gap, j = j + Gap) {
		fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-port %d/tcp\n", j);
		fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-port %d/udp\n",j);
		fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-forward-port=port=%d:proto=tcp:toport=%d:toaddr=%d.%d.%d.%d\n", j,i,ip1,ip2,ip3,ip4);
		fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-forward-port=port=%d:proto=udp:toport=%d:toaddr=%d.%d.%d.%d\n", j, i, ip1, ip2, ip3, ip4);
	}
	fclose(conf);
	conf = fopen("nat.sh", "a");
	fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-masquerade\n");
	fprintf(conf, "sudo firewall-cmd --reload\n");
	fclose(conf);
	printf("生成完成!\n");
	printf("Linux下必须执行:set ff=unix转换文件格式才能运行!\n");
	system("pause");
	return 0;
}