#include <stdio.h>
#include <stdlib.h>

int ServerStartNum, ServerEndNum, NATStartNum, NATEndNum, PortGap, ServerPort, NATPort,OpenPort, mode, run;
int ip1,ip2,ip3,ip4;
char cmd[200], protocol[5];
int main() {
	system("clear");
	UI();
	if (mode == 3) {
		CheckNAT();
	}
	else if (mode == 1 || mode == 2) {
		printf("请输入远程服务器起始端口号-终止端口号，如10000-20000:");
		scanf("%d-%d", &ServerStartNum, &ServerEndNum);
		printf("\n");
		printf("请输入中转服务器起始端口号-终止端口号，如10000-20000:");
		scanf("%d-%d", &NATStartNum, &NATEndNum);
		printf("\n");
		printf("请输入端口号间隔:");
		scanf("%d", &PortGap);
		printf("\n");
		printf("请输入远程服务器ip，注意中间点改成空格，如8.8.8.8请写为8 8 8 8:");
		scanf("%d %d %d %d", &ip1, &ip2, &ip3, &ip4);
		printf("\n");
		printf("请输入转发协议(t=tcp or u=udp):");
		scanf("%s", protocol);
		printf("\n");
		if (CheckInput()==1) {
			printf("非法输入，请检查输入！\n");
		}
		else {
			NATProtocol();
			if (mode == 1) {
				AddNAT();
				printf("\n\n");
				printf("执行完成!\n");
			}
			else {
				DelNAT();
				printf("\n\n");
				printf("生成完成!\n");
			}
			printf("\n");
			printf("执行完成！\n");
		}
	}
	else if(mode==4||mode==5) {
		printf("请输入端口号，如10000:");
		scanf("%d", &OpenPort);
		printf("请输入协议(t=tcp or u=udp):");
		scanf("%s", protocol);
		if (CheckInput() == 1) {
			printf("非法输入，请检查输入！\n");
		}
		else {
			NATProtocol();
			if (mode == 4) {
				PortOpen();
				printf("\n\n");
				printf("执行完成!\n");
			}
			else {
				PortClose();
				printf("\n\n");
				printf("生成完成!\n");
			}
			printf("\n");
			printf("执行完成！\n");
		}
	}
	else if (mode == 6) {
		system("systemctl stop firewalld.service");
		system("systemctl disable firewalld.service");
		printf("执行完成！\n");
	}
	else if (mode == 7) {
		system("yum install firewalld firewall-config -y");
		system("systemctl start firewalld.service");
		system("systemctl enable firewalld.service");
		printf("执行完成！\n");
	}
	else{
		exit(0);
	}
	return 0;
}

int UI() {
	printf("请注意：本软件仅支持CentOS系统，其它Linux系统不支持！\n\n");
	printf("请选择要执行的操作：\n\n1.添加转发规则\n\n2.删除转发规则\n\n3.查询转发规则\n\n4.开放特定端口\n\n5.删除特定端口\n\n6.关闭firewalld\n\n7.安装并开启firewalld(第一次使用建议执行，否则可能会转发失败)\n\n0.退出\n\n请输入：");
	scanf("%d", &mode);
	printf("\n");
	return 0;
}

int AddNAT() {
	for (ServerPort = ServerStartNum, NATPort = NATStartNum; ServerPort <= ServerEndNum; ServerPort = ServerPort + PortGap, NATPort = NATPort + PortGap) {
		sprintf(cmd, "firewall-cmd --zone=public --permanent --add-port %d/%s", NATPort,protocol);
		system(cmd);
		sprintf(cmd, "firewall-cmd --zone=public --permanent --add-forward-port=port=%d:proto=%s:toport=%d:toaddr=%d.%d.%d.%d", NATPort, protocol,ServerPort, ip1, ip2, ip3, ip4);
		system(cmd);
	}
	system("firewall-cmd --zone=public --permanent --add-masquerade");
	system("firewall-cmd --reload");
	system("firewall-cmd --list-all");
	return 0;
}

int DelNAT(){
	for (ServerPort = ServerStartNum, NATPort = NATStartNum; ServerPort <= ServerEndNum; ServerPort = ServerPort + PortGap, NATPort = NATPort + PortGap) {
		sprintf(cmd, "firewall-cmd --zone=public --permanent --remove-forward-port=port=%d:proto=%s:toport=%d:toaddr=%d.%d.%d.%d", NATPort, protocol,ServerPort, ip1, ip2, ip3, ip4);
		system(cmd);
		sprintf(cmd, "firewall-cmd --zone=public --permanent --remove-port %d/%s", NATPort,protocol);
		system(cmd);
	}
	system("firewall-cmd --reload");
	system("firewall-cmd --list-all");
	return 0;
}

int CheckNAT() {
	printf("系统NAT设置记录:\n\n");
	system("firewall-cmd --list-all");
	printf("\n");
	return 0;
}

int PortOpen() {
	sprintf(cmd, "firewall-cmd --zone=public --add-port=%d/%s --permanent", OpenPort, protocol);
	system(cmd);
	system("firewall-cmd --reload");
	system("firewall-cmd --list-all");
	return 0;
}

int PortClose() {
	sprintf(cmd, "firewall-cmd --zone=public --remove-port=%d/%s --permanent", OpenPort, protocol);
	system(cmd);
	system("firewall-cmd --reload");
	system("firewall-cmd --list-all");
	return 0;
}

int CheckInput() {
	if (mode == 2 || mode == 3) {
		if (ServerStartNum > ServerEndNum || NATStartNum > NATEndNum || ServerStartNum > 65535 || ServerEndNum > 65535 || NATStartNum > 65535 || NATEndNum > 65535) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (mode == 4 || mode == 5) {
		if (OpenPort > 65535) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

int NATProtocol() {
	if (protocol[0] == 't') {
		sprintf(protocol, "tcp");
	}
	else {
		sprintf(protocol, "udp");
	}
	return 0;
}
