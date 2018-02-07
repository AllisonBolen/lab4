#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <netinet/ether.h>

int main(int argc, char **argv){

int sockfd = socket(PF_PACKET,SOCK_RAW, htons(ETH_P_ALL)); // I want a socket where Im going to see the entire packet
struct sockaddr_ll addr, listenaddr;
listenaddr.sll_family=AF_PACKET; // family exists for conversion stuill tell waht it originally was
listenaddr.sll_protocol=htons(ETH_P_ALL);
listenaddr.sll_ifindex=if_nametoindex("h1-eth0");//interface  try not to hard code this is for mininet
bind(sockfd,(struct sockaddr*)&listenaddr,sizeof(listenaddr));

while(1){
  int len = sizeof(addr);
  char buf[5000];
  int n = recvfrom(sockfd,buf,5000,0,(struct sockaddr*)&addr, &len); //set up recive?

  if(addr.sll_pkttype!=PACKET_OUTGOING){

    printf("GOT A PACKET\n");

    struct ether_header eh;
    memcpy(&eh,&buf[0],14); // what does this do? copying to eh from the // ehternet is first thing so it always starts a byte zero of buffer
    printf("Destination %s\n", ether_ntoa((struct ether_addr*)&eh.ether_dhost));

  }
}
}
