#include <stdio.h>
#include <stdlib.h>

int ServerStartNum, ServerEndNum, NATStartNum, NATEndNum, Gap, i, j, protocol, mode, run;
int ip1,ip2,ip3,ip4;
FILE* conf;

int main() {
	printf("请选择运行模式：\n\n1.添加转发规则\n\n2.删除转发规则\n\n请输入：");
	scanf("%d", &mode);
	printf("\n");
	printf("请输入远程服务器起始端口号-终止端口号，如10000-20000：");
	scanf("%d-%d", &ServerStartNum, &ServerEndNum);
	printf("\n");
	printf("请输入中转服务器起始端口号-终止端口号，如10000-20000：");
	scanf("%d-%d", &NATStartNum, &NATEndNum);
	printf("\n");
	printf("请输入端口号间隔：");
	scanf("%d", &Gap);
	printf("\n");
	printf("请输入远程服务器ip，如8.8.8.8请写为8-8-8-8：");
	scanf("%d-%d-%d-%d", &ip1,&ip2,&ip3,&ip4);
	printf("\n");
	printf("请输入转发协议：\n\n1.All\n\n2.tcp\n\n3.udp\n\n请输入：");
	scanf("%d", &protocol);
	printf("\n");
	if (ServerStartNum > ServerEndNum || NATStartNum > NATEndNum || ServerStartNum > 65535 || ServerEndNum > 65535 || NATStartNum > 65535 || NATEndNum > 65535) {
		printf("非法输入，请检查输入！\n");
	}
	else {
		if (mode == 1) {
			conf = fopen("nat-add.sh", "w");
			fprintf(conf, "#!/bin/sh\n");
			fprintf(conf, "systemctl start firewalld.service\n");
			if (protocol == 1) {
				for (i = ServerStartNum, j = NATStartNum; i <= ServerEndNum; i = i + Gap, j = j + Gap) {
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-port %d/tcp\n", j);
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-port %d/udp\n", j);
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-forward-port=port=%d:proto=tcp:toport=%d:toaddr=%d.%d.%d.%d\n", j, i,ip1,ip2,ip3,ip4);
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-forward-port=port=%d:proto=udp:toport=%d:toaddr=%d.%d.%d.%d\n", j, i,ip1,ip2,ip3,ip4);
				}
			}
			else if (protocol == 2) {
				for (i = ServerStartNum, j = NATStartNum; i <= ServerEndNum; i = i + Gap, j = j + Gap) {
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-port %d/tcp\n", j);
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-forward-port=port=%d:proto=tcp:toport=%d:toaddr=%d.%d.%d.%d\n", j, i,ip1,ip2,ip3,ip4);
				}
			}
			else {
				for (i = ServerStartNum, j = NATStartNum; i <= ServerEndNum; i = i + Gap, j = j + Gap) {
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-port %d/udp\n", j);
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-forward-port=port=%d:proto=udp:toport=%d:toaddr=%d.%d.%d.%d\n", j, i,ip1,ip2,ip3,ip4);
				}
			}
			fprintf(conf, "sudo firewall-cmd --zone=public --permanent --add-masquerade\n");
			fprintf(conf, "sudo firewall-cmd --reload\n");
			fprintf(conf, "sudo firewall-cmd --list-all\n");
			fclose(conf);
			printf("\n\n");
			printf("生成完成!\n");
		}
		else {
			conf = fopen("nat-del.sh", "w");
			fprintf(conf, "#!/bin/sh\n");
			if (protocol == 1) {
				for (i = ServerStartNum, j = NATStartNum; i <= ServerEndNum; i = i + Gap, j = j + Gap) {
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --remove-forward-port=port=%d:proto=tcp:toport=%d:toaddr=%d.%d.%d.%d\n", j, i,ip1,ip2,ip3,ip4);
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --remove-forward-port=port=%d:proto=udp:toport=%d:toaddr=%d.%d.%d.%d\n", j, i,ip1,ip2,ip3,ip4);
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --remove-port %d/tcp\n", j);
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --remove-port %d/udp\n", j);
				}
			}
			else if (protocol == 2) {
				for (i = ServerStartNum, j = NATStartNum; i <= ServerEndNum; i = i + Gap, j = j + Gap) {
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --remove-forward-port=port=%d:proto=tcp:toport=%d:toaddr=%d.%d.%d.%d\n", j, i,ip1,ip2,ip3,ip4);
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --remove-port %d/tcp\n", j);
				}
			}
			else {
				for (i = ServerStartNum, j = NATStartNum; i <= ServerEndNum; i = i + Gap, j = j + Gap) {
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --remove-forward-port=port=%d:proto=udp:toport=%d:toaddr=%d.%d.%d.%d\n", j, i,ip1,ip2,ip3,ip4);
					fprintf(conf, "sudo firewall-cmd --zone=public --permanent --remove-port %d/udp\n", j);
				}
			}
			fprintf(conf, "sudo firewall-cmd --reload\n");
			fprintf(conf, "sudo firewall-cmd --list-all\n");
			fclose(conf);
			printf("\n\n");
			printf("生成完成!\n");
		}
		printf("\n");
		printf("是否立即运行命令?（是=1，否=2）：");
		scanf("%d", &run);
		if (run == 1) {
			if (mode == 1) {
				system("chmod +x nat-add.sh");
				system("bash nat-add.sh");
			}
			else {
				system("chmod +x nat-del.sh");
				system("bash nat-del.sh");
			}
		}
		printf("\n");
		printf("执行完成！\n");
	}
	return 0;
}