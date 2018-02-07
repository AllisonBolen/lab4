lab.c

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <netinet/ether.h>

int main(int argc, char **argv){

int socket = socket(PF_PACKET.SOCK_RAW, htons(ETH_P_ALL); // I want a socket where Im going to see the entire packet
struct sockaddr_ll addr, listenaddr;
listenaddr.sll_family=AF_PACKET; // family exists for conversion stuill tell waht it originally was
listenaddr.sll_protocol=htons(ETH_P_ALL);
listenaddr.sll_ifindex=if_nametoindex("h1-eth0");//interface  try not to hard code this is for mininet
bind(sockfd,(struct sockaddr*))&listenaddr,sizeof(listenaddr);

while(1){
  int len = sizeof(addr);
  char buf[5000];
  int n = recvfrom(sockfd,buf,0,(struct sockaddr*)&addr, &len); //set up recive?
  // these type of sockets see all packets
  if(addr.sll_pkttype!=PACKET_OUTGOING){
    // no option for incoming jsut fileter outgoing
    printf("GOT A PACKET\n");
    // all packets are an array of chars
    // to no tlook at them a byte a t a time
    //usr/include/net dir on dc comps, we can find a bunch of .h files some can give us structs for low level sll_protocol
    // look at eitehrnet.h we can see a struct for ethernet header 10mb ethernet header
    // conatins the ethernet header structs and types and shit
    struct ether_header eh;
    memcpy(&eh,&buf[0],14); // what does this do? copying to eh from the buf the lenght of
    // ehternet is first thing so it always starts a byte zero of buffer
    printf("Destination %s\n", ether_ntoa((struct ether_addr*)&eh.ether_dhost));
    // print teh desination of the packet we saw
    // for higher layer protocols
  }
}




// h to n s takes a short int
// h to n l takes a long 32 bit
// these can all work,
// n to h s convert from teh networks byte order to teh hosts byte order
// n to h l
// wil have to use one of those functions
}
